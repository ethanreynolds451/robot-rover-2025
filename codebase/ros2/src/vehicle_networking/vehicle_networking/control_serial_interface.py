'''
Manages serial communication with control board
- Subscribes to control commands from other nodes and sends them to the control board
- Reads status updates from the control board and publishes them to status topic
- Does not parse data, just passes through as strings

*** When run in nopacket mode ***

This version subdscibes and publishes as raw strings instead of passinag through the 
serial packet manager. Use this for tests that bypass the packet manager.
Must be use with control board code that uses raw strings, not packets.
Waning: sending and recieving strings greater than 64 bytes may cause issues with the arduino 

Topics: 
 Subscribes to: 
- /vehicle/control_str
    - String messages containing control commands to send to the control board
 Publishes to: 
- /vehicle/control_status_str
    - String messages containing status updates read from the control board

*** When run in packet mode ***

NOT YET IMPLEMENTED

Topics: 
 Subscribes to: 
- /vehicle/control_packets
    - String messages containing packetized control commands to send to the control board
 Publishes to: 
- /vehicle/control_status_packets
    - String messages containing packetized status updates read from the control board

***

Services: 
 Server for:
- /vehicle/control_serial_interface/reset
    - Resets the serial connection to the control board
- /vehicle/control_serial_interface/get_status
    - Returns the status of the serial connection
- /vehicle/control_serial_interface/set_active
    - Activates or deactivates the serial interface
 Client for: 
- /vehicle/serial_manager/get_serial_port
    - Requests the serial port to use for communication with the control board

Parameters: 
- packet_mode (bool, default: true)
- verbose (bool, default: false)
    - Whether to log all commands and status updates in the console, or just log connection status
    - Useful for debugging but a lot of clutter / overhead for normal operation
- serial_port (string, default: '')
    - The serial port to use for communication with the control board
    - Will request from serial manager service if request_port parameter is true
- serial_baudrate (int, default: 115200)
    - The baud rate for the serial connection
    - Set this in launch file 
- request_port (bool, default: true)
    - Use local parameter or request from serial manager service
- active (bool, default: true)
    - Allows serial interface to be deactivated when not needed
- read_interval (double, default: 0.1)
    - Interval in seconds to read from serial port
- port_check_interval (double, default: 3.0)
    - Interval in seconds to check and open serial port if not connected
- port_timeout (double, default: 3.0)
    - Timeout in seconds for waiting for serial port from serial manager service
'''

# Packages for serial / hardware interface
import serial

# Packages for ROS2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from urllib import request, response

# Services
from std_srvs.srv import Empty
from std_srvs.srv import SetBool
from vehicle_interfaces.srv import GetSerialDeviceStatus, GetSerialPort

