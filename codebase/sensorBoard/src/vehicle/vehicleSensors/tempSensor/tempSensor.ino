#include "tempSensor.h"

uint8_t PIN = A1;
uint8_t SLOPE = 0.1;
uint8_t INTERCEPT = 0.0;

using tempSensor = temp_sensor::temp_object;

tempSensor temp(A1, SLOPE, INTERCEPT);

char outputString[41];

uint16_t hex_2(float value) {
    // First cast to int32 to avoid overflow
    int32_t scaled_value = static_cast<int32_t>(value * 100);
    // Verify that it fits in 16 bits and if not saturate it to the max/min value
    if (scaled_value > 32767) {
        scaled_value = 32767;
    } else if (scaled_value < -32768) {
        scaled_value = -32768;
    }
    // Now cast to uint16
    return static_cast<uint16_t>(scaled_value);
}

void setup() {
    Serial.begin(115200);
    temp.initialize();
    temp.begin();
}

void loop() {
    temp.poll();

    if (temp.peek().measurement.is_new) {

        // Calculate timestamps and offsets for the packet
        unsigned long arduino_timestamp = millis();
        unsigned long offset_timestamp = arduino_timestamp - temp.peek().timestamp;
        
        // Prepare the output string
        memset(outputString, 0, sizeof(outputString));
        int pos = 0;

        // Add the arduino timestamp and sensor header data to the string
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "tmp[n:0");
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(temp.get_state()), static_cast<uint8_t>(temp.get_error()));

        if(temp.peek().measurement.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",temp:%x", hex_2(temp.get_measurement().value));
        }

        // End the packet and send over serial
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);

        // Clear the data
        temp.clear();

    }
}