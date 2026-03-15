//#include <IRremote.h>

#include "IRremote-4.4.1/src/IRremote.h"

#include "irSensor.h"

uint8_t IR_PIN = 2; 

irSensor testIR(IR_PIN); 

void setup() {
  Serial.begin(9600); 
  testIR.begin(); 
}

void loop() {
  if(testIR.update()){
    Serial.println("Recieved Data:"); 
    Serial.print("     Command: "); 
    Serial.println(testIR.command()); 
    Serial.print("     Address: "); 
    Serial.println(testIR.address()); 
    Serial.print("     Full data: "); 
    Serial.println(testIR.data()); 
  }
}
