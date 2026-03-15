//#include <IRremote.h>

#include "IRremote-4.4.1/src/IRremote.h"

#include "irSensor.h"

uint8_t IR_PIN = 4; 

irSensor testIR(IR_PIN); 

void setup() {
  Serial.begin(9600); 
  testIR.begin(); 
  Serial.println("Initiated IR sensor"); 
}

void loop() {
  if(testIR.update()){
    Serial.println("Recieved Data:"); 
    if(testIR.is_new_command()){
      Serial.print("     Command: "); 
      Serial.print(testIR.get_command()); 
      Serial.print(" at time "); 
      Serial.println(testIR.get_command_timestamp());
    }
    if(testIR.is_new_address()){
      Serial.print("     Address: "); 
      Serial.print(testIR.get_address()); 
      Serial.print(" at time "); 
      Serial.println(testIR.get_address_timestamp());
    }
    if(testIR.is_new_data()){
      Serial.print("     Data: "); 
      Serial.print(testIR.get_data(), HEX); 
      Serial.print(" at time "); 
      Serial.println(testIR.get_data_timestamp());
    }
  }
}
