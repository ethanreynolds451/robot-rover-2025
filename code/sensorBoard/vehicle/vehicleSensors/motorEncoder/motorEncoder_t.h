namespace motor_encoder {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  FAULT         = 255       // persistent/latched failure
};

struct PINS {
    uint8_t a;
    uint8_t b;
};

struct CONFIG {
    PINS pins;
};

struct ZERO {
    unsigned long timestamp = 0;
};

struct POSITION {
    bool is_new = false;
    long value = 0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    ZERO zero;
    POSITION position;
};

}