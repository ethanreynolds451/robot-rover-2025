#ifndef CODES_h
#define CODES_h

#include "numberOfSensors.h"

namespace Code {
  static const uint8_t number_of_sensors = NumberOfSensors::types;     // Number of valid commands
  static const uint8_t number_of_errors = 6;      
  struct code_struct {                 // Structure for code mapping
    uint8_t index;
    char code[4];
  };
  struct error_packet {
    uint8_t index;
    char code[8];   // 8 byte max for codes
  };
  namespace Sensor {
    const char* ultrasonic = "hc";
    const char* tof = "lof";
    const char* steering ="str";
    const char* mpu = "mpu";
    const char* qmc = "qmc";
    const char* gps = "gps";
    const char* remote = "ir";
  };
  // Mapping of sensor indices to codes
  const code_struct sensor[number_of_sensors] = {
      {0, Sensor::ultrasonic},     // Ultrasonic sensor
      {1, Sensor::tof},    // Light of Flight sensor
      {2, Sensor::steering},    // Steering angle sensor
      {3, Sensor::mpu},    // MPU sensor
      {4, Sensor::qmc},    // QMC5883L sensor
      {5, Sensor::gps},    // GPS sensor
      {6, Sensor::remote}      // Infrared remote sensor
  };
  const error_packet error[number_of_errors] = {
      {0, "none"},    // no error
      {1, "addr"},    // address not found
      {2, "init"},    // failed to initialize
      {3, "read"},    // failed to read data
      {4, "nocom"},   // unable to communicate
      {5, "other"}    // any other failure
  };
};

#endif