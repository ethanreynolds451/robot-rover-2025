#ifndef ADDRESS_h
#define ADDRESS_h

#include "dependencies/libraries.h"

namespace address {
  static constexpr uint8_t lof[number_of_lof] = {0x29, 0x30, 0x31, 0x32}; // First default, rest must be programmed ON EACH POWER CYCLE IS VOLATILE
  static constexpr uint8_t qmc[number_of_qmc] = {0x0D};           // Default (verified from datasheeet)
  static constexpr uint8_t mpu[number_of_mpu] = {0x68, 0x69};     // First default, second with adjustor pulled up to 5v
  static constexpr uint8_t pcf = 0x20;     // Default according to ChatGPT, check specific model
  bool detect(uint8_t address) {      // From chat GPT, script to detect if i2c address is on bus, non-blocking and will not freze (hopefully)
    // Enable internal pull-ups on SDA and SCL pins
    pinMode(Pin::SDA, INPUT_PULLUP);
    pinMode(Pin::SCL, INPUT_PULLUP);
    // Small delay to let lines settle
    delay(10);
    // Check if lines are actually HIGH (pulled up)
    bool sda_high = digitalRead(Pin::SDA);
    bool scl_high = digitalRead(Pin::SCL);
    if (!sda_high || !scl_high) {
    return false; // Skip scanning, no proper bus setup
    }
    unsigned long start = millis();
    while (millis() - start < 100) { // 100 ms timeout
    Wire.beginTransmission(address);
    uint8_t result = Wire.endTransmission(true);
    if (result == 0) {
      return true;  // Device responded at this address
    }
    delay(5); // small delay before retrying
    }
    return false;  // No device responded
  }
};

#endif