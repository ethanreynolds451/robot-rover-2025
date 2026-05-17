# Custom for MPU on robot

std_msgs/Header                     header       # timestamp / frame ID
std_msgs/Bool                       is_valid
uint32                              arduino_timestamp

sensor_msgs/Imu                     imu          # inertial measurements
sensor_msgs/Temperature             temp         # temperature