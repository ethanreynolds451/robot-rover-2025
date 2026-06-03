#ifndef TEMP_SENSOR_T_H
#define TEMP_SENSOR_T_H

namespace temp_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  IDENTIFIED    = 1,        // initialized
  CONFIGURED    = 2,        // init/config applied
  READY         = 3,        // producing valid readings
  ACTIVE        = 4,        // actively reading data
  FAULT         = 15       // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 15       // An unknown error has ocurred
};

struct CALIBRATION {
    float slope = 1.0;                       
    float intercept = 0.0;       
};

struct INVALID_DATA {
    float min = -10.0;                       
    float max_external = 40.0;
    float max_internal = 100.0;   
    bool use_external = false;       // Distinguish valid range for ambinet vs. control box temperature
};

struct CONFIG {
    uint8_t pin = A0;
    CALIBRATION calibration;
    INVALID_DATA invalid_data_thresholds;
};

struct TEMP {
    bool is_new = false;
    float value = 0.0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    TEMP measurement;
};

}

#endif