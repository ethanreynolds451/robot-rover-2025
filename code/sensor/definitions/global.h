#ifndef GLOBAL_h
#define GLOBAL_h

// Program flow / functionality parameters
static const long baudrate = 115200;
static const uint32_t gps_baudrate = 4800;
static const uint16_t serial_delay = 10;
static const uint16_t loop_interval = 10;
static const uint16_t send_interval = 25;
static const uint8_t string_limit = 64;

// How many of each type of sensor
static const uint8_t number_of_ultrasonic = 6;
static const uint8_t number_of_lof = 4;
static const uint8_t number_of_qmc = 1;
static const uint8_t number_of_mpu = 2;
static const uint8_t number_of_ir = 1;
static const uint8_t number_of_gps = 1;
static const uint8_t number_of_sensors =
    number_of_ultrasonic + number_of_lof + number_of_qmc + number_of_mpu +
    number_of_ir + number_of_gps;

// How many times to retry sensor initializations before moving on
static const uint8_t sensor_retry = 3;



#endif