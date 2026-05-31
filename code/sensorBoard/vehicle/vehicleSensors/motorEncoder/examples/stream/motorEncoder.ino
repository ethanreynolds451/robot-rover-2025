// Stream encoder data in ROS sensor string parser format
// Streams as encoder 0, which maps to the steering encoder data topic

#include <Encoder.h>
#include "Encoder/Encoder.h"
#include "motorEncoder.h"

uint8_t PIN_A = 2; 
uint8_t PIN_B = 3;
unsigned long BAUDRATE = 115200;

using motorEncoder = motor_encoder::encoder_object;

motorEncoder encoder(PIN_A, PIN_B); 

// Buffer to hold the output string
char outputString[60];

uint8_t sign_bit(long value){
    return (value < 0) ? 1 : 0;
}

void setup(){
    Serial.begin(BAUDRATE); 
    encoder.initialize();
    encoder.begin();
}

void loop(){
    encoder.poll();

    if (encoder.peek().position.is_new){

        // Calculate timestamps and offsets for the packet
        unsigned long arduino_timestamp = millis();
        unsigned long offset_timestamp = arduino_timestamp - encoder.peek().position.timestamp;
        
        // Prepare the output string
        memset(outputString, 0, sizeof(outputString));
        int pos = 0;

        // Add the arduino timestamp and sensor header data to the string
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "enc[n:0");
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x0", static_cast<uint8_t>(encoder.get_state()));

        // Add new snsor data
        if(encoder.peek().position.is_new){
          pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",p:%x;%x", sign_bit(encoder.get_position().value), abs(encoder.get_position().value));
        } 

        // End the packet and send over serial
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);

        // Clear the data 
        encoder.clear();
    }
}
