'''
This node parses string messages from the control board into ControlData messages for use by the rest of the system

Topics
 Subscribes to:
- /vehicle/control_status_str
    - String
 Publishes to:
- /vehicle/control_status
    - ControlData custom msg type

'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import ControlData
from std_msgs.msg import String

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml


class VehicleControlStringParser(Node):
    def __init__(self):
        super().__init__('vehicle_control_string_parser')
        self.get_logger().info('Starting Vehicle Control String Parser Node')

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

        # Subscriber to vehicle control messages
        self.control_subscriber = self.create_subscription(String, '/vehicle/control_status_str', self.control_callback, 10)
        # Publisher for string formatted control messages
        self.control_string_publisher = self.create_publisher(ControlData, '/vehicle/control_status', 10)


    def control_callback(self, msg):
        # Convert the string message to a ControlData message
        control_data = self.convert(msg)
        # Publish the ControlData message
        if control_data:  # Only publish if conversion was successful
            self.control_string_publisher.publish(control_data)
            self.get_logger().info(f"Published control status update: {control_data}")
        else:
            self.get_logger().error("Failed to convert control status message to ControlData format")


    def convert(self, msg):
        # Declare output type ControlData
        control_data = ControlData()
        # Get the string from the incoming message
        control_string = msg.data

        # First, check for valid packet delimiters
        start_delimiter = self.delimiters.get('packet_start', '')
        end_delimiter = self.delimiters.get('packet_end', '')
        # Makes sure delimiters aren't empty to avoid edge case
        if start_delimiter and end_delimiter:
            if not control_string.startswith(self.delimiters.get('packet_start', '')) or not control_string.endswith(self.delimiters.get('packet_end', '')):
                self.get_logger().error(f"Invalid control status message recieved: missing start/end delimiter")
                return None
        else:
            self.get_logger().error("Packet delimiters not defined in config files; unable to validate incoming messages")
            return None

        # If valid, extract data from the string
        for control_name, code in self.control_codes.items():
            if code in control_string:
                # Extract the data from between the data delimiters
                try:
                    # The index of the start data delimiter
                    start_index = control_string.index(code) + len(code)
                    # Starting at this index, look for the first instance of the end delimiter
                    end_index = control_string.index(self.delimiters.get('data_end', ''), start_index)
                    
                    # Validate both delimiters before attempting to extract data
                    if control_string[end_index:end_index + len(self.delimiters.get('data_end', ''))] != self.delimiters.get('data_end', '') or control_string[start_index:start_index + len(self.delimiters.get('data_start', ''))] != self.delimiters.get('data_start', ''):
                        self.get_logger().error(f"Invalid control status message format for {control_name}: missing data delimiters")
                        continue  # Skip this field but continue parsing others
                    
                    # Extract the value as a string
                    data_start_index = start_index + len(self.delimiters.get('data_start', ''))
                    data_end_index = end_index          # End-exclusive slicing in Python
                    value_substring = control_string[data_start_index:data_end_index]
                    
                    # Convert the value to the appropriate type based on the control field
                    try: 
                        value = self.string_to_ros_type(value_substring, self.control_codes.get(control_name + '_type', 'string'))  # Default to string type if not specified
                        # Set the corresponding field in the ControlData message
                        setattr(control_data, control_name, value)
                    except Exception as e:
                        self.get_logger().error(f"Error converting value for {control_name}: {e}")
                        continue  # Skip this field but continue parsing others

                except ValueError as e:
                    self.get_logger().error(f"Error parsing control status message for {control_name}: {e}")
                    continue  # Skip this field but continue parsing others

        return control_data


    # This function must be updated to handle each datatype possible in a message
    def string_to_ros_type(self, value_str, ros_type):
        try:
            if ros_type == 'boolean':
                return value_str in ['1', 'true', 'True']
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