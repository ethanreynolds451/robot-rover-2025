''' 
This node converts vehicle control mesages to string format for sending over serial
Important note: this DOES NOT ensure that packets are less than 64 bytes - they must be broken up by the packet manager

Topics
 Subscribes to:
- /vehicle/control
    - ControlData custom msg type
 Publishes to:
- /vehicle/control_str
    - String

Parameters: 
- verbose (bool, default: false)
    - Whether to log all constructed strings in the console
    - Useful for debugging but a lot of clutter / overhead for normal operation
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


class VehicleControlStringBuilder(Node):
    def __init__(self):
        super().__init__('vehicle_control_string_builder')
        self.get_logger().info('Starting Vehicle Control String Builder Node')

        # Expected execution parameters
        self.declare_parameter('verbose', False)  # Whether to log all constructed strings in the console

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
        self.control_subscriber = self.create_subscription(ControlData, '/vehicle/control', self.control_callback, 10)
        # Publisher for string formatted control messages
        self.control_string_publisher = self.create_publisher(String, '/vehicle/control_str', 10)



    def control_callback(self, msg):
        # Convert the ControlData message to a string format
        control_string = self.convert(msg)
        # Publish the string message
        if control_string:  # Only publish if conversion was successful
            str_msg = String()
            str_msg.data = control_string
            self.control_string_publisher.publish(str_msg)
            if self.get_parameter('verbose').get_parameter_value().bool_value:
                self.get_logger().info(f"Published control string: {control_string}")
        else:
            self.get_logger().error("Failed to convert control message to string format")


    def convert(self, control_msg):
        control_string = ""       # String to be returned
        # Convert the ControlData message to a string format
        
        # First add the start packet delimiter
        control_string += self.delimiters.get('packet_start', '')

        # Then go through the control message and add corresponding codes and values
        
        # Iterate through each valid command field
        # Note: field names must match in both places!
        for field, code in self.control_codes.items(): 
            try:
                value = getattr(control_msg, field)  # Get the value from the message using the field name
                # Handle bool objects by converting to 1 or 0
                if isinstance(value, bool):
                    value = '1' if value else '0'

                # Will always send all commands, may need to change this in future if more complex data is added to command stream
                # For now this method makes logic simpler and provides redundancy without adding significantly more processing delay
                code = self.control_codes.get(field, None)  # Get the corresponding code for the field
                if code:  # Only add to string if a code exists for the field
                    control_string += code                                      # Add the code
                    control_string += self.delimiters.get('field_start', '')    # Add the field start delimiter
                    control_string += str(value)                                # Add the value
                    control_string += self.delimiters.get('field_end', '')      # Add field end delimiter
            except Exception as e:
                self.get_logger().error(f"Error processing control message field '{field}': {e}")
                continue  # Skip this field and continue with the next one

        # Finally add the end packet delimiter
        control_string += self.delimiters.get('packet_end', '')

        return control_string

def main(args=None):
    rclpy.init(args=args)
    vehicle_control_string_builder = VehicleControlStringBuilder()
    rclpy.spin(vehicle_control_string_builder)
    vehicle_control_string_builder.destroy_node()
    rclpy.shutdown()