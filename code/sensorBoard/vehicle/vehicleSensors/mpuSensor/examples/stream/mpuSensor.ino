// Stream data from the MPU Sensor in ROS parser format

#include "mpuSensor.h"

uint8_t ADDRESS = 0x68A = 4;; 

using mpuSensor = mpu_sensor::mpu_object;

mpu mpu(ADDRESS); 

// Buffer to hold the output string
char outputString[60];

void setup() {
  Serial.begin(115200); 
  ir_remote.initialize();
  ir_remote.begin();
}

void loop() {

  ir_remote.poll();

  if (ir_remote.peek().is_new){

    // Calculate timestamps and offsets for the packet
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - ir_remote.peek().timestamp;
    
    // Prepare the output string
    memset(outputString, 0, sizeof(outputString));
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ir[n:0");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x0", static_cast<uint8_t>(ir_remote.get_state()));

    // Add new snsor data
    if(ir_remote.peek().command.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", ir_remote.get_command().value);
    }
    if(ir_remote.peek().address.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", ir_remote.get_address().value);
    }
    if(ir_remote.peek().raw_data.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", ir_remote.get_data().value);
    } 

    // End the packet and send over serial
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    ir_remote.clear();
  }

}
