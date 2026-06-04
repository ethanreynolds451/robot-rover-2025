#include "tofSensor.h"

uint8_t ADDRESS = 0x30; // Just a random address to verify that reassignment works

using tofSensor = tof_sensor::tof_object;

tofSensor tof(ADDRESS); 

// Buffer to hold the output string
char outputString[58];    
void setup() {
  Serial.begin(115200); 
  // This does the blocking address reasignment
  tof.initialize(tof_sensor::WIRE::START_WIRE);
  delay(100);    // Short delay for I2C initialization
  tof.begin();
}

void loop() {

  tof.poll();

  if (tof.peek().is_new){

    // Calculate the timestamp offset
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - tof.peek().timestamp;
    
    // Prepare the output string
    memset(outputString, 0, sizeof(outputString));
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "tof[n:0");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(tof.get_state()), static_cast<uint8_t>(tof.get_error()));

    // Add new snsor data
    if(tof.peek().range.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",r:%x", tof.get_range().value);
    }
    if(tof.peek().background_rate.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",b:%x", tof.get_background_rate().value);
    }
    if(tof.peek().signal_rate.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",g:%x", tof.get_signal_rate().value);
    }
    if(tof.peek().signal_quality.is_new){
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",q:%x", tof.get_signal_quality().value);
    }

    // End the packet and send over serial
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    tof.clear();
  }

}
