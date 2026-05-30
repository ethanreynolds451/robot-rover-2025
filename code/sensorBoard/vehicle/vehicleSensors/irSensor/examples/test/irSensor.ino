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
  // Poll the sensor
  testIR.poll();

  // Get the current state of the sensor
  ir_sensor::get_state_str(testIR.get_state(), stateString, sizeof(stateString));
  Serial.println("Current IR sensor state: " + String(stateString));

  // Check for new data
  ir_sensor::DATA data = testIR.peek();
  if (data.command.is_new || data.address.is_new || data.raw_data.is_new){
    Serial.println("New IR data received:");

    // Print new data
    if(data.command.is_new){
        Serial.println(" - Command: " + String(data.command.value) + " (timestamp: " + String(data.command.timestamp) + ")");
    }
    if(data.address.is_new){
        Serial.println(" - Address: " + String(data.address.value) + " (timestamp: " + String(data.address.timestamp) + ")");
    }
    if(data.raw_data.is_new){
        Serial.println(" - Raw Data: " + String(data.raw_data.value) + " (timestamp: " + String(data.raw_data.timestamp) + ")");
    }

    testIR.clear();
  }
  delay(loop_delay);
}
