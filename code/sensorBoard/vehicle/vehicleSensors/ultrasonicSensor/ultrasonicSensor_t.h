#ifndef ULTRASONIC_SENSOR_T_H
#define ULTRASONIC_SENSOR_T_H

namespace ultrasonic_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  WAITING       = 5,        // waiting for reading (ping sent, waiting for response)
  FAULT         = 255       // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 255       // An unknown error has ocurred
};

struct PINS {
    uint8_t trig = A0;      // Match the defaults in AsyncSonar
    uint8_t echo = A0;
};

struct CALIBRATION {
    int8_t temp = 25;                           // Celsius, signed int8_t
    unsigned int timeout_distance = 2000;       // mm, unsigned int
};

struct CONFIG {
    PINS pins;
    CALIBRATION calibration;
};

struct DISTANCE {
    bool is_new = false;
    float value = 0.0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    DISTANCE distance;
};

}

#endif 