#ifndef QMC_SENSOR_T_H
#define QMC_SENSOR_T_H

namespace qmc_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // ready to start taking data, but not actively doing so
  ACTIVE        = 5,        // actively taking data
  FAULT         = 15        // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 15        // An unknown error has ocurred
};

enum class WIRE : bool {
    START_WIRE = true,
    NO_START_WIRE = false
};

struct VECTOR_3 {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
};

struct VECTOR_3_FLOAT {
    float x;
    float y;
    float z;
};

struct CALIBRATION {
    VECTOR_3 offsets;
    VECTOR_3_FLOAT scales{1.0, 1.0, 1.0};
};

struct INVALID_DATA {
    int16_t mag_min = -32767;
    int16_t mag_max = 32767;
    int16_t direction_min = 0;
    int16_t direction_max = 360;
};

struct CONFIG {
    uint8_t address = 0x0D;   
    CALIBRATION calibration;
    INVALID_DATA invalid_data_thresholds;
};

struct MAG {
    bool is_new = false;
    VECTOR_3 value;
    unsigned long timestamp = 0;
};

struct DIRECTION {
    bool is_new = false;
    int16_t value = 0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    bool is_new = false;
    MAG mag;
    DIRECTION direction;
};

}

#endif