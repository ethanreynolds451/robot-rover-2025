// This version has been modified to transmit data for IR control 
//    corresponding to the same string format used by the system

//#include <IRremote.h>

#include "IRremote-4.4.1/src/IRremote.h"

#include "irSensor.h"

uint8_t IR_PIN = 4; 

irSensor testIR(IR_PIN, IR_LED_OFF); 

// Buffer to hold the output string
char outputString[64];

void setup() {
  Serial.begin(115200); 
  testIR.begin(); 
  // Serial.println("Initiated IR sensor"); 
}

void loop() {
  // If there is new data from the IR sensor
  if(testIR.update()){
    // Clear any previous data from the buffer
    memset(outputString, 0, sizeof(outputString));

    // Create variables for data
    unsigned long arduino_timestamp = 0;
    unsigned long sensor_timestamp = 0;
    unsigned long offset_timestamp = 0;
    uint16_t command = 0;
    uint16_t address = 0;
    IRRawDataType data = 0;
    bool isCommand = false;
    bool isAddress = false;
    bool isData = false;

    // Get the recieved data, will use the last timestamp of any data type
    if(testIR.is_new_command()){
      isCommand = true;
      command = testIR.get_command();
      sensor_timestamp = testIR.get_command_timestamp();
    }
    if(testIR.is_new_address()){
      isAddress = true;
      address = testIR.get_address();
      sensor_timestamp = testIR.get_address_timestamp();
    }
    if(testIR.is_new_data()){
      isData = true;
      data = testIR.get_data();
      sensor_timestamp = testIR.get_data_timestamp();
    }

    // Calculate timestamps
    arduino_timestamp = millis();
    offset_timestamp = arduino_timestamp - sensor_timestamp;

    // Declare and the string incrementer to 0
    int pos = 0; 

    // Construct the output string
    // Encode the data as hexadecimal to save space
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ir[");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "t:%x", offset_timestamp);
    if (isCommand){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", command);
    }
    if (isAddress){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", address);
    }
    if (isData){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", data);
    }
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
