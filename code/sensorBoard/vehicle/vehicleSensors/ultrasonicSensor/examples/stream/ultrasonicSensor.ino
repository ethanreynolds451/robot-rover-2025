#include "ultrasonicSensor.h"

uint8_t TRIG = 38; 
uint8_t ECHO = A15;

using ultrasonicSensor = ultrasonic_sensor::ultrasonic_object;

ultrasonicSensor ultrasonic(TRIG, ECHO);

// Buffer to hold the output string
char outputString[41];  

void setup() {
  Serial.begin(115200); 
  ultrasonic.initialize();
  ultrasonic.begin();
}

void loop() {
  ultrasonic.update(); 

  ultrasonic.poll();

  if (ultrasonic.peek().is_new){

    // Calculate the timestamp offset
    unsigned long arduino_timestamp = millis();
    unsigned long offset_timestamp = arduino_timestamp - ultrasonic.peek().timestamp;
    
    // Prepare the output string
    memset(outputString, 0, sizeof(outputString));
    int pos = 0;

    // Add the arduino timestamp and sensor header data to the string
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ult[n:0");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(ultrasonic.get_state()), static_cast<uint8_t>(ultrasonic.get_error()));

    // Add new snsor data
    if(ultrasonic.peek().distance.is_new){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",r:%x", ultrasonic.get_distance().value);
    }

    // End the packet and send over serial
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
    Serial.println(outputString);

    // Clear the data 
    ultrasonic.clear();
  }

}
