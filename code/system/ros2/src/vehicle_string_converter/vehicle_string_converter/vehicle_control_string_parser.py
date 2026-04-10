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
        if not control_string.startswith(self.delimiters.get('packet_start', '')) and not control_string.endswith(self.delimiters.get('packet_end', '')):
            self.get_logger().error(f"Invalid control status message recieved: missing start/end delimiter")
            return None

        # If valid, extract data from the string
        for control_name, code in self.control_codes.items():
            if code in control_string:
                # do stuff

        # Discard any invalid messages that do not match the expected formatÁDFCLÑ