// Stream data from the MPU Sensor in ROS parser format

#include <Wire.h>
#include "mpuSensor.h"

uint8_t ADDRESS = 0x68; 

using mpuSensor = mpu_sensor::mpu_object;

mpuSensor mpu(ADDRESS); 

// Buffer to hold the output string
char outputString[76];      // Value is max possible number of characters for valid string, including null character
// More than 63 bytes so will require multiple blocking serial writes
// Use packet version for non-blocking stream

void setup() {
  Serial.begin(115200); 
  mpu.initialize(mpu_sensor::WIRE::START_WIRE);
  delay(100);    // Short delay for I2C initialization
  mpu.begin();
}

void loop() {

  mpu.poll();

  if (mpu.peek().is_new){

    // Calculate timestamps and offsets for the packet
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - mpu.peek().timestamp;
    
    // Prepare the output string
    memset(outputString, 0, sizeof(outputString));
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "mpu[n:0");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(mpu.get_state()), static_cast<uint8_t>(mpu.get_error()));

    // Add new snsor data
    if(mpu.peek().accel.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", mpu.get_acceleration().value);
    }
    if(mpu.peek().gyro.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",g:%x", mpu.get_gyro().value);
    }
    if(mpu.peek().temp.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", mpu.get_temperature().value);
    }

    // End the packet and send over serial
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    mpu.clear();
  }

}