class ControlSerialInterface(Node):
    def __init__(self):
        super().__init__('control_serial_interface')
        self.get_logger().info('control_serial_interface : initialization started')
        # Expected command line parameters
        self.declare_parameter('packet_mode', True)  # Whether to use packet manager or pass through raw strings
        if self.get_parameter('packet_mode').get_parameter_value().bool_value:
            self.get_logger().info('Starting Control Serial Interface Node in Packet Mode')
        else:
            self.get_logger().info('Starting Control Serial Interface Node in Raw String Mode')
        
        # Set back to string mode if attemspting to use packet mode
        if self.get_parameter('packet_mode').get_parameter_value().bool_value:
            self.get_logger().warning('Packet mode is not yet implemented, defaulting to raw string mode')
            self.set_parameters([rclpy.parameter.Parameter('packet_mode', rclpy.Parameter.Type.BOOL, False)])    

        self.declare_parameter('verbose', False)  # Default to suppress repeat of commands and status updates in logs, set to true to log all commands and updates

        # Set up subscriber to receive control commands from other nodes
        self.control_subscriber = self.create_subscription(String, '/vehicle/control_str', self.control_callback, 10)
        # Set up publisher to publish status updates from control board
        self.status_publisher = self.create_publisher(String, '/vehicle/control_status_str', 10)
        # Debug
        # self.get_logger().info('Topics intitialized')
        # Set up services to manage serial connection
        self.reset_service = self.create_service(Empty, '/vehicle/control_serial_interface/reset', self.reset_serial)
        self.get_status_service = self.create_service(GetSerialDeviceStatus, '/vehicle/control_serial_interface/get_status', self.get_status)
        self.set_active_service = self.create_service(SetBool, '/vehicle/control_serial_interface/set_active', self.set_active)
        # Debug
        # self.get_logger().info('Serial services intitialized')
        # Set up client to request serial port form serial manager
        self.get_port_client= self.create_client(GetSerialPort, '/vehicle/serial_manager/get_serial_port')
        # Serial connection parameters
        self.declare_parameter('active', True)                                                   # Whether the serial interface is active and should attempt to connect
        self.declare_parameter('serial_port', '')                                       # Default value for serial port parameter
        self.declare_parameter('request_port', True)                                                   # Whether to request port from serial manager service or use local parameter
        self.declare_parameter('serial_baudrate', 115200)                                              # Default value for serial baud rate parameter
        self.serial = None
        self.port = None
        self.baudrate = None
        # Debug
        # self.get_logger().info('Serial parameters intitialized')
        # Timer to periodically read from serial port and publish status updates
        self.declare_parameter('read_interval', 0.1)  # Interval in seconds to read from serial port
        self.declare_parameter('port_check_interval', 3.0)  # Interval in seconds to check and open serial port
        self.create_timer(self.get_parameter('read_interval').get_parameter_value().double_value, self.read_port) 
        self.create_timer(self.get_parameter('port_check_interval').get_parameter_value().double_value, self.check_connection)
        self.declare_parameter('port_timeout', 3.0)  # Timeout in seconds for waiting for serial port from serial manager
        
        self.get_logger().info('control_serial_interface : initialization successful')

    # Serial communication functions

    def get_port(self):
        if not self.port:
            self.get_logger().info('No serial port defined for control board, attempting to acquire port')
            if self.get_parameter('request_port').get_parameter_value().bool_value:
                if not self.get_port_client.wait_for_service(timeout_sec=1.0):
                    self.get_logger().error('Serial manager service not available')
                    return
                self.get_logger().info('Requesting serial port from serial manager service')
                request = GetSerialPort.Request()
                request.device = "control board"  
                # Request the port with a timeout
                future = self.get_port_client.call_async(request)
                future.add_done_callback(self.handle_port_response)
                return
            else:
                self.port = self.get_parameter('serial_port').get_parameter_value().string_value
                self.get_logger().info(f'Using serial port from parameter: {self.port}')
                    
    def handle_port_response(self, future):
        try:
            response = future.result()
            self.port = response.port
            if self.port:
                self.get_logger().info(f'Received serial port: {self.port}')
            else:
                self.get_logger().error('Control board not identified')
        except Exception as e:
            self.get_logger().error(f'Service call failed: {e}')
            self.port = None           


    def open_port(self):
        if self.port: 
            self.get_logger().info('Attempting to open serial port for control board')
            # Get the latest serial port and baudrate values
            self.baudrate = self.get_parameter('serial_baudrate').get_parameter_value().integer_value
                # May change this later to allow for changes without reseting default parameter
            # Attempt to open the serial port with error handling
            # Make sure the port is defined 
            try:
                self.serial = serial.Serial(self.port, self.baudrate, timeout=1)
                self.get_logger().info(f'Opened serial port {self.port} at baud rate {self.baudrate}')
            except serial.SerialException as e:
                self.get_logger().error(f'Failed to open serial port {self.port} with error: {e}')
                self.serial = None
        else:
            self.get_logger().error('No port defined for control board, cannot open serial connection')
        
    def close_port(self):
        if self.serial:
            self.serial.close()
            self.get_logger().info(f'Closed serial port {self.port}')
            self.serial = None 

    def check_connection(self):
        if self.get_parameter('active').get_parameter_value().bool_value:
            if not self.serial or not self.serial.is_open:
                self.get_logger().warning('Control board serial port is not open, attempting to open')
                self.get_port()
                self.open_port()
        else:
            if self.serial and self.serial.is_open:
                self.get_logger().info('Control board serial interface deactivated, closing serial port')
                self.close_port()

    def read_port(self):
        if self.serial and self.get_parameter('active').get_parameter_value().bool_value:
            try:
                if self.serial.in_waiting > 0:
                    status_update = self.serial.readline().decode().strip()  # Read a line of data from the control board
                    if status_update:  # Only publish if we got a non-empty update
                        msg = String()
                        msg.data = status_update
                        self.status_callback(msg)  # Call the status callback to handle the update
                        if self.get_parameter('verbose').get_parameter_value().bool_value:
                            self.get_logger().info(f'Read status update from control board: {status_update}')
            except serial.SerialException as e:
                self.get_logger().error(f'Failed to read from serial port with error: {e}')
                self.close_port()  # Close the port if error encountered
        
    # Serial interface functions

    def control_callback(self, msg):
        # Execute whenever a control command is recieved from annother node
        if self.get_parameter('active').get_parameter_value().bool_value:
            if self.serial:
                try:
                    self.serial.write(msg.data.encode())  # Send control command to control board
                    if self.get_parameter('verbose').get_parameter_value().bool_value:
                        self.get_logger().info(f'Sent command to control board: {msg.data}')
                except serial.SerialException as e:
                    self.get_logger().error(f'Failed to send control command with error: {e}')
                    self.close_port()  # Close the port if error encountered
            else: 
                self.get_logger().warning('Received control command but control board is not connected')
    
    def status_callback(self, msg):
        # Execute whenever a status update is recieved from the control board
        self.status_publisher.publish(msg)  # Publish status update to other nodes
        if self.get_parameter('verbose').get_parameter_value().bool_value:
            self.get_logger().info(f'Recieved status update from control board: {msg.data}')

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

    def set_active(self, request, response):
        self.get_logger().info(f'Setting serial interface active to: {request.active}')
        self.set_parameter('active', request.active)
        response.success = True
        return response


def main(args=None):
    rclpy.init(args=args)
    control_serial_interface = ControlSerialInterface()
    rclpy.spin(control_serial_interface) 
    control_serial_interface.destroy_node()
    rclpy.shutdown()