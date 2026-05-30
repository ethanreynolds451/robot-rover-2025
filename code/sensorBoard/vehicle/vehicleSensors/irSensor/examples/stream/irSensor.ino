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
  // Poll the sensor
  testIR.poll();

  // Check for new data
  ir_sensor::DATA data = testIR.peek();
  if (data.is_new){
    ir_sensor::STATE state = testIR.get_state();

    // Calculate timestamps
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - data.timestamp;

    // Declare and the string incrementer to 0
    int pos = 0; 

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ir[");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "n:0,");       
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x0", static_cast<uint8_t>(state));

    // Add any new snsor data
    if(data.command.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", irSensor.get_command().value);
    }
    if(data.address.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", irSensor.get_address().value);
    }
    if(data.raw_data.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", irSensor.get_data().value);
    } 

    // End the packet
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");

    // Send the packet over serial with newline character to indicate end of packet
    // This does not go through the serial manager's packetization system since this is a simple test
    // It is guarenteed to always be less than 64 bytes
    Serial.println(outputString);

    // Clear the IR data to ensure no old data is transmitted in the next loop
    // Just a safety measure since they should all be cleared by the getter functions
    testIR.clear();
  }
}
