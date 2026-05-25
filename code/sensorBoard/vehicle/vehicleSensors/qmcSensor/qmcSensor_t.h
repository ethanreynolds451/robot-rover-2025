namespace qmc_sensor {

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

struct VECTOR_3 {
    float x;
    float y;
    float z;
};

struct CALIBRATION {
    VECTOR_3 offsets = {0, 0, 0};
    VECTOR_3 scales = {1.0, 1.0, 1.0};
};

struct CONFIG {
    uint8_t address = 0x0D;   
    CALIBRATION calibration;
};

struct MAG {
    bool is_new = false;
    VECTOR_3 value{0, 0, 0};
    unsigned long timestamp = 0;
}

struct DIRECTION {
    bool is_new = false;
    float value = 0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    MAG mag;
    DIRECTION direction;
};

}