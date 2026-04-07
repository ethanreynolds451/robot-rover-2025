''' 
This node simulates the control board.
- Reads commands from control_str topic
- Publishes status to control_status topic
- Potential for future expansion to virtual vehicle environment
Uses asynchronous processing to simulate control board delay
This module assumes a perfectly functional control board and does not simulate any unexpected behaviour or hardware issues.
'''

# Packages for ROS2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
import asyncio

class VehicleControlSim(Node):
    def __init__(self):
        super().__init__('vehicle_control_sim')
        self.get_logger().info('Starting Vehicle Control Simulation Node')

        # Set up a callback group to handle qued commands sequentially (simulate processing time of control board)
        self.cb_group = MutuallyExclusiveCallbackGroup()

        # Subscriber for control commands
        self.create_subscription(String, 
            'control_str', 
            self.control_command_callback, 
            qos_profile=10,
            callback_group=self.cb_group
        )

        # Publisher for control status
        self.control_status_publisher = self.create_publisher(
            String, 
            'control_status', 
            10
        )

        # Queue for incoming commands to simulate processing delay for control board
        self._command_queue = asyncio.Queue()

        # Delay in seconds to simulate control board processing time (callibrate based on hardware)
        self.declare_parameter('processing_delay', 0.1)  

        # Max time that a command can be held in the que before being dropped
        self.declare_parameter('max_command_queue_time', 1.0)

        # Track dropped commands
        self._dropped_commands = 0


    # This executes whenever a command is published to the control_str topic
    def control_command_callback(self, msg):
        # Create a tupple with timestamp to record command arrival time for queuing
        quued_command = (msg.data, self.get_clock().now())
        self._command_queue.put_nowait(quued_command)  # Add command to the queue
        self.get_logger().info(f'Queued control command: {msg.data} at time: {quued_command[1].to_msg().sec}.{quued_command[1].to_msg().nanosec}')


    # This executes in the background to process commands from the queue with a delay to simulate control board processing time
    async def process_command_queue(self):
        # Check the oldest command in the queue and process it if it's been there for less than the max allowed time, otherwise drop it
        # Runs as background process in node for asynchronous processing
        
        # Only executes when ther is a command in the que, no need to check if it is empty
        while rclpy.ok():
            try:
                command, arrival_time = await asyncio.wait_for(
                    self._command_queue.get(), timeout=1.0
                )
            except asyncio.TimeoutError:
                continue

            # If the latest command is too old, drop it and loop back to start
            current_time = self.get_clock().now()
            age_sec = (current_time - arrival_time).nanoseconds / 1e9
            if age_sec > self.get_parameter('max_command_queue_time').get_parameter_value().double_value:
                # Update the tracker for number of dropped commands
                self._dropped_commands += 1
                # Log dropped command and continue to next one in queue
                self.get_logger().warning(f'Dropped stale command: {command}')
                continue
        
            # Simulate sending the the next command to the control board
            self.get_logger().info(f'Sent command to control board: {command}')
            
            # Simulate the hardware delay using asyncio sleep
            await asyncio.sleep(self.get_parameter('processing_delay').get_parameter_value().double_value)  # Simulate processing delay
            
            # Publish a simulated status update from the control board
            status_msg = String()
            status_msg.data = f'{command}'
            self.control_status_publisher.publish(status_msg)
            self.get_logger().info(f'Recieved status update from control board: {status_msg.data}')



def main(args=None):
    rclpy.init(args=args)
    node = VehicleControlSim()

    executor = MultiThreadedExecutor()
    executor.add_node(node)

    loop = asyncio.get_event_loop()

    # Run the async command processor alongside the ROS executor
    loop.run_until_complete(asyncio.gather(
        loop.run_in_executor(None, executor.spin),
        node.process_command_queue()
    ))

    node.destroy_node()
    rclpy.shutdown()