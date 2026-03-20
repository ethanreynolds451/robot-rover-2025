'''
Manages serial communication with control board
- Subscribes to control commands from other nodes and sends them to the control board
- Reads status updates from the control board and publishes them to status topic
- Does not parse data, just passes through as strings

Topics: 
 Subscribes to: 
- /vehicle/control_str
    - String messages containing control commands to send to the control board
 Publishes to: 
- /vehicle/control_status_str
    - String messages containing status updates read from the control board

Services: 
 Server for:
- /vehicle/control_serial_interface/reset
    - Resets the serial connection to the control board
- /vehicle/control_serial_interface/get_status
    - Returns the status of the serial connection
 Client for: 
- /vehicle/serial_manager/get_serial_port
    - Requests the serial port to use for communication with the control board
    - TODO implement service

Parameters: 
- serial_port (string, default: '/dev/ttyUSB0')
    - The serial port to use for communication with the control board
    - Will request from serial manager service
- serial_baudrate (int, default: 115200)
    - The baud rate for the serial connection
    - Set this in launch file 
- request_port (bool, default: true)
    - Use local parameter or request from serial manager service
'''

# Packages for serial / hardware interface
import serial

# Packages for ROS2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from urllib import response


class ControlSerialInterface(Node):
    def __init__(self):
        super().__init__('control_serial_interface')
        self.get_logger().info('Starting Control Serial Interface Node')
        # Set up subscriber to receive control commands from other nodes
        self.control_subscriber = self.create_subscription(String, '/vehicle/control_str', self.control_callback, 10)
        # Set up publisher to publish status updates from control board
        self.status_publisher = self.create_publisher(String, '/vehicle/control_status_str', 10)
        # Serial connection parameters
        self.declare_parameter('serial_port', '/dev/ttyUSB0')                                       # Default value for serial port parameter
        self.declare_parameter('request_port', True)                                                   # Whether to request port from serial manager service or use local parameter
        self.declare_parameter('serial_baudrate', 115200)                                              # Default value for serial baud rate parameter
        self.serial = None
        # Timer to periodically read from serial port and publish status updates
        self.create_timer(0.1, self.read_port) 
        # TODO add parameter fot timer period

    # Serial communication functions

    def get_port(self):
        if self.get_parameter('request_port').get_parameter_value().bool_value:
                # TODO implement service client to request port from serial manager
                self.get_logger().info('Requesting serial port from serial manager service')
                # For now, just use the local parameter as a placeholder
                port = self.get_parameter('serial_port').get_parameter_value().string_value
        else:
            port = self.get_parameter('serial_port').get_parameter_value().string_value
        return port


    def open_port(self):
        if not self.serial:
            # Get the latest serial port and baudrate parameters
            port = self.get_port()
            baudrate = self.get_parameter('serial_baudrate').get_parameter_value().integer_value
            # Attempt to open the serial port with error handling
            # Make sure the port is defined
            if port:
                try:
                    self.serial = serial.Serial(port, baudrate, timeout=1)
                    self.get_logger().info(f'Opened serial port {port} at baud rate {baudrate}')
                except serial.SerialException as e:
                    self.get_logger().error(f'Failed to open serial port {port}: {e}')
                    self.serial = None
            else:
                self.get_logger().error('Serial port not found')
    
    def close_port(self):
        if self.serial and self.serial.is_open:
            self.serial.close()
            self.get_logger().info(f'Closed serial port {self.port}')
            self.serial = None

    def read_port(self):
        if self.serial and self.serial.is_open:
            try:
                if self.serial.in_waiting > 0:
                    status_update = self.serial.readline().decode().strip()  # Read a line of data from the control board
                    if status_update:  # Only publish if we got a non-empty update
                        msg = String()
                        msg.data = status_update
                        self.status_callback(msg)  # Call the status callback to handle the update
            except serial.SerialException as e:
                self.get_logger().error(f'Failed to read from serial port with error: {e}')
                self.close_port()  # Close the port if error encountered
        else:
            self.get_logger().warning('Serial port is not open, attempting to open')
            self.open_port()  # Attempt to open the port

    
    # Searial interface functions

    def control_callback(self, msg):
        # Execute whenever a control command is recieved from annother node
        if self.serial and self.serial.is_open:
            try:
                self.serial.write(msg.data.encode())  # Send control command to control board
                self.get_logger().info(f'Sent control command to control board: {msg.data}')
            except serial.SerialException as e:
                self.get_logger().error(f'Failed to send control command with error: {e}')
        else: 
            self.get_logger().warning('Received control command but control board is not connected')
    
    def status_callback(self, msg):
        # Execute whenever a status update is recieved from the control board
        self.status_publisher.publish(msg)  # Publish status update to other nodes
        self.get_logger().info(f'Published status update from control board: {msg.data}')

    # Service callback functions

    def reset_serial(self, request, response):
        self.get_logger().info('Resetting serial connection to control board')
        self.close_port()
        self.open_port()
        return response

    def get_status(self, request, response):
        if self.serial and self.serial.is_open:
            response.status = 'connected'
        else:
            response.status = 'disconnected'
        return response

def main(args=None):
    rclpy.init(args=args)
    control_serial_interface = ControlSerialInterface()
    rclpy.spin(control_serial_interface)
    control_serial_interface.destroy_node()
    rclpy.shutdown()