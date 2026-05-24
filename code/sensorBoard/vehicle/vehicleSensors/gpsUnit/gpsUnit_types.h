
#ifndef GPS_UNIT_TYPES_H
#define GPS_UNIT_TYPES_H

namespace gps_unit {

// *** State and error enums *** //

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  FAULT         = 255,        // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    BUS_FAULT   = 3,        // There is a problem with the communication bus (software serial or hardware serial)
    UNKNOWN     = 255       // An unknown error has ocurred
};

// *** Config and parameter structs *** //

struct PINS {
    uint8_t tx = 0;     
    uint8_t rx = 1;
};

struct CONFIG {
    PINS pins;
    unsigned long baudrate = 9600;
    unsigned long timeout = 5000;       // Disconnected if nothing recieved after 

// *** Data structs *** //

struct COORDINATES {
    bool is_new = false;
    float lat;
    float long;
    unsigned long timestamp;
};

struct ALTITUDE {
    bool is_new = false;
    float value;
    unsigned long timestamp;
};

struct POSITION {
    COORDINATES coordinates;
    ALTITUDE altitude;
};

struct SPEED {
    bool is_new = false;
    float value;
    unsigned long timestamp;
}; 

struct COURSE {
    bool is_new = false;
    float value;
    unsigned long timestamp;
};

struct VELOCITY {
    SPEED speed;
    COURSE course;
};

struct TIME {
    bool is_new = false;
    unsigned long value;  
    unsigned long timestamp;
};

struct FIX {
    bool is_new = false;
    uint8_t value;  
    unsigned long timestamp;
};

struct DATA {
    unsigned long timestamp;        // Packet timestamp
    POSITION position;              // Data describing position
    VELOCITY velocity;              // Data describing velocity
    TIME time;                      // GPS time
    FIX fix;                        // GPS fix quality
};

}

#endif