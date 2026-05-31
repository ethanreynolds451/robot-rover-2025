// Test script for motor encoder sensor

#define NO_DYNAMIC_ALLOCATION

#include <Encoder.h>
#include "Encoder/Encoder.h"
#include "motorEncoder.h"
#include "motorEncoder_codes.h"

uint8_t PIN_A = 2; 
uint8_t PIN_B = 3;
unsigned long BAUDRATE = 115200;

using motorEncoder = motor_encoder::encoder_object;

motorEncoder encoder(PIN_A, PIN_B); 

// State string buffer
char stateString[16];

void setup(){
    Serial.begin(BAUDRATE); 
    Serial.println("Serial communication started at baudrate: " + String(BAUDRATE));
    Serial.println("Initializing motor encoder sensor...");
    encoder.initialize();
    motor_encoder::get_state_str(encoder.get_state(), stateString, sizeof(stateString));
    Serial.println("Motor encoder sensor in state: " + String(stateString));
    Serial.println("Starting motor encoder sensor...");
    encoder.begin();
    motor_encoder::get_state_str(encoder.get_state(), stateString, sizeof(stateString));
    Serial.println("Motor encoder sensor in state: " + String(stateString));
}

void loop(){
    motor_encoder::get_state_str(encoder.get_state(), stateString, sizeof(stateString));
    Serial.println("Current motor encoder sensor state: " + String(stateString));

    Serial.println("Polling motor encoder sensor for new data...");
    encoder.poll();

    if (encoder.peek().position.is_new){
        Serial.println("New motor encoder data received:");
        // Add new snsor data
        if(encoder.peek().position.is_new){
            Serial.println(" - Position: " + String(encoder.get_position().value) + " (timestamp: " + String(encoder.peek().position.timestamp) + ")");
        } 

        // Clear the data 
        encoder.clear();
    }
}
