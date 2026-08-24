#ifndef MPU_SENSOR_T_H
#define MPU_SENSOR_T_H

#define MPUPARAM_ACCELRANGE_DEFAULT MPU6050_RANGE_2_G      // estimate for low speed vehcile, increase if needed
#define MPUPARAM_GYRORANGE_DEFAULT MPU6050_RANGE_250_DEG   // estimate for low speed vehcile, increase if needed
#define MPUPARAM_BANDWIDTH_DEFAULT MPU6050_BAND_44_HZ      // based on 25 ms relay timeout

namespace mpu_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // ready to read valid data, but not actively reading
  ACTIVE        = 5,        // actively reading data
  FAULT         = 15        // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 15       // An unknown error has ocurred
};

enum class WIRE : bool {
    START_WIRE = true,
    NO_START_WIRE = false
};

struct CALIBRATION {
    mpu6050_accel_range_t accel_range = MPUPARAM_ACCELRANGE_DEFAULT; 
    mpu6050_gyro_range_t gyro_range = MPUPARAM_GYRORANGE_DEFAULT;
    mpu6050_bandwidth_t bandwidth = MPUPARAM_BANDWIDTH_DEFAULT;      
};

struct INVALID_DATA {
    // For validity checks, values are converted to real units using sensor.getEvent()
    float accel_max = 160;
    float gyro_max = 2000;
    int temp_min = -40;
    int temp_max = 85;
};

struct CONFIG {
    uint8_t address = 0x68;
    CALIBRATION calibration;
    INVALID_DATA invalid_data_thresholds;
};

struct VECTOR_3 {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
};

struct ACCEL {
    bool is_new = false;
    unsigned long timestamp = 0;
    VECTOR_3 value;
};

struct GYRO {
    bool is_new = false;
    unsigned long timestamp = 0;
    VECTOR_3 value;
};

struct TEMP {
    bool is_new = false;
    unsigned long timestamp = 0;
    int16_t value = 0;
};

struct DATA {
    ACCEL accel;
    GYRO gyro;
    TEMP temp;
    unsigned long timestamp = 0;
    bool is_new = false;
};

}

#endif