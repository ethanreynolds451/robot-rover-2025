#ifndef TOF_SENSOR_T_H
#define TOF_SENSOR_T_H

namespace tof_sensor {

// No queremos exponer estas constantes
static constexpr uint8_t DEFAULT_ADDRESS = 0x29;
static constexpr uint8_t BACKGROUND_RATE_REGISTER = 0x22;   
static constexpr uint8_t SIGNAL_RATE_REGISTER = 0x20;   
static constexpr uint8_t SIGNAL_QUALITY_REGISTER = 0x14;

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  PAUSED        = 5,        // temporarily paused (e.g. to save power)
  FAULT         = 255       // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 255       // An unknown error has ocurred
};

enum class WIRE : bool {
    START_WIRE = true,
    NO_START_WIRE = false
};

struct INVALID_DATA {
    uint16_t distance_min = 0;  
    uint16_t distance_max = 8190; 
    uint16_t light_min = 0;       
    uint16_t light_max = 50000;   
};

struct CONFIG {
    uint8_t address = DEFAULT_ADDRESS;   
    float o
};

struct DISTANCE {
    bool is_new = false;
    uint16_t value = 0;
    unsigned long timestamp = 0;
};

struct BACKGROUND_RATE {
    bool is_new = false;
    uint16_t value = 0;
    unsigned long timestamp = 0;
};

struct SIGNAL_RATE {
    bool is_new = false;
    uint16_t value = 0;
    unsigned long timestamp = 0;
};

struct SIGNAL_QUALITY {
    bool is_new = false;
    uint8_t value = 0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    DISTANCE distance;
    BACKGROUND_RATE background_rate;
    SIGNAL_RATE signal_rate;
    SIGNAL_QUALITY signal_quality;
};

#endif