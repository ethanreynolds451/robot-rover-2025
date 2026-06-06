#ifndef DEVICES_H
#define DEVICES_H

#include "device_params_t.h"

using ult = device_params::ULTRASONIC_SENSOR;

// *** Ultrasonic Sensors *** //

ult ultrasonic_sensor[] = {
    // Side left ultrasonic
    {
    .trig_pin = 30,
    .echo_pin = A11,
    .temp_calibration = 25, 
    .timeout_distance = 1200 
    }, 
    // Front left ultrasonic
    {
    .trig_pin = 32,
    .echo_pin = A12,
    .temp_calibration = 25, 
    .timeout_distance = 2000 
    },
    // Front right ultrasonic
    {
    .trig_pin = 34,
    .echo_pin = A13,
    .temp_calibration = 25, 
    .timeout_distance = 2000 
    },
    // Side right ultrasonic
    {
    .trig_pin = 36,
    .echo_pin = A14,
    .temp_calibration = 25, 
    .timeout_distance = 1200 
    },
    // Rear ultrasonic
    {  
    .index = 4,
    .trig_pin = 38,
    .echo_pin = A15,
    .temp_calibration = 25, 
    .timeout_distance = 1000 
    }
};

#endif 