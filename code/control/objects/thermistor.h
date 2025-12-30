#ifndef THERMISTOR_h
#define THERMISTOR_h

#include "dependencies/libraries.h"

class log_thermistor(){
    public:
        log_thermistor(pin_def, a_def, b_def){};
        read(){
            return get_temperature();
        }
    private:
        uint8_t pin;
        float a;
        float b;
        get_temperature(){
            uint16_t temp = analogRead(pin);
            temp = a*log(temp) - b;
            return temp; 
        }  
};

#endif