#ifndef IR_SENSOR_T_H
#define IR_SENSOR_T_H

namespace ir_sensor {

enum class LED : uint8_t {
  LED_OFF,
  LED_ON
};

enum class STATE : uint8_t {
  UNINITIALIZED = 0,       
  DISCONNECTED  = 1,        
  IDENTIFIED    = 2,        
  CONFIGURED    = 3,        
  READY         = 4,       
  ACTIVE        = 5, 
  FAULT         = 255      
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