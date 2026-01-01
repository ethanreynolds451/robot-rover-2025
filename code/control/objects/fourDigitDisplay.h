#ifndef FOURDIGITDISPLAY_h
#define FOURDIGITDISPLAY_h

#include "dependencies/libraries.h"

class fourDigitDisplayPCF {
    public:
        fourDigitDisplayPCF(
        uint8_t address_def,
        uint8_t pin1,
        uint8_t pin2,
        uint8_t pin3,
        uint8_t pin4
        )
        : display(address_def)
        {
            digit_pins[0] = pin1;
            digit_pins[1] = pin2;
            digit_pins[2] = pin3;
            digit_pins[3] = pin4;
        }
        void set_polarity(char* polarity){
            if(strcmp(polarity, "common_anode") == 0){
                display.setCommonAnode(true);
            } else if(strcmp(polarity, "common_cathode") == 0){
                display.setCommonAnode(false);
            }
        }
        void begin(){
            display.begin();
            for (int i = 0; i < 4; i++) {
                pinMode(digit_pins[i], OUTPUT);
                digitalWrite(digit_pin[i], LOW);
            }
        }
        void set_delay(unsigned long delay_time){
            display.setDelay(delay_time);
        }
        void print_digit(uint8_t digit, uint8_t position){
            if(position < 1 || position > 4) return; // Invalid position
            display.print(digitToSegment[digit], digit_pins[position - 1]);
        }
        void set_decimal_point(uint8_t position, bool state){
            display.setDecimalPoint(7, position, status);
        }
        // assumes configuration with decimal pin on PCF pin 07
        void clear_decimal_point(){
            for (int i = 0; i < 4; i++) {
                display.setDecimalPoint(7, digit_pins[i], false);
            }
        }
        void print_integer(uint16_t number){
            if (number > 9999){
                print_digit(0b01111001, 2);
                print_digit(0b01110011, 3);
                print_digit(0b01110011, 4);
            }; // Print "Err" for numbers > 9999
            clear_decimal_point();
            for (int i = 0; i < 4; i++) {
                uint8_t digit = (number / pow(10, 3 - i)) % 10;
                print_digit(digit, i + 1);
            }
        }
        void print_decimal(float number){
            int integer_component = (int)number;
            int digits;
            int decimal_place;
            if(integer_component > 999) {
                digits = integer_component;
                decimal_place = 4; // No decimal point
            } else if(integer_component > 99){
                digits = integer_component * 10 + (int)((number - integer_component) * 10) % 10;
                decimal_place = 3;
            } else if(integer_component > 9){
                digits = integer_component * 100 + (int)((number - integer_component) * 100) % 100;
                decimal_place = 2;
            } else {
                digits = integer_component * 1000 + (int)((number - integer_component) * 1000) % 1000;
                decimal_place = 1;
            }
            print_integer(digits);
            clear_decimal_point();
            set_decimal_point(decimal_place, true);
        }
    private:
        I2CDisplayController display;
        int address;
        uint8_t digit_pins[4];
        const uint8_t digitToSegment[] = {
            // XGFEDCBA
            0b00111111,    // 0
            0b00000110,    // 1
            0b01011011,    // 2
            0b01001111,    // 3
            0b01100110,    // 4
            0b01101101,    // 5
            0b01111101,    // 6
            0b00000111,    // 7
            0b01111111,    // 8
            0b01101111,    // 9
            0b01110111,    // A
            0b01111100,    // b
            0b00111001,    // C
            0b01011110,    // d
            0b01111001,    // E
            0b01110001     // F
        };
};

#endif

// Functions in the source library:
    // I2CDisplayController display(pcf_address);
    // display.setDigitsPort(portselect);
    // display.setCommonAnode(true);
    // display.setDecimalPoint(decimal_pin, switching_pin, status);
    // display.begin(); //connection with PCF8575
    // display.setDelay(500);
    // display.getdelay();
    // display.print(digitToSegment[i], DISPLAY_1);