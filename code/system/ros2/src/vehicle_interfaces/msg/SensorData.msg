# This is a combined message for raw data from all the sensors 
# It is used by the translator node to convert serial string to sensor information

# Sensor String:  {mpu[n, accel, gyro, temp]
#                  qmc[n, mag, head, temp]
#                  gps[n, lat, long, alt, vel, head, time, sats]
#                  tof[n, dist, light]
#                  us[n, dist]
#                  tmp[n, temp]
#                  str[dir, pos, spd]
#                  ir[addr, cmd, data]}
# Might change this for better parsing

# One field for each type of sensor, the actual sensor is tracked using Frame ID for each instance

std_msgs/Header                         header

vehicle_interfaces/MPUData[]            mpu                # array for multiple sensors

vehicle_interfaces/QMCData[]            qmc                # array for multiple sensors

vehicle_interfaces/GPSData[]            gps                # Only one GPS unit used

vehicle_interfaces/TOFData[]            tof                # array for multiple sensors

vehicle_interfaces/UltrasonicData[]     ultrasonic         # array for multiple sensors

vehicle_interfaces/TemperatureData[]    temp               # array for multiple sensors

vehicle_interfaces/EncoderData[]        encoder            # Raw data from Arduino encoder library

vehicle_interfaces/IRData[]             ir_remote          # From remote control IR sensor