''' 
This node converts vehicle control mesages to string format for sending over serial
Important note: this DOES NOT ensure that packets are less than 64 bytes - they must be broken up by the serial manager

Topics
 Subscribes to:
- /vehicle/control
 Publishes to:
- /vehicle/control_str

'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import VehicleControl
from std_msgs.msg import String

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml


class VehicleControlStringBuilder(Node):
    def __init__(self):
        super().__init__('vehicle_control_string_builder')
        self.get_logger().info('Starting Vehicle Control String Builder Node')
        # Subscriber to vehicle control messages
        self.control_subscriber = self.create_subscription(VehicleControl, '/vehicle/control', self.control_callback, 10)
        # Publisher for string formatted control messages
        self.control_string_publisher = self.create_publisher(String, '/vehicle/control_str', 10)

        # Load control and delimiter codes once at startup
        package_share = get_package_share_directory('vehicle_string_converter')
        control_config_path = os.path.join(package_share, 'config', 'control_codes.yaml')
        delimiter_config_path = os.path.join(package_share, 'config', 'delimiters.yaml')
        self.control_codes = {}
        self.delimiters = {}
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


    def control_callback(self, msg):
        # Convert the VehicleControl message to a string format
        control_str = self.convert(msg)
        # Publish the string message
        if control_str:  # Only publish if conversion was successful
            str_msg = String()
            str_msg.data = control_str
            self.control_string_publisher.publish(str_msg)
            self.get_logger().info(f"Published control string: {control_str}")

    # Do later
    def convert(self, control_msg):
        str = ""       # String to be returned
        # Convert the VehicleControl message to a string format
        # First add the start packet delimiter
        str = str + self.delimiters.get('start', '')
        # Then go through the control message and add corresponding codes and values
        for field in control_msg.__slots__:  # Iterate through each field in the message
            value = getattr(control_msg, field)  # Get the value of the field
            # Will always send all commands, may need to change this in future if more complex data is added to command stream
            # For now this method makes logic simpler and provides redundancy without adding significantly more processing delay
            code = self.control_codes.get(field, None)  # Get the corresponding code for the field
            if code:  # Only add to string if a code exists for the field
                str = str + code + str(value)  # Add the code and value to the string
            else:
                self.get_logger().warning(f"No control code found for field '{field}', skipping this field.")
        # Finally add the end packet delimiter
        str = str + self.delimiters.get('end', '')
        return str
    


def main(args=None):
    rclpy.init(args=args)
    vehicle_control_string_builder = VehicleControlStringBuilder()
    rclpy.spin(vehicle_control_string_builder)
    vehicle_control_string_builder.destroy_node()
    rclpy.shutdown()