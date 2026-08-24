# Command String: {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]fan[0]}
# Might want to change this?

std_msgs/Header     header                 # Contains the system time when the packet was processed
uint32              arduino_timestamp      # Only for incoming packets
bool                brake
bool                drive_reverse
bool                steer_reverse
bool                shift_up
uint8               drive_power
uint8               steer_power
uint8               fan_speed