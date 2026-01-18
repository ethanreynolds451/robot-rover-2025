#ifndef DETECTI2CADDRESS_h
#define DETECTI2CADDRESS_h

#include "dependencies/libraries.h"

bool detectI2CAddress(uint8_t address) {      // From chat GPT, script to detect if i2c address is on bus, non-blocking and will not freze (hopefully)
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

#endif