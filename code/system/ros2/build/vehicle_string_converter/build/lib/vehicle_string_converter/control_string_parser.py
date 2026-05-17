'''
This node parses string messages from the control board into ControlData messages for use by the rest of the system

Note: this version cannot handle custom data types or special encodings
If these are added, the code must be updated to work like the sensor parser

Topics
 Subscribes to:
- /vehicle/control_status_str
    - String
 Publishes to:
- /vehicle/control_status
    - ControlData custom msg type

Parameters: 
- verbose (bool, default: false)
    - Whether to log all parsed data in the console
    - Useful for debugging but a lot of clutter / overhead for normal operation

'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import ControlFeedback
from std_msgs.msg import String

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml


class VehicleControlStringParser(Node):
    def __init__(self):
        super().__init__('vehicle_control_string_parser')
        self.get_logger().info('Starting Vehicle Control String Parser Node')

        # Expected execution parameters
        self.declare_parameter('verbose', False)  # Whether to log all parsed data in the console

        # Load control and delimiter codes once at startup
        package_share = get_package_share_directory('vehicle_string_converter')
        control_config_path = os.path.join(package_share, 'config', 'control_codes.yaml')
        delimiter_config_path = os.path.join(package_share, 'config', 'delimiters.yaml')
        try:
            with open(control_config_path, 'r') as f:
                self.control_codes = yaml.safe_load(f)
            with open(delimiter_config_path, 'r') as f:
                self.delimiters = yaml.safe_load(f)
        except Exception as e:
            # The control system can't run without the codes, but sensors can still run
            self.get_logger().error(f"Error loading control files; system will be unable to interface with control board: {e}")
            # Exit the node if configs can't be loaded
            rclpy.shutdown()
            return         

        self.get_logger().info(f"Successfully loaded control codes")

        # Subscriber to vehicle control update string messages
        self.control_subscriber = self.create_subscription(String, '/vehicle/control_status_str', self.control_callback, 10)
        # Publisher for control data formatted messages
        self.control_string_publisher = self.create_publisher(ControlFeedback, '/vehicle/control_status', 10)


    def control_callback(self, msg):
        # Convert the string message to a ControlFeedback message
        control_data = self.convert(msg)
        # Publish the ControlFeedback message
        if control_data:  # Only publish if conversion was successful
            self.control_string_publisher.publish(control_data)
            if self.get_parameter('verbose').get_parameter_value().bool_value:
                self.get_logger().info(f"Published control status update: {control_data}")
        else:
            self.get_logger().error("Failed to convert control status message to ControlFeedback format")


    def convert(self, msg):
        # Declare output type ControlFeedback
        control_data = ControlFeedback()
        # Get the string from the incoming message
        control_string = msg.data

        # First, check for valid packet delimiters
        start_delimiter = self.delimiters.get('packet_start', '')
        end_delimiter = self.delimiters.get('packet_end', '')
        # Makes sure delimiters aren't empty to avoid edge case
        if start_delimiter and end_delimiter:
            if not control_string.startswith(start_delimiter) or not control_string.endswith(end_delimiter):
                self.get_logger().error(f"Invalid control status message received: missing start/end delimiter")
                return None
        else:
            self.get_logger().error("Packet delimiters not defined in config files; unable to validate incoming messages")
            return None

        # Verify the data start and end delimiter
        data_start_delimiter = self.delimiters.get('field_start', '')
        data_end_delimiter = self.delimiters.get('field_end', '')
        if not data_start_delimiter or not data_end_delimiter:
            self.get_logger().error("Data delimiters not defined in config files; unable to validate incoming messages")
            return None

        # After checking the packet delimiters, strip them
        # (there existence has already been validated so they can safely be removed without additional checks)
        control_string = control_string[len(start_delimiter):len(control_string) - len(end_delimiter)]

        # Now split the string into components based on data delimiters
        command_strings = {}
        while control_string:
            # The code runs up to but not including the next data start delimiter
            split_index_start = control_string.find(data_start_delimiter)
            if split_index_start == -1:
                break  # No more data start delimiters, exit the loop
            split_index_end = split_index_start + len(data_start_delimiter)
            end_index = control_string.find(data_end_delimiter, split_index_end)
            if end_index == -1:
                self.get_logger().error(f"Invalid control status message format: the last data in the packet was missing its end delimiter")
                break  # No more data end delimiters, exit the loop
            
            # Get the next code and data substrings and store them in the command_strings dict
            next_code = control_string[:split_index_start]  # Get the substring before the next data start delimiter
            next_code = next_code.strip()  # Remove any leading/trailing whitespace from the code  
            next_data = control_string[split_index_end:end_index]  # Get the substring after the next data start delimiter

            # Only store if a code is present
            if not next_code:
                self.get_logger().warn("Empty control code encountered, skipping")
            else:
                command_strings[next_code] = next_data  # Store the code and its corresponding data substring
            
            # Strip the processed part of the string for the next iteration
            control_string = control_string[end_index + len(data_end_delimiter):]
            

        # Make sure there was valid data found in the command string
        if not command_strings:
            self.get_logger().error(f"Invalid control status message format: no valid command strings found")
            return None
        
        # Convert each piece of data into appropriate datatype and assign it to the corresponding field in the ControlFeedback message
        fields_and_types = control_data._fields_and_field_types
        data_parsed = False  # Flag to track if at least one piece of data was successfully parsed
        for next_code, next_data in command_strings.items():
            # Get the corresponding field name from the config file
            control_name = self.control_codes.get(next_code)
            # Make sure it is a valid control code form config file
            if not control_name:
                self.get_logger().warn(f"Unrecognized control code '{next_code}' in control status message; skipping this field")
                continue
            # Convert the value to the appropriate datatype based on the field type and assign it to the corresponding field in the ControlFeedback message
            try: 
                # Convert the value (from AI IDK if the format is right here)
                ros_type = fields_and_types.get(control_name, 'string')
                value = self.string_to_ros_type(next_data, ros_type)
                # Set the corresponding field in the ControlFeedback message
                setattr(control_data, control_name, value)
                data_parsed = True  # Set the flag to True if at least one piece of data was successfully parsed
            except Exception as e:
                self.get_logger().error(f"Error converting value for {control_name}: {e}")
                continue  # Skip this field but continue parsing others
            except ValueError as e:
                self.get_logger().error(f"Error parsing control status message for {control_name}: {e}")
                continue  # Skip this field but continue parsing others
        
        if not data_parsed:
            self.get_logger().warn("No valid data found in control status message")
            return None  # Return None if no valid data was parsed, otherwise return the ControlFeedback message
        
        return control_data


    # This function must be updated to handle each datatype possible in a message
    def string_to_ros_type(self, value_str, ros_type):
        try:
            if ros_type == 'boolean':
                return value_str.lower() in ['1', 'true']
            elif ros_type.startswith('int') or ros_type.startswith('uint'):
                return int(value_str)
            elif ros_type.startswith('float'):
                return float(value_str)
            elif ros_type == 'string':
                return value_str
            else:
                self.get_logger().warn(f"Unknown type '{ros_type}', treating as string")
                return value_str
        except Exception as e:
            self.get_logger().error(f"Failed to convert '{value_str}' to {ros_type}: {e}")
            return None


def main(args=None):
    rclpy.init(args=args)
    node = VehicleControlStringParser()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()