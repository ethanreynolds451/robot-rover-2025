#ifndef NUMBEROFSENSORS_h
#define NUMBEROFSENSORS_h

namespace NumberOfSensors{
    static constexpr uint8_t all = 15;         // Total number of sensors
    static constexpr uint8_t types = 6;         // Total number of sensors
    static constexpr uint8_t tof = 5;           // Number of VL53L0X sensors
    static constexpr uint8_t ultrasonic = 5;    // Number of HC-SR04 sensors
    static constexpr uint8_t qmc = 1;           // Number of QMC5883L sensors
    static constexpr uint8_t mpu = 2;           // Number of MPU6050 sensors
    static constexpr uint8_t ir = 1;            // Number of ir sensors
    static constexpr uint8_t encoder = 1;       // Number of motor encoders
    // Not actually a sensor but included for convenience
    static constexpr uint8_t pcf = 1;           // Number of PCF8574 expanders
}

#endif