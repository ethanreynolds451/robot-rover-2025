// Debug script for IR sensor

#include "irSensor.h"

#include "irSensor_codes.h"

uint8_t IR_PIN = 4; 
unsigned long BAUDRATE = 115200;
size_t loop_delay = 500; 

using irSensor = ir_sensor::ir_object;

irSensor testIR(IR_PIN, ir_sensor::LED::LED_OFF); 

char stateString[16];

void setup() {
  Serial.begin(BAUDRATE); 
  Serial.println("Serial communication started at baudrate: " + String(BAUDRATE));
  Serial.println("Initializing IR sensor...");
  testIR.initialize();
  ir_sensor::get_state_str(testIR.get_state(), stateString, sizeof(stateString));
  Serial.println("IR sensor in state: " + String(stateString));
  Serial.println("Starting IR sensor...");
  testIR.begin();
  ir_sensor::get_state_str(testIR.get_state(), stateString, sizeof(stateString));
  Serial.println("IR sensor in state: " + String(stateString));
}

void loop() {
  // Get the current state of the sensor
  ir_sensor::get_state_str(testIR.get_state(), stateString, sizeof(stateString));
  Serial.println("Current IR sensor state: " + String(stateString));

  // Poll the sensor
  Serial.println("Polling IR sensor for new data...");
  testIR.poll();

  // Check for new data
  if (testIR.peek().is_new){
    Serial.println("New IR data received:");
    // Print new data
    if(testIR.peek().command.is_new){
        Serial.println(" - Command: " + String(irSensor.get_command().value) + " (timestamp: " + String(testIR.peek().command.timestamp) + ")");
    }
    if(testIR.peek().address.is_new){
        Serial.println(" - Address: " + String(irSensor.get_address().value) + " (timestamp: " + String(testIR.peek().address.timestamp) + ")");
    }
    if(testIR.peek().raw_data.is_new){
        Serial.println(" - Raw Data: " + String(irSensor.get_data().value) + " (timestamp: " + String(testIR.peek().raw_data.timestamp) + ")");
    }
    testIR.clear();
  }
  delay(loop_delay);
}
