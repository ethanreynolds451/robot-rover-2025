'''
Finds the serial port for communication with a given device
Will search through /dev for devices matching certain criteria to find the correct port
Saves found port in cach for future lookups
Must be told when to reset saved port and re-search

Uses a timer to check serial ports: 
- if a new device is plugged in, it will attempt to identify it
- if a device is unplugged (port no longer found), it will reset the cached port

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
- Timer interval to check ports (default 5 seconds)

'''

# Packages for serial / hardware interface
import serial                       # For serial communication
import serial.tools.list_ports      # To get the ports and information

# ROS2 service definitions
from vehicle_interfaces.srv import GetSerialPort, ResetSerialPort

# Packages for ROS2
import rclpy
from rclpy.node import Node

# Get device identifiers from config files
import os
from ament_index_python.packages import get_package_share_directory
import json                         # For reading the device identifiers


class SerialManager(Node):
    def __init__(self): 
        super().__init__('serial_manager')
        self.get_logger().info('Starting Serial Manager Node')

        # First attempt to load device identifier file to ensure it is available before starting the node
        self.device_identifiers = {}
        package_share = get_package_share_directory('vehicle_networking')
        device_identifiers_file = os.path.join(package_share, 'config', 'device_identifiers.json')
        try:
            with open(device_identifiers_file, 'r') as f:
                self.device_identifiers = json.load(f)
                self.get_logger().info(f'Successfully loaded device identifiers')
        except Exception as e:
            self.get_logger().error(f'Error loading device identifiers file: {e}')
            # Shut down the node if the device identifiers can't be loaded
            rclpy.shutdown()
            return

        # Set up services to manage serial port information
        self.get_port_service = self.create_service(GetSerialPort, '/vehicle/serial_manager/get_serial_port', self.get_serial_port)
            # Only returns the port, uses string for simplicity
        self.reset_port_service = self.create_service(ResetSerialPort, '/vehicle/serial_manager/reset_serial_port', self.reset_serial_port)
        # Parameters for serial port searching
            # self.declare_parameter('search_paths', ['/dev/ttyUSB*', '/dev/ttyACM*'])  # Paths to search for serial devices
            # Probably wont need this but keeping as parameter in case needed to modify in future
        # Cache for found serial ports (device name : port)
        self.serial_ports = {}
        # Timer to periodically check for device changes
        self.declare_parameter('check_interval', 1.0)  # Interval in seconds
        self.create_timer(self.get_parameter('check_interval').get_parameter_value().double_value, self.check_devices)

    def reset_serial_port(self, request, response):
        # Clear the cached serial port for a specific device
        device = request.device
        if device in self.serial_ports:
            del self.serial_ports[device]
            self.get_logger().info(f'Reset cached serial port for device: {device}')
        else:
            self.get_logger().info(f'No cached serial port to reset for device: {device}')
        return response

    def check_devices(self):
        # Debug: check values for saved ports
        # self.get_logger().info(f'Current cached serial ports: {self.serial_ports}')
        # Implementation for checking device changes
    # 1) Get available USB devices and their information
        all_ports = serial.tools.list_ports.comports()
        # Debug: not finding devices
        # self.get_logger().info(f'Checking for serial devices... Found {len(all_ports)} total ports')
        # Filter out invalid ports
        ports = []
        for port in all_ports:
            if port.vid:        # Exclude ports that don't have a VID (e.g. built-in serial ports, bluetooth, wifi, etc.)
                ports.append(port)
        for port in ports:
            # Debuggin
            # self.get_logger().info(f'Cached ports: {self.serial_ports}')
            if port.device not in self.serial_ports.values():  # Only log new ports that are not already cached
                self.get_logger().info(f'Found serial port: {port.device} (Description: {port.description}, VID: {port.vid}, PID: {port.pid}, Manufacturer: {port.manufacturer}, Product: {port.product})')
    # 2) Check for disconnected devices
        devices = list(self.serial_ports.items())  # Create a list of items to avoid dictionary size change during iteration
        for device, port in devices:
            if port not in [p.device for p in ports]:
                self.get_logger().info(f'Device {device} disconnected (port {port} not found)')
                # Remove the cached port for this device
                del self.serial_ports[device]
    # 3) Check for new devices and attempt to identify them
        if self.device_identifiers:
            for port in ports:
                if port.device not in self.serial_ports.values():
                    # Exclude invalid devices that don't have a VID (e.g. bluetooth, wifi, etc.)
                    self.get_logger().info(f'New device detected: {port.device} ({port.description})')
                    # Attempt to match the new device to an identifier in the file
                    identified = False
                    for device in device_identifiers:
                        device_name = device["name"]
                        vid = device["vid"]
                        pid = device["pid"]
                        manufacturer = device["manufacturer"]
                        product = device["product"]
                        self.get_logger().info(f'Checking if device {port.device} matches identifier for {device_name} (VID: {vid}, PID: {pid}, Manufacturer: {manufacturer}, Product: {product})')
                        if (vid == port.vid and 
                                pid == port.pid and
                                manufacturer == port.manufacturer and
                                product == port.product):
                            self.serial_ports[device_name] = port.device
                            self.get_logger().info(f'Identified device {device_name} at port {port.device}')
                            identified = True
                            break  # Stop checking other identifiers once a match is found                    
                    if not identified: 
                        self.get_logger().info(f'Could not identify device at port {port.device} (VID: {port.vid}, PID: {port.pid}, Manufacturer: {port.manufacturer}, Product: {port.product})')
        else:
            self.get_logger().error('No device identifiers available, unable to identify new devices')    


    # This returns the serial port for a specific device or empty if device is not found
    def get_serial_port(self, request, response): 
        device = request.device
        # Check if there is already a cached device
        if device in self.serial_ports:
            response.port = self.serial_ports[device]
            self.get_logger().info(f'Returning cached serial port for device {device}: {response.port}')
            return response
        # If not cached, check if the device is currently connected
        self.check_devices()  # Update the device list before checking
        if device in self.serial_ports:
            response.port = self.serial_ports[device]
            self.get_logger().info(f'Found new serial port for device {device}: {response.port}')
        else:
            response.port = ''
            self.get_logger().info(f'Serial port for device {device} not found')
        return response


def main(args=None):
    rclpy.init(args=args)
    serial_manager = SerialManager()
    rclpy.spin(serial_manager)
    serial_manager.destroy_node()
    rclpy.shutdown()