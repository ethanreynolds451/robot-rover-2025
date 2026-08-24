'''
This node simulates the vehicle sensor board
- Subscribes to simulated sensor environment data topic
- Publishes to the sensor_str topic to mimic real sensor board output

Note: module uses string messages and relies on conversion layer just like the real vehicle

Topics:
 Subscribes to:
- /vehicle/sim_sensor_data
    - sensor data from the simulated environment to mimic real sensor board input, mimics the topic
 Publishes to: 
- /vehicle/sensor_str
    - sensor data published to mimic the sensor board output, mimics the topic used in the real vehicle for easy integration with conversion layer

Services:
- None

Parameters: 
- processing_delay (double)
    - delay in seconds to simulate sensor board processing time (callibrate based on hardware)
- max_sensor_queue_time (double)
    - max time in seconds that a sensor data can be held in the queue before being dropped to prevent excessive queuing of stale data
    
'''

# Packages for ROS2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
import asyncio

class VehicleSensorSim(Node):
    def __init__(self):
        super().__init__('vehicle_sensor_sim')
        self.get_logger().info('Starting Vehicle Sensor Simulation Node')

        # Set up a callback group to handle qued sensor data sequentially (simulate processing time of sensor board)
        self.cb_group = MutuallyExclusiveCallbackGroup()

        # Subscriber for simulated sensor data
        self.create_subscription(
            String, 
            'sim_sensor_data', 
            self.sensor_data_callback, 
            qos_profile=10,
            callback_group=self.cb_group
        )

        # Publisher for sensor board output
        self.sensor_str_publisher = self.create_publisher(
            String,
            'sensor_str',
            10
        )

        # Queue for incoming data to simulate processing delay for sensor board
        self._command_queue = asyncio.Queue()

        # Delay in seconds to simulate sensor board processing time (callibrate based on hardware)
        self.declare_parameter('processing_delay', 0.1)

        # Max time that sensor data can be held in the que before being dropped
        self.declare_parameter('max_sensor_queue_time', 1.0)


    def sensor_data_callback(self, msg):
        # Whenever new sensor data is recieved from the simulated environment, add it to the quee
        quued_command = (msg.data, self.get_clock().now())
        self._command_queue.put_nowait(quued_command)
        self.get_logger().info(f'Queued sensor command: {msg.data} at time: {quued_command[1].to_msg().sec}.{quued_command[1].to_msg().nanosec}')

    
    async def process_sensor_data(self):
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
            if age_sec > self.get_parameter('max_sensor_queue_time').get_parameter_value().double_value:
                # Update the tracker for number of dropped commands
                # self._dropped_data += 1
                # Log dropped command and continue to next one in queue
                self.get_logger().warning(f'Dropped stale sensor data: {command}')
                continue

            # Simulate the hardware delay using asyncio sleep
            await asyncio.sleep(self.get_parameter('processing_delay').get_parameter_value().double_value)  # Simulate processing delay
            
            # Publish the command to the sensor data string topic to mimic the sensor board output
            sensor_msg = String()
            sensor_msg.data = f'{command}'
            self.sensor_str_publisher.publish(sensor_msg)
            self.get_logger().info(f'Recieved data from sensor board: {sensor_msg.data}')


def main(args=None):
    rclpy.init(args=args)
    node = VehicleSensorSim()

    # Start the background process to handle queued sensor data
    executor = MultiThreadedExecutor()
    executor.add_node(node)

    loop = asyncio.get_event_loop()

    # Run the async command processor alongside the ROS executor
    loop.run_until_complete(asyncio.gather(
        loop.run_in_executor(None, executor.spin),
        node.process_sensor_data()
    ))

    node.destroy_node()
    rclpy.shutdown()