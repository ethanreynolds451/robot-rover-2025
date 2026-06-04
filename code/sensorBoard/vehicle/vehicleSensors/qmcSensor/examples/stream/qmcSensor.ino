// Stream QMC data in ROS parser format

#include <Wire.h>
#include "qmcSensor.h"

uint8_t ADDRESS = 0x0D; 

using qmcSensor = qmc_sensor::qmc_object;

qmcSensor qmc(ADDRESS); 

// Buffer to hold the output string
char outputString[58];      // Value is max possible number of characters for valid string, including null character
// More than 63 bytes so will require multiple blocking serial writes
// Use packet version for non-blocking stream// Use packet version for non-blocking stream

void setup() {
  Serial.begin(115200); 
  qmc.initialize(qmc_sensor::WIRE::START_WIRE);
  delay(100);    // Short delay for I2C initialization
  qmc.begin();
}

void loop() {

  qmc.poll();

  if (qmc.peek().is_new){

    // Calcucode/sensorBoard/vehicle/vehicleSensors/tofSensor/examples/blank/tofSensor.inolate timestamps and offsets for the packet
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - qmc.peek().timestamp;
    
    // Prepare the output string
    memset(outputString, 0, sizeof(outputString));
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "qmc[n:0");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(qmc.get_state()), static_cast<uint8_t>(qmc.get_error()));

    // Add new snsor data
    if(qmc.peek().direction.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",h:%x", qmc.get_direction().value);
    }
    if(qmc.peek().mag.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",m:%x;%x;%x", qmc.get_mag().value.x, qmc.get_mag().value.y, qmc.get_mag().value.z);
    }

    // End the packet and send over serial
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    qmc.clear();
  }

}
