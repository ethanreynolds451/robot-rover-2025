#ifndef DEVICE_PARAMS_T_H
#define DEVICE_PARAMS_T_H

namespace device_params {

struct ULTRASONIC_SENSOR {
    uint8_t trig_pin;
    uint8_t echo_pin;
    int8_t temp_calibration; // Celsius, signed int8_t
    unsigned int timeout_distance; // mm, unsigned int
};

}

#endif