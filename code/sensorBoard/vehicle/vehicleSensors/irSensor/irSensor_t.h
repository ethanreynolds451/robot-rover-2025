namespace ir_sensor {

enum class LED : uint8_t {
  LED_OFF,
  LED_ON
};

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  UNVERIFIED    = 2,        // no data read yet
  VERIFIED      = 3,        // confirmed functionality by reading data
  PAUSED        = 4,        // not currently reading data, but was verified before
  FAULT         = 255       // persistent/latched failure
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