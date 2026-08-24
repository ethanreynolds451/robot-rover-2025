// Test script for QMC sensor

#include <Wire.h>
#include "qmcSensor.h"

#include "qmcSensor_codes.h"

uint8_t ADDRESS = 0x0D; 
unsigned long BAUDRATE = 115200;
unsigned long LOOP_DELAY = 500; // Delay between each loop iteration in milliseconds

using qmcSensor = qmc_sensor::qmc_object;

qmcSensor qmc(ADDRESS); 

char stateString[16];   // Buffer to hold the state string for printing
char errorString[16];   // Buffer to hold the error string for printing

void setup() {
  Serial.begin(BAUDRATE); 
  Serial.println("Started serial communication");
  Serial.println("Initializing QMC sensor...");
  qmc.initialize(qmc_sensor::WIRE::START_WIRE);
  qmc_sensor::get_error_str(qmc.get_error(), stateString, sizeof(stateString));
  qmc_sensor::get_error_str(qmc.get_error(), errorString, sizeof(errorString));
  Serial.print("Initialization complete with state: " + String(stateString) + " and error: " + String(errorString) + "\n"); 
  Serial.println("Waiting for I2C initialization");
  delay(100);    // Short delay for I2C initialization
  Serial.println("Beginning QMC sensor...");
  qmc.begin();
  qmc_sensor::get_error_str(qmc.get_error(), stateString, sizeof(stateString));
  qmc_sensor::get_error_str(qmc.get_error(), errorString, sizeof(errorString));
  Serial.print("Begin complete with state: " + String(stateString) + " and error: " + String(errorString) + "\n");
  Serial.println("Entering main loop");
}

void loop() {

  qmc_sensor::get_error_str(qmc.get_error(), stateString, sizeof(stateString));
  qmc_sensor::get_error_str(qmc.get_error(), errorString, sizeof(errorString));
  Serial.print("Current state: " + String(stateString) + " and error: " + String(errorString) + "\n");
  
  Serial.println("Polling QMC sensor...");
  qmc.poll();

  if (qmc.peek().is_new){
    Serial.println("New data available:");

    // Add new snsor data
    if(qmc.peek().direction.is_new){
        Serial.print(" - Direction: " + String(qmc.get_direction().value) + "\n");
    }
    if(qmc.peek().mag.is_new){
      Serial.print(" - Magnetic field: " + String(qmc.get_mag().value.x) + ", " + String(qmc.get_mag().value.y) + ", " + String(qmc.get_mag().value.z) + "\n");
    }

    // Clear the data 
    qmc.clear();
  }

  delay(LOOP_DELAY); // Delay before the next loop iteration

}
