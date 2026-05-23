# Custom for gps

std_msgs/Header                     header       # timestamp / frame ID
std_msgs/Bool                       is_valid
uint32                              arduino_timestamp

sensor_msgs/NavSatFix               position     # positional data
                                                 # includes optional fix information
float32                             heading      # heading in degrees
float32                             speed_kmph   # velocity calculated by unit
uint32                              gps_time     # satelite time from GPS
uint8                               sats         # number of saltelites used for signal

