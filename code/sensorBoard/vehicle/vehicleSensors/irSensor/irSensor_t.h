#ifndef IR_SENSOR_T_H
#define IR_SENSOR_T_H

namespace ir_sensor {

enum class LED : uint8_t {
  LED_OFF,
  LED_ON
};

enum class STATE : uint8_t {
  UNINITIALIZED = 0,    // hardware not initialized
  DISCONNECTED  = 1,    // initialized but not connected or connection not checked
  IDENTIFIED    = 2,    // sensor connection verified
  CONFIGURED    = 3,    // configurations / calibrations applied
  READY         = 4,    // producing valid data but not active
  ACTIVE        = 5,    // sensor is actively reading data
  FAULT         = 255   // sensor is in a locked fault state - must be reset / re-initialized
};

struct CONFIG {
    uint8_t pin;
    LED led_active;
};

struct COMMAND {
    bool is_new = false;
    uint16_t value = 0;
    unsigned long timestamp = 0;
};

struct ADDRESS {
    bool is_new = false;
    uint16_t value = 0;
    unsigned long timestamp = 0;
};

struct RAW_DATA {
    bool is_new = false;
    IRRawDataType value = 0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    COMMAND command;
    ADDRESS address;
    RAW_DATA data;
};

}

#endif