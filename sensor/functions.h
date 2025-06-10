#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

void setup_function(){
    Serial.begin(baudrate);
    Wire.begin();
    PCF.begin();
    sensor.begin();     // this will call begin on any objects that require this and assign I2C addresses to the lof sensors
}

void update_sensors(){
    sensor.read_all();
}

void send_data(){
    Serial.println(data.get());
}



#endif
