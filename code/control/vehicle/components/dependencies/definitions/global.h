// Compiled successfully 2025-01-02

#ifndef GLOBAL_h
#define GLOBAL_h

// Global definitions not associated with specific namespace
#define BAUD_RATE 115200;                   // Serial baud rate
#define STRING_LIMIT 64                     // Maximum length of input string, matches serial buffer
#define BATTERY_VOLTAGE_SLOPE 1/.60         // Voltage divider slope for battery monitor 
#define BATTERY_TYPE "FLOODED"              // Flooded lead acid battery
#define MIN_FAN_TEMP 25                     // Temperature below which fan is at min speed
#define MAX_FAN_TEMP 50                     // Temperature above which fan is at max speed


#endif 
