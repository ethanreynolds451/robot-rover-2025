# Launches the modules required for controlling the vehicle with a remote control

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler, EmitEvent, LogInfo, TimerAction
from launch.event_handlers import OnProcessExit, OnProcessStart, OnProcessIO
from launch.events import Shutdown
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

from vehicle_assets import play_sound_effect

def startup_hook(context):
    print("\n=== SYSTEM STARTUP: Initializing IR control system ===\n")
    # Play sound to indicate system is starting up
    play_sound_effect('system_start.mp3')

def failure_cleanup_hook(event, context):
    print("\n=== SYSTEM SHUTDOWN: Stopping motors and saving error logs ===\n")
    # Play fatal error sound effect
    play_sound_effect('fatal_error.mp3')
    # Ensure everything gets shut down correctly by stopping all running nodes and saving logs
    # ADD STUFF HERE
    Shutdown()

def system_ready_hook(event = None, context = None):
    print("\n=== SYSTEM READY: Vehicle is ready for remote control ===\n")
    # Play sound to indicate system is ready
    play_sound_effect('system_ready.mp3')


def generate_launch_description():
    # Declare launch arguments
    logger_level_arg = DeclareLaunchArgument(
        'logger_level',
        default_value='info',
        description='Logging level for the nodes (e.g., debug, info, warn, error)'
    )
    node_verbosity_arg = DeclareLaunchArgument(
        'node_verbosity_enabled',
        default_value='false',
        description='Enable verbose logging for the nodes'
    )
    packet_mode_arg = DeclareLaunchArgument(
        'packet_mode',
        default_value='',
        description='Enable packet mode for the listed serial interfaces, expects comma separated list of interfaces'
    )

    # Perform a sequential startup to ensure run dependencies are met

    # First start the serial manager to give it time to identify connected devices
    serial_manager_node = Node(
        package='vehicle_networking',
        executable='serial_manager',
        name='serial_manager',
        output='both',     # Log to both console and log files
        emulate_tty=True,  # Ensure the node can run in headless mode without issues
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
    )

    serial_manager_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=serial_manager_node,
            on_exit=[
                LogInfo(msg='Serial Manager node has failed to start, shutting down launch.'),
                EmitEvent(event=failure_cleanup_hook)
            ]
        )
    )

    serial_manager_on_success = RegisterEventHandler(
        OnProcessIO(
            target_action=serial_manager_node,
            on_stdout=lambda event: [delay_for_serial_hardware] if b"initialization successful" in event.text else None
        )
    )

    delay_for_serial_hardware = TimerAction(
        period=3.0, # Wait 3 seconds for the serial manager to initialize hardware
        # This gives it time to identify connected devices so that they are ready when serial interfaces start up
        actions=[sensor_serial_interface_node, control_serial_interface_node]
    )

    sensor_serial_interface_node = Node(
        package='vehicle_networking',
        executable='sensor_serial_interface',
        name='sensor_serial_interface',
        output='both',
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
        parameters=[{
            'verbose': LaunchConfiguration('node_verbosity_enabled'),
            'packet_mode': LaunchConfiguration('packet_mode')
        }]
    )

    sensor_serial_interface_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=sensor_serial_interface_node,
            on_exit=[
                LogInfo(msg='Sensor Serial Interface node has failed to start, shutting down launch.'),
                EmitEvent(event=Shutdown())
            ]
        )
    )

    control_serial_interface_node = Node(
        package='vehicle_networking',
        executable='control_serial_interface',
        name='control_serial_interface',
        output='both',
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
        parameters=[{
            'verbose': LaunchConfiguration('node_verbosity_enabled'),
            'packet_mode': LaunchConfiguration('packet_mode')
        }]
    )

    control_serial_interface_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=control_serial_interface_node,
            on_exit=[
                LogInfo(msg='Control Serial Interface node has failed to start, shutting down launch.'),
                EmitEvent(event=Shutdown())
            ]
        )
    )

    sensor_serial_interface_on_success = RegisterEventHandler(
        OnProcessIO(
            target_action=sensor_serial_interface_node,
            






    ir_control_node = Node(
        package='vehicle_controllers',
        executable='ir_control',
        name='ir_control',
        output='both',
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
        parameters=[{
            'verbose': LaunchConfiguration('node_verbosity_enabled')
        }]
    )

    ir_control_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=ir_control_node,
            on_exit=[
                LogInfo(msg='IR Control node has failed to start, shutting down launch.'),
                EmitEvent(event=failure_cleanup_hook)
            ]
        )
    )



    sensor_string_parser_node = Node(
        package='vehicle_string_converter',
        executable='sensor_string_parser',
        name='sensor_string_parser',
        output=message_output,
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
        parameters=[{
            'verbose': LaunchConfiguration('node_verbosity_enabled')
        }]
    )

    sensor_string_parser_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=sensor_string_parser_node,
            on_exit=[
                LogInfo(msg='Sensor String Parser node has failed to start, shutting down launch.'),
                EmitEvent(event=Shutdown())
            ]
        )
    )

    control_string_builder_node = Node(
        package='vehicle_string_converter',
        executable='control_string_builder',
        name='control_string_builder',
        output=message_output,
        arguments = ['--ros-args', '--log-level', LaunchConfiguration('logger_level')],
        parameters=[{
            'verbose': LaunchConfiguration('node_verbosity_enabled')
        }]
    )

    control_string_builder_error_handler = RegisterEventHandler(
        OnProcessExit(
            target_action=control_string_builder_node,
            on_exit=[
                LogInfo(msg='Control String Builder node has failed to start, shutting down launch.'),
                EmitEvent(event=Shutdown())
            ]
        )
    )


    return LaunchDescription([
        logger_level_arg,
        node_verbosity_arg,
        packet_mode_arg,
        ir_control_node,
        ir_control_error_handler,
        sensor_string_parser_node,
        sensor_string_parser_error_handler,
        control_string_builder_node,
        control_string_builder_error_handler,
        sensor_serial_interface_node,
        sensor_serial_interface_error_handler,
        control_serial_interface_node,
        control_serial_interface_error_handler,
        serial_manager_node,
        serial_manager_error_handler
    ])




'''
Generic launch file template

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='your_package_name',
            executable='your_executable_name',
            name='node_name',
            output='screen',
            parameters=[{'param_name': 'value'}],
            remappings=[('/old_topic', '/new_topic')]
        )
    ])
'''