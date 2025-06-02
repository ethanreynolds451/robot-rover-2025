#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h


void setup_function(){
    Serial.begin(baud_rate);
    Wire.begin();
}

void update_sensors(){

}

void send_data(){
    Serial.println(data.get());
}

#endif
