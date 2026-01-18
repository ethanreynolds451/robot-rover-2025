#ifndef ERRORS_h
#define ERRORS_h

#include "dependencies/definitions.h"

namespace error {                    // Storage for sensor errors
    uint8_t ultrasonic[number_of_ultrasonic];
    uint8_t lof[number_of_lof];
    uint8_t mpu[number_of_mpu];
    uint8_t qmc[number_of_qmc];
    uint8_t gps;
};

#endif