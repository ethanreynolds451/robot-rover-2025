'''
This node parses string messages from the sensor board into SensorData messages for use by the rest of the system

Topics
 Subscribes to:
- /vehicle/sensor_data_str
    - String
 Publishes to:
- /vehicle/sensor_data
    - SensorData custom msg type

'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import SensorData
from std_msgs.msg import String

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml

class VehicleSensorStringParser(Node):
     def __init__(self):
        super().__init__('vehicle_sensor_string_parser')
        self.get_logger().info('Starting Vehicle Sensor String Parser Node')

        # Load sensor and delimiter codes once at startup