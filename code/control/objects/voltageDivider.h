// This file is hardlinked and exists in both control and sensor

#ifndef THERMISTOR_h
#define THERMISTOR_h

#include "dependencies/libraries.h"

class linearDivider(){
    public:
        linear_divider(uint8_t pin_def, float slope, float intercept) : (pin(pin_def), m(slope), b(intercept) ) {};
        void set_pin(uint8_t pin_def){
            pin = pin_def;
        }
        void set_slope(float m_def){
            m = m_def;
        }
        void set_offset(float b_def){
            b = b_def;
        }
        void set(unit8_t pin_def, float m_def, float b_def){
            pin = pin_def;
            m = m_def;
            b = b_def;
        }
        float read(){
            return get_value();
        }
    private:
        uint8_t pin;
        float m;
        float b;
        float get_value(){
            uint16_t value = analogRead(pin);
            value = m*value + b;
            return value; 
        }
}

class logDivider(){
    public:
        log_divider(uint8_t pin_def, float a_def = 1, float b_def = 0) : (pin(pin_def), a(a_def), b(b_def) ) {};
        void set_pin(uint8_t pin_def){
            pin = pin_def;
        }
        void set_factor(float a_def){
            a = a_def;
        }
        void set_offset(float b_def){
            b = b_def;
        }
        void set(unit8_t pin_def, float a_def, float b_def){
            pin = pin_def;
            a = a_def;
            b = b_def;
        }
        float read(){
            return get_value();
        }
    private:
        uint8_t pin;
        float a;
        float b;
        float get_value(){
            uint16_t value = analogRead(pin);
            value = a*log(value) - b;
            return value; 
        }  
};

#endif