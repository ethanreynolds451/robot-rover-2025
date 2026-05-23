# Custom for encoder data from arduino encoder library

std_msgs/Header     header
std_msgs/Bool       is_valid
uint32              arduino_timestamp

float32             position        # encoder ticks
std_msgs/Bool       calibrated
int8                direction       # -1, 0, 1