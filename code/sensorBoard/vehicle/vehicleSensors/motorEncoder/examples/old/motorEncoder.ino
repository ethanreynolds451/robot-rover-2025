#include <Arduino.h>
#include <Encoder.h>

#include "Encoder/Encoder.h"

#include "motorEncoder.h"

#define PIN_A 2
#define PIN_B 3

using motorEncoder = motor_encoder::encoder_object;

motorEncoder testEncoder(PIN_A, PIN_B); 

// Buffer to hold the output string
char outputString[64];

void setup() {
  Serial.begin(9600);   
}

void loop() {
  if (testEncoder.update()) {
    if (testEncoder.is_new_position()) {
      // Initialize output buffer and variables
      memset(outputString, 0, sizeof(outputString));
      unsigned long arduino_timestamp = 0;
      unsigned long sensor_timestamp = 0;
      unsigned long offset_timestamp = 0;
      long position = 0;

      // Get the current position and timestamp      
      position = testEncoder.get_position();
      arduino_timestamp = millis();
      sensor_timestamp = testEncoder.get_position_timestamp();
      offset_timestamp = arduino_timestamp - sensor_timestamp;

      // Convert position to unsigned long for hexadecimal encoding, extract sign
      uint8_t direction = (position < 0) ? 2 : (position > 0) ? 0 : 1;

      // Construct the output string, encode as hexadecimal
      int pos = 0;
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, "str[t:%x", offset_timestamp);
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:1,p:%x,d:%x]", position, direction);    // Just say it's calibrated for testing
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, "}");

      // Print the output string
      Serial.println(outputString);

      // Clear the position updated flag
      testEncoder.clear();
    }
  }
}
