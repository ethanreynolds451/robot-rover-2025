// Stream IR data in ROS sensor string parser format

#include "irSensor.h"

uint8_t IR_PIN = 4; 

using irSensor = ir_sensor::ir_object;

irSensor testIR(IR_PIN, ir_sensor::LED::LED_OFF); 

// Buffer to hold the output string
char outputString[60];

void setup() {
  Serial.begin(115200); 
  testIR.initialize();
  testIR.begin();
}

void loop() {

  testIR.poll();

  if (testIR.peek().is_new){

    // Calculate timestamps and offsets for the packet
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - testIR.peek().timestamp;
    
    // Start building the output string
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ir[");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "n:0,");       
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x0", static_cast<uint8_t>(testIR.get_state()));

    // Add new snsor data
    if(testIR.peek().command.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", testIR.get_command().value);
    }
    if(testIR.peek().address.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", testIR.get_address().value);
    }
    if(testIR.peek().raw_data.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", testIR.get_data().value);
    } 

    // End the packet and send
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    testIR.clear();
  }
  
}
