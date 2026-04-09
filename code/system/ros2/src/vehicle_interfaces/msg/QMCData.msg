# Custom for QMC on robot

std_msgs/Header                     header       # timestamp / frame ID
std_msgs/Bool                       is_valid

string                              id           # device name
sensor_msgs/MagneticField           mag          # 3-axis magnetometer
float32                             heading      # heading in degrees
sensor_msgs/Temperature             temp         # temperature (if available)
      