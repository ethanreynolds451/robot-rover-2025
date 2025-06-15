#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

void setup_function(){
    Serial.begin(baudrate);
    Serial.println("Starting setup"); 
    Wire.begin();
    Wire.setTimeout(50); 
    start_pcf(); 
    sensor.begin();     // this will call begin on any objects that require this and assign I2C addresses to the lof sensors
    Serial.println("Setup complete"); 
}

void update_sensors(){
    sensor.read_all();
}

void send_data(){
    Serial.println(data.get());
}



#endif
