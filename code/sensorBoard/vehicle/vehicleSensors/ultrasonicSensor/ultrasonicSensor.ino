#include "ultrasonicSensor.h"

#include "ultrasonicSensor_codes.h"


uint8_t TRIG = A9; 
uint8_t ECHO = A8;
unsigned long BAUDRATE = 115200;
unsigned long POLL_INTERVAL = 500;

unsigned long timer = millis(); 

using ultrasonicSensor = ultrasonic_sensor::ultrasonic_object;

ultrasonicSensor ultrasonic(TRIG, ECHO);

char stateString[16];
char errorString[16];

void setup() {
    Serial.begin(BAUDRATE); 
    Serial.println("Started serial communication");
    Serial.println("Initializing ultrasonic sensor...");
    ultrasonic.initialize();
    ultrasonic_sensor::get_state_str(ultrasonic.get_state(), stateString, sizeof(stateString));
    ultrasonic_sensor::get_error_str(ultrasonic.get_error(), errorString, sizeof(errorString));
    Serial.print("Ultrasonic sensor initialized with state : " + String(stateString) + " and error: " + String(errorString) + "\n" );
    Serial.println("Beginning ultrasonic sensor...");
    ultrasonic.begin();
    ultrasonic_sensor::get_state_str(ultrasonic.get_state(), stateString, sizeof(stateString));
    ultrasonic_sensor::get_error_str(ultrasonic.get_error(), errorString, sizeof(errorString));
    Serial.println("Ultrasonic sensor started with state : " + String(stateString) + " and error: " + String(errorString) + "\n" );
    Serial.println("Entering main loop...");
}

void loop() {
  // Need to call update for AsyncSonar!
  ultrasonic.update(); 

  if((millis() - timer) > POLL_INTERVAL){
    timer = millis(); 
  
  ultrasonic_sensor::get_state_str(ultrasonic.get_state(), stateString, sizeof(stateString));
  ultrasonic_sensor::get_error_str(ultrasonic.get_error(), errorString, sizeof(errorString));
  Serial.println("Current ultrasonic sensor state : " + String(stateString) + " and error: " + String(errorString) + "\n" );

  Serial.println("Polling ultrasonic sensor...");
  ultrasonic.poll();

  if (ultrasonic.peek().is_new){
    Serial.println("New ultrasonic sensor data available: ");
    // Print new snsor data
    if(ultrasonic.peek().distance.is_new){
        Serial.println("Distance: " + String(ultrasonic.get_distance().value) + " mm");
    }
    // Clear the data 
    ultrasonic.clear();
  }

  }

}
