#ifndef GLOBAL_h
#define GLOBAL_h

// Global definitions not associated with specific namespace
static const long input_timeout = 5000;	    // If no command recieved for interval, reset all outputs to default
static const long baud_rate = 115200;       // Serial baud rate
static const uint8_t string_limit = 64;     // Maximum length of input string, matches serial buffer
static const uint8_t pwm_min = 50;          // Minimum PWM value to overcome motor deadzone
static const uint8_t pwm_max = 200;         // Maximum PWM value to prevent overvoltage to motor driver
static const uint16_t loop_delay = 10;      // Must be at least 6 for data integrity
static const uint8_t serial_delay = 1;     // In loop cycles, NOT ms
static const uint16_t fan_delay = 10000;    // Check and update the temperature every 10 seconds
uint8_t echo_enabled = 1;                   // Set to 1 to enable serial echo for debugging
// Send data at 50ms interval

#endif 
