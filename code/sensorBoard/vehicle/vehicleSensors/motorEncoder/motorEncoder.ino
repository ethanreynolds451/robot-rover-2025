#include <Arduino.h>
#include <Encoder.h>

#include "Encoder/Encoder.h"

#include "motorEncoder.h"

#define PIN_A 2
#define PIN_B 3

motorEncoder testEncoder(PIN_A, PIN_B); 

void setup() {
  Serial.begin(9600);   
}

void loop() {
  if(testEncoder.is_new_position()){
    Serial.print("The motor has moved " );
    Serial.print(testEncoder.get_position_change());
    Serial.println(" units"); 
    Serial.print("The motor is now at position "); 
    Serial.println(testEncoder.read_position()); 
  }
  delay(1000);   
}
