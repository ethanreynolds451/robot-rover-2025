#ifndef ADDRESS_h
#define ADDRESS_h

#include "numberOfSensors.h"

namespace Address {
  static constexpr uint8_t tof[NumberOfSensors::tof] = {
    0x29, 0x30, 0x31, 0x32, 0x33
  };  // First default, rest must be programmed ON EACH POWER CYCLE IS VOLATILE, use XSHUT pin to ennable individually
  static constexpr uint8_t qmc[NumberOfSensors::qmc] = {
    0x0D
  };  // Default (verified from datasheeet)
  static constexpr uint8_t mpu[numberOfSensors::mpu] = {
    0x68, 0x69
  };  // First default, second with adjustor pulled up to 5v
  static constexpr uint8_t pcf[NumberOfSensors::pcf] = {
    0x20
  };  // Default according to ChatGPT, check specific model
};

#endif