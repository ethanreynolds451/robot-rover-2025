#ifndef FOURDIGITDISPLAY_h
#define FOURDIGITDISPLAY_h

#include "dependencies/libraries.h"

class fourDigitDisplayPCF {
    public:
        fourDigitDisplayPCF(uint8_t address_def, scl_def, sda_def, pin1, pin2, pin3, pin4) : (address, scl, sda, digit_pins[0], digit_pins[1], digit_pins[2], digit_pins[3]){}
        void begin(){
            Wire.begin(scl, sda);
            display.begin();
            for (int i = 0; i < 4; i++) {
                pinMode(digit_pins[i], OUTPUT);
                digitalWrite(digit_pin[i], LOW);
            }
        }
    private:
        int address;
        uint8_t scl;
        uint8_t sda;
        uint8_t digit_pins[4];

        
};

#endif