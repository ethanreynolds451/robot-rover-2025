'''
Finds the serial port for communication with a given device
Will search through /dev for devices matching certain criteria to find the correct port
Saves found port in cach for future lookups
Must be told when to reset saved port and re-search

Services: 
 Server for: 
- /vehicle/serial_manager/get_serial_port
    - Requests the serial port to use for communication with a specific device
    - Expects a string argument specifying the device (e.g. 'control_board')
    - Returns a string with the serial port (e.g. '/dev/ttyUSB0') or none if not found
    - Uses saved cache to return port if already found
- /vehicle/serial_manager/reset_serial_port
    - Resets the cached serial port information (e.g. if device was unplugged and replugged)

Parameters: 
- Paths to search for serial devices (e.g. '/dev/ttyUSB*')
- Path to file with device identifiers (default to current directory)

'''

# Packages for serial / hardware interface
import serial

# Packages for ROS2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from urllib import response

class SerialManager(Node):
    def __init__(self): 
        super().__init__('serial_manager')
        self.get_logger().info('Starting Serial Manager Node')
        # Set up services to manage serial port information
        self.get_port_service = self.create_service(GetSerialPort, '/vehicle/serial_manager/get_serial_port', self.get_serial_port)
        self.reset_port_service = self.create_service(Empty, '/vehicle/serial_manager/reset_serial_port', self.reset_serial_port)
        # Parameters for serial port searching
        self.declare_parameter('search_paths', ['/dev/ttyUSB*', '/dev/ttyACM*'])  # Paths to search for serial devices
        self.declare_parameter('device_identifiers_file', 'device_identifiers.txt')  # File with device identifiers
        # Cache for found serial ports
        self.serial_ports = {}

