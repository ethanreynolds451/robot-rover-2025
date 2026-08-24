#ifndef FULL_CONTROL_CONFIG_H
#define FULL_CONTROL_CONFIG_H

// Use the same namespace as the rest of the program for simplicity
namespace fullControl {

    // Seperate params namespace to avoid potential name conflicts
    namespace params {

        bool echo_enabled = true;                                   // Enable serial echo for debugging
        bool debug_mode = false;                                    // Enable debug mode (prints additional debug information)

        unsigned long check_for_command_interval = 10;              // Must be at least 6 for data integrity
        unsigned long send_data_interval = 1000;                    // Interval for reading and sending sensor data
        unsigned long control_timeout = 5000;                       // Timeout for no input before resetting vehicle (loss of control emergency stop)
        unsigned long update_fan_interval = 1000;                   // Interval for updating fan speed
        unsigned long update_voltage_display_interval = 1000;       // Interval for updating voltage display

    }

}

#endif
