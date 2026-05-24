/*
UNITS:
 - Temperature: Celsius (slope and intercept must be calibrated accordingly)
*/

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "voltageDivider/voltageDivider.h"

char outputString[60]; // Buffer for formatted output string

namespace temp_sensor {

class temp_object {
    public:
        temp_object(uint8_t pin, float slope, float intercept) 
        : divider(pin, slope, intercept) {}

        bool begin(){
            // Nothing to do, divider constructor sets the pinMode
            return true;
        }

        // *** Divider parameter setters and getters ***
        void set_pin(uint8_t pin){
            this->pin = pin;
            divider.set_pin(pin);
        }
        uint8_t get_pin(){
            return this->pin;
        }
        void set_slope(float m){
            this->slope = m;
            divider.set_slope(m);
        }
        float get_slope(){
            return this->slope;
        }
        void set_offset(float b){
            this->intercept = b;
            divider.set_offset(b);
        }
        float get_offset(){
            return this->intercept;
        }
        void set(uint8_t pin, float m, float b){
            this->pin = pin;
            this->slope = m;
            this->intercept = b;
            divider.set(pin, m, b);
        }
        
        // *** Control loop functions ***
        bool read(){   
            this->temp_timestamp = millis();
            this->temperature = divider.read(); 
            this->temp_updated = true;
            return true;
        } 
        bool update(){
            return read();
        }

        // *** Data access functions ***
        bool is_new_temp(){
            return this->temp_updated; 
        }
        float get_temp(){
            this->temp_updated = false;
            return this->temperature;
        }
        unsigned long get_temp_timestamp(){
            return this->temp_timestamp;
        }
        unsigned long get_temp_age(){
            return millis() - this->temp_timestamp;
        }

        // *** Maintience functions ***
        void clear(){
            this->temp_updated = false; 
        }
        void reset(){
            this->temperature = 0; 
            this->temp_timestamp = 0;
            this->clear(); 
        }

    private:
        // Sensor parameters 
        uint8_t pin = 0;
        linearDivider divider;
        // Volate divider doesn't expose slope and intercept, so need to track them here
        float slope = 0;
        float intercept = 0;
        // Data
        float temperature = 0;
        bool temp_updated = false;
        unsigned long temp_timestamp = 0;
};
    
}

#endif