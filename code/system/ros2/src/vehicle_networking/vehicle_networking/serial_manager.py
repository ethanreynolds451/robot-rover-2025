'''
TODO: Fix this
cutors.py", line 118, in await_or_execute
    return callback(*args)
  File "/root/build/vehicle_networking/vehicle_networking/serial_manager.py", line 91, in check_devices
    for device_name, identifiers in device_identifiers.items():
'''


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
- Path to file with device identifiers (default to current directory)
- Timer interval to check ports (default 5 seconds)

'''

# Packages for serial / hardware interface
import serial                       # For serial communication
import serial.tools.list_ports      # To get the ports and information
import json                         # For reading the device identifiers

# ROS2 service definitions
from vehicle_networking_interfaces.srv import GetSerialPort, ResetSerialPort

# Packages for ROS2
import rclpy
from rclpy.node import Node

class SerialManager(Node):
    def __init__(self): 
        super().__init__('serial_manager')
        self.get_logger().info('Starting Serial Manager Node')
        # Set up services to manage serial port information
        self.get_port_service = self.create_service(GetSerialPort, '/vehicle/serial_manager/get_serial_port', self.get_serial_port)
            # Only returns the port, uses string for simplicity
        self.reset_port_service = self.create_service(ResetSerialPort, '/vehicle/serial_manager/reset_serial_port', self.reset_serial_port)
        # Parameters for serial port searching
            # self.declare_parameter('search_paths', ['/dev/ttyUSB*', '/dev/ttyACM*'])  # Paths to search for serial devices
            # Probably wont need this but keeping as parameter in case needed to modify in future
        self.declare_parameter('device_identifiers_file', 'device_identifiers.json')  # File with device identifiers
            # Identifier file in same directory, may move to dedicated directory for config files later 
        # Cache for found serial ports (device name : port)
        self.serial_ports = {}
        # Timer to periodically check for device changes
        self.declare_parameter('check_interval', 5.0)  # Interval in seconds
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
        # Implementation for checking device changes
        ports = serial.tools.list_ports.comports()
        # First, check for disconnected devices
        for device, port in list(self.serial_ports.items()):
            if port not in [p.device for p in ports]:
                self.get_logger().info(f'Device {device} disconnected (port {port} not found)')
                # Remove the cached port for this device
                del self.serial_ports[device]
        # Next, check for new devices
        # Load the file with device identifiers
        device_identifiers = {}
        try:
            with open(self.get_parameter('device_identifiers_file').get_parameter_value().string_value, 'r') as f:
                device_identifiers = json.load(f)
        except Exception as e:
            self.get_logger().error(f'Error loading device identifiers file: {e}')
        if device_identifiers:
            for port in ports:
                if port.device not in self.serial_ports.values():
                    self.get_logger().info(f'New device detected: {port.device} ({port.description})')
                    # Attempt to match the new device to an identifier in the file
                    for device_name, identifiers in device_identifiers.items():
                        if (identifiers.get('vid') == port.vid and 
                                identifiers.get('pid') == port.pid and
                                identifiers.get('manufacturer') == port.manufacturer and
                                identifiers.get('product') == port.product):
                            self.serial_ports[device_name] = port.device
                            self.get_logger().info(f'Identified device {device_name} at port {port.device}')
                        else: 
                            self.get_logger().info(f'Could not identify device at port {port.device} (VID: {port.vid}, PID: {port.pid}, Manufacturer: {port.manufacturer}, Product: {port.product})')


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
            self.get_logger().info(f'Found serial port for device {device}: {response.port}')
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