// This file is hardlinked and exists in both control and sensor folders

// Compiled successfully 2025-01-02

#ifndef VOLTAGEDIVIDER_h
#define VOLTAGEDIVIDER_h

#include <Arduino.h>

class linearDivider {
    public:
        linearDivider(uint8_t pin_def, float slope, float intercept) : pin(pin_def), m(slope), b(intercept) {
            pinMode(pin, INPUT);
        };
        void set_pin(uint8_t pin_def){
            pin = pin_def;
            pinMode(pin, INPUT);
        }
        void set_slope(float m_def){
            m = m_def;
        }
        void set_offset(float b_def){
            b = b_def;
        }
        void set(uint8_t pin_def, float m_def, float b_def){
            set_pin(pin_def);
            set_slope(m_def);
            set_offset(b_def);
        }
        inline float read() const { 
            return get_value(); 
        }
    private:
        uint8_t pin;
        float m;
        float b;
        float get_value(){
            float value = analogRead(pin);
            value = m*value + b;
            return value; 
        }
};

class logDivider {
    public:
        logDivider(uint8_t pin_def, float a_def = 1, float b_def = 0) : pin(pin_def), a(a_def), b(b_def) {
            pinMode(pin, INPUT);
        };
        void set_pin(uint8_t pin_def){
            pin = pin_def;
            pinMode(pin, INPUT);
        }
        void set_factor(float a_def){
            a = a_def;
        }
        void set_offset(float b_def){
            b = b_def;
        }
        void set(uint8_t pin_def, float a_def, float b_def){
            set_pin(pin_def);
            set_factor(a_def);
            set_offset(b_def);
        }
        inline float read() const { 
            return get_value(); 
        }
    private:
        uint8_t pin;
        float a;
        float b;
        float get_value(){
            float value = analogRead(pin);
            value = a*log(value) - b;
            return value; 
        }  
};

#endif