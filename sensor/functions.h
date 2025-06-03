#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h


void setup_function(){
    Serial.begin(baud_rate);
    Wire.begin();
    Sensor.initialize(); 
}

void update_sensors(){
    sensor.read_all(); 
}

void send_data(){
    Serial.println(data.get());
}

#endif
