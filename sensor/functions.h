#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h


void setup_function(){
    Serial.begin(baud_rate);
    Wire.begin();
    Sensor.begin();     // this will call begin on any objects that require this and assign I2C addresses to the lof sensors
}

void update_sensors(){
    sensor.read_all(); 
}

void send_data(){
    Serial.println(data.get());
}

void set_pinmodes(){
    pinMode(Pin::HCSR04[0], OUTPUT);
    for(int i = 1; i < number_of_HCSR04; i++){
        pinMode(Pin::HCSR04[i], INPUT);
    }
    for(int i = 0; i < number_of_lof; i++){
        pinMode(Pin::x_shut[i], OUTPUT);
    }
    pinMode(Pin::steer_position, INPUT);
    pinMode
}

#endif
