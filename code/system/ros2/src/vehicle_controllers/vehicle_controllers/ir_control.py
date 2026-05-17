'''
Controller to allow the vehicle to be controlled with an IR remote control
Used for testing and demo

Note: this bypasses the data manager layer, directly interfacing with the raw data and commands
May pass through these layers once they are implemented for rigerous validity checking, but not needed for basic control

Since the commands are immediately executed without validation, no ROS timestamp is included for control packets

Run requirements:
- vehicle_networking/serial_manager
- vehicle_networking/control_serial_interface
- vehicle_networking/sensor_serial_interface
- vehicle_string_converter/vehicle_control_string_builder
- vehicle_string_converter/vehicle_sensor_string_builder
If running in packet mode, also requires:
- vehicle_packet_manager/inbound_packet_manager
- vehicle_packet_manager/outbound_packet_manager

Topics
 Subscribes to:
- /vehicle/sensor_data
    - SensorData custom msg type
 Publishes to:
- /vehicle/control_data
    - ControlData custom msg type

Parameters
- verbose (bool): Whether to log all parsed data in the console; default False
'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import ControlData, SensorData

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml

class IRRemoteController(Node):
    def __init__(self):
        super().__init__('ir_control')
        self.get_logger().info('Starting IR Remote Controller Node')

        # Expected execution parameters
        self.declare_parameter('verbose', False)  # Whether to log all parsed data in the console

        # Load codes, delimiters, internalh fields, and special encoding parameters once at startup
        package_share = get_package_share_directory('vehicle_controllers')
        ir_config_path = os.path.join(package_share, 'config', 'ir_commands.yaml')
        control_defaults_path = os.path.join(package_share, 'config', 'control_defaults.yaml')

        try:
            with open(ir_config_path, 'r') as f:
                self.ir_commands = yaml.safe_load(f)
            with open(control_defaults_path, 'r') as f:
                self.control_defaults = yaml.safe_load(f)
                # Convert any command and data values into lists 
                for command_name, command_mapping in self.ir_commands.items():
                    for address, params in command_mapping.items():
                        if 'command' in params and not isinstance(params['command'], list):
                            params['command'] = [params['command']]
                        if 'data' in params and not isinstance(params['data'], list):
                            params['data'] = [params['data']]
        except Exception as e:
            self.get_logger().error(f"Error loading IR config file: {e}")
            raise

        except Exception as e:
            # The control system can't run without the codes, but sensors can still run
            self.get_logger().error(
                f"Error loading sensor files; system will be unable to interface with sensor board: {e}"
            )
            raise  # Re-raise so main() knows initialization failed

        self.get_logger().info("Successfully loaded IR command configurations and control defaults")

        # Create subscriber to raw sensor data
        self.sensor_subscriber = self.create_subscription(
            SensorData,
            '/vehicle/sensor_data',
            self.sensor_callback,
            10
        )

        # Create publisher to control data
        self.control_string_publisher = self.create_publisher(
            ControlData,
            '/vehicle/control_data',
            10
        )

        # Create internal variables to store states to construct control commands
        # Allows preserving, incrementing, and decrementing
        self.control_states = {}
        self.previous_control_states = {}
        self.hold_speed = False

        # Create timer to reset if commands are not held
        self.create_timer(0.5, self.timeout_callback)


    def sensor_callback(self, msg):
        # When a new sensor message is recieved, process it
        # msg is a SensorData message
        # Extract the IR data field since that's all that matters here
        ir_field = msg.ir_remote[0]  # Assuming only one IR remote data field, adjust if multiple fields are possible
        # First check if it contains valid IR remote data
        if not self.is_valid_ir_data(ir_field):
            self.get_logger().debug(f"Received sensor packet without valid IR data: {msg.data}")
            return  # Ignore non-IR data
        
        # If there is valid IR data, extract it and check if it matches known commands
        # The same command may trigger more than one action, so loop through and make a list
        ir_address = ir_field.address
        ir_command = ir_field.command
        ir_data = ir_field.data

        commands_to_execute = []
        for command_name, command_mapping in self.ir_commands.items():
            # Command name is the name of the command
            # Command mapping is a dict that maps addresses to command and data values

            # First check if the address matches or if command does not depend on address
            addresses = command_mapping.keys()
            # Check for commands that can be triggered by any address
            if 'any' in addresses:
                # Using nested if statements to avoid key error for optional fields
                # Use in to handle lists for multi mappìng
                if 'command' in command_mapping['any']:
                    if ir_command in command_mapping['any']['command']:
                        commands_to_execute.append(command_name)
                elif 'data' in command_mapping['any']:
                    if ir_data in command_mapping['any']['data']:
                        commands_to_execute.append(command_name)
            # Check for commands that can only be triggered by a specific address
            if ir_address in addresses:
                # This command depends on a specific address, so check if the command and data match
                if 'command' in command_mapping[ir_address]:
                    if ir_command in command_mapping[ir_address]['command']:
                        commands_to_execute.append(command_name)
                elif 'data' in command_mapping[ir_address]:
                    if ir_data in command_mapping[ir_address]['data']:
                        commands_to_execute.append(command_name)

        if not commands_to_execute:
            self.get_logger().warn(f"Received unrecognized IR command: address {ir_address}, command {ir_command}, data {ir_data}")
            return  # No matching command, ignore
        else:
            if self.get_parameter('verbose').get_parameter_value().bool_value:
                self.get_logger().info(f"Received IR command: address {ir_address}, command {ir_command}, data {ir_data} -> executing commands: {commands_to_execute}")
        self.execute_commands(commands_to_execute)

    def is_valid_ir_data(self, ir_field):
        # Check if the data contains valid IR remote data based on the loaded codes
        # Extract the field from the SensorData message
        if not ir_field:
            return False  # No IR data field or empty list, ignore
        # Check if there is remote control data in the field
        if ir_field.command is None and ir_field.data is None:
            # No control data was recieved from the remote, ignore 
            return False 
        return True
        
    def execute_commands(self, commands):
        self.previous_control_states = self.control_states.copy()  # Store the current states before executing new commands

        # Execute the given list of commands by publishing the corresponding control data
        for command in commands:
            if command == 'ignore':
                if self.get_parameter('verbose').get_parameter_value().bool_value:
                    self.get_logger().info(f"Ignoring command: {command}")
                continue  # This command is meant to be ignored, so skip it
            # Speed control commands
            elif command.startswith('set_speed_'):
                speed_value = int(command.split('_')[-1])  # Extract the speed value from the command name
                self.control_states['drive_power'] = speed_value  # Update the internal state
            elif command.startswith('increment_speed_'):
                params = command.split('_')[-1]  # Extract the increment amount from the command name
                amount = int(params.split('-')[-1])  # Extract the increment amount from the command name
                direction = params.split('-')[0]  # Extract the increment direction (up or down) from the command name
                if direction == 'down':
                    amount = -amount  # Negate the amount for decrementing
                current_speed = self.control_states.get('drive_power', self.control_defaults['drive_power'])
                self.control_states['drive_power'] = current_speed + amount  # Increment speed by the specified amount

            # Direction / shift commands
            elif command.startswith('set_direction_'):
                direction = command.split('_')[-1]  # Extract the direction from the command name
                if direction == 'forward':
                    self.control_states['drive_reverse'] =  False
                elif direction == 'reverse':
                    self.control_states['drive_reverse'] = True
            elif command == 'toggle_direction':
                current_direction = self.control_states.get('drive_reverse', self.control_defaults['drive_reverse'])
                self.control_states['drive_reverse'] = not current_direction  # Toggle direction
            elif command == 'toggle_shift':
                current_shift = self.control_states.get('shift_up', self.control_defaults['shift_up'])
                self.control_states['shift_up'] = not current_shift  # Toggle shift up:

            # Steering control commands
            elif command.startswith('set_steering_'):
                params = command.split('_')[-1]  # Extract the steering parameters from the command name
                direction = params.split('-')[0]  # Extract the steering direction (left or right) from the command name
                value = int(params.split('-')[-1])  # Extract the steering value from the command name
                if direction == 'left':
                    self.control_states['steer_reverse'] = False  # Set left steering power (negative value)
                elif direction == 'right':
                    self.control_states['steer_reverse'] = True  # Set right steering power (positive value)
                self.control_states['steer_power'] = value  # Update the internal state with the new steering power
                
            # Motion control commands
            elif command == 'toggle_hold_speed':
                self.hold_speed = not self.hold_speed  # Toggle hold speed state
            elif command == 'go':
                # Switches from resistive brakeing to current source for drive motors
                # Might want to update conrol board firmware for gradual acceleration
                # Right now it just relys on remote control user to determine 
                self.control_states['brake'] = False 
                # If previous state saved, use it, otherwise defualt
                self.control_states['drive_power'] = self.previous_control_states.get('drive_power', self.control_defaults['drive_power'])
            elif command == 'stop':
                self.control_states['brake'] = True 
                self.control_states['drive_power'] = 0
                # Store the previous speed
                self.previous_control_states['drive_power'] = self.control_states.get('drive_power', self.control_defaults['drive_power'])  # Store the current speed before stopping
            elif command == 'coast':
                # Shuts off power source to drive motors without braking
                self.control_states['brake'] = False 
                self.control_states['drive_power'] = 0
                # Store the previous speed
                self.previous_control_states['drive_power'] = self.control_states.get('drive_power', self.control_defaults['drive_power'])  # Store the current speed before coasting

        self.send_control()

    def send_control(self):
        # Construct a ControlData message from the current control states and publish it
        # Make sure to convert to proper ROS2 types
        try:
            control_msg = ControlData()
            control_msg.brake = self.control_states.get('brake', self.control_defaults['brake'])
            control_msg.drive_reverse = self.control_states.get('drive_reverse', self.control_defaults['drive_reverse'])
            control_msg.steer_reverse = self.control_states.get('steer_reverse', self.control_defaults['steer_reverse'])
            control_msg.shift_up = self.control_states.get('shift_up', self.control_defaults['shift_up'])
            control_msg.drive_power = self.control_states.get('drive_power', self.control_defaults['drive_power'])
            control_msg.steer_power = self.control_states.get('steer_power', self.control_defaults['steer_power'])
            control_msg.fan_speed = self.control_states.get('fan_speed', self.control_defaults['fan_speed'])
            self.control_string_publisher.publish(control_msg)  # Publish the control command to the rest of the system
            if self.get_parameter('verbose').get_parameter_value().bool_value:
                self.get_logger().info(f"Published control command: {control_msg}")
        except Exception as e:
            self.get_logger().error(f"Error constructing or publishing control message: {e}")

    def timeout_callback(self):
        self.control_states['steer_power'] = 0
        if not self.hold_speed:
            self.control_states['drive_power'] = 0      
        # Nothing else needs to be reset              


def main(args=None):
    rclpy.init(args=args)
    try:
        node = IRRemoteController()
    except Exception as e:
        print(f"Failed to initialize node: {e}")  # print since logger may not be available
        rclpy.shutdown()
        return  
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()