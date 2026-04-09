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

std_msgs/Header                         header             # When the packet was processed by node
uint32                                  arduino_timestamp  # Arduino board system time in millis        

vehicle_interfaces/MPUData[]            mpu                # Internal MPU6050 IMU(s)

vehicle_interfaces/QMCData[]            qmc                # Internal QMC5583P magnetometer(s)

vehicle_interfaces/GPSData[]            gps                # One GPS unit used

vehicle_interfaces/ToFData[]            tof                # Distance and light intensity

vehicle_interfaces/UltrasonicData[]     ultrasonic         # Raw distance readings

vehicle_interfaces/TemperatureData[]    temperature        # Calculated temperatre from thermistor / voltage divider

vehicle_interfaces/EncoderData[]        encoder            # Raw data from Arduino encoder library

vehicle_interfaces/IRData[]             ir_remote          # From remote control IR sensor