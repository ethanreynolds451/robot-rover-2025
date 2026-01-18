// This file is hardlinked and exists in both control and sensor folders

// Compiled successfully 2025-01-02

#ifndef VOLTAGEDIVIDER_h
#define VOLTAGEDIVIDER_h

#include <Arduino.h>

class linearDivider {
    public:
        linearDivider(uint8_t pin, float slope, float intercept) : pin(pin), m(slope), b(intercept) {
            pinMode(pin, INPUT);
        };
        void set_pin(uint8_t pin){
            this->pin = pin;
            pinMode(pin, INPUT);
        }
        void set_slope(float m){
            this->m = m;
        }
        void set_offset(float b){
            this->b = b;
        }
        void set(uint8_t pin, float m, float b){
            set_pin(pin);
            set_slope(m);
            set_offset(b);
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
        logDivider(uint8_t pin, float a = 1, float b = 0) : pin(pin), a(a), b(b) {
            pinMode(pin, INPUT);
        };
        void set_pin(uint8_t pin){
            this->pin = pin;
            pinMode(pin, INPUT);
        }
        void set_factor(float a){
            this->a = a;
        }
        void set_offset(float b){
            this->b = b;
        }
        void set(uint8_t pin, float a, float b){
            set_pin(pin);
            set_factor(a);
            set_offset(b);
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