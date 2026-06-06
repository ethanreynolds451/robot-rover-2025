#include "tofSensor.h"

#include "tofSensor_codes.h"

uint8_t ADDRESS = 0x30; // Just a random address to verify that reassignment works
unsigned long BAUDRATE = 115200;
unsigned long LOOP_DELAY = 500;

using tofSensor = tof_sensor::tof_object;

tofSensor tof(ADDRESS); 

char stateString[16];
char errorString[16];

void setup() {
  Serial.begin(BAUDRATE); 
  Serial.println("Serial communication started");
  Serial.println("Initializing ToF sensor...");
  // This does the blocking address reasignment
  tof.initialize(tof_sensor::WIRE::START_WIRE);
  tof_sensor::get_state_str(tof.get_state(), stateString, sizeof(stateString));
  tof_sensor::get_error_str(tof.get_error(), errorString, sizeof(errorString));
  Serial.println("ToF sensor initialized with state: " + String(stateString) + " and error: " + String(errorString));
  Serial.println("Waiting 100ms before starting sensor...");
  delay(100);    // Short delay for I2C initialization
  Serial.println("Starting ToF sensor...");
  tof.begin();
  tof_sensor::get_state_str(tof.get_state(), stateString, sizeof(stateString));
  tof_sensor::get_error_str(tof.get_error(), errorString, sizeof(errorString));
  Serial.println("ToF sensor started with state: " + String(stateString) + " and error: " + String(errorString));
  Serial.println("Entering main loop...");
}

void loop() {

  tof_sensor::get_state_str(tof.get_state(), stateString, sizeof(stateString));
  tof_sensor::get_error_str(tof.get_error(), errorString, sizeof(errorString));
  Serial.println("Current state: " + String(stateString) + ", Current error: " + String(errorString));

  Serial.println("Polling ToF sensor...");
  tof.poll();

  if (tof.peek().is_new){
    Serial.println("New data available from ToF sensor:");
    // Print new snsor data
    if(tof.peek().range.is_new){
      Serial.println(" - Range: " + String(tof.get_range().value));
    }
    if(tof.peek().background_rate.is_new){
      Serial.println(" - Background Rate: " + String(tof.get_background_rate().value));
    }
    if(tof.peek().signal_rate.is_new){
      Serial.println(" - Signal Rate: " + String(tof.get_signal_rate().value));
    }
    if(tof.peek().signal_quality.is_new){
      Serial.println(" - Signal Quality: " + String(tof.get_signal_quality().value));
    }
    
    // Clear the data 
    tof.clear();
  }

  delay(LOOP_DELAY);

}
