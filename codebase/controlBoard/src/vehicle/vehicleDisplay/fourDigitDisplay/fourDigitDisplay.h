// Compiled successfully 2025-01-02

#ifndef FOURDIGITDISPLAY_h
#define FOURDIGITDISPLAY_h

// Include library in the main library header file
// Uncomment to debug only this file

// #include <i2cdisplaycontroller.h>

class fourDigitDisplayPCF {
    public:
        fourDigitDisplayPCF(
            uint8_t address,
            uint8_t pin1,
            uint8_t pin2,
            uint8_t pin3,
            uint8_t pin4
        )
        : address(address), display(address)
        {
            digit_pins[0] = pin1;
            digit_pins[1] = pin2;
            digit_pins[2] = pin3;
            digit_pins[3] = pin4;

            for (int i = 0; i < 4; i++) {
                pinMode(digit_pins[i], OUTPUT);
                digitalWrite(digit_pins[i], LOW);
            }

        }
        void begin(){
            this->display.begin();              // Initialize I2C communication
        }
        void set_address(uint8_t address){
            this->address = address;
            this->display = I2CDisplayController(address);
        }
        void set_common_annode(bool is_common_anode){
            // stated function name in library is wrong, this one actually sets value of isCommonAnnode
            this->display.setDisplayConfiguration(is_common_anode);
        }
        void set_delay(unsigned long delay_time){
            this->display.setDelay(delay_time);
        }
        void print_digit(uint8_t digit, uint8_t position){
            if(position < 1 || position > 4) return; // Invalid position
            if(digit > 15) return; // Invalid digit
            this->display.print(digitToSegment[digit], digit_pins[position - 1]);
        }
        void set_decimal_point(uint8_t position, bool state){
            this->display.setDecimalPoint(DECIMAL_PIN, position, state);
        }
        void clear_decimal_point(){
            for (int i = 0; i < 4; i++) {
                this->display.setDecimalPoint(DECIMAL_PIN, digit_pins[i], false);
            }
        }
        void print_integer(uint16_t number){
            if (number > 9999){
                print_digit(0b01111001, 2);
                print_digit(0b01110011, 3);
                print_digit(0b01110011, 4);
            }; // Print "Err" for numbers > 9999
            clear_decimal_point();
            uint16_t divisors[] = {1000, 100, 10, 1};
            for (uint8_t i = 0; i < 4; i++) {
                uint8_t digit = (number / divisors[i]) % 10;
                print_digit(digit, i + 1);
            }
        }
        void print_decimal(float number){
            uint16_t integer_component = static_cast<uint16_t>(number);
            uint16_t digits;
            uint8_t decimal_place;

            if (integer_component > 999) {
                // 4-digit integer, no decimal
                digits = integer_component;
                decimal_place = 4; // no decimal point
            } else if (integer_component > 99) {
                // 3-digit integer → 1 decimal place
                digits = static_cast<uint16_t>(round(number * 10));
                decimal_place = 3;
            } else if (integer_component > 9) {
                // 2-digit integer → 2 decimal places
                digits = static_cast<uint16_t>(round(number * 100));
                decimal_place = 2;
            } else {
                // 1-digit integer → 3 decimal places
                digits = static_cast<uint16_t>(round(number * 1000));
                decimal_place = 1;
            }
            clear_decimal_point();
            print_integer(digits);           // print as 4-digit integer
            if (decimal_place < 4) {         // only set decimal if needed
                set_decimal_point(decimal_place, true);
            }
        }   
    private:
        I2CDisplayController display;
        uint8_t address;
        uint8_t digit_pins[4];
        static constexpr uint8_t DECIMAL_PIN = 7;
        const uint8_t digitToSegment[16] = {
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
    // display.setCommonAnode(true); actually setDisplayConfiguration(true);
    // display.setDecimalPoint(decimal_pin, switching_pin, status);
    // display.begin(); //connection with PCF8575
    // display.setDelay(500);
    // display.getdelay();
    // display.print(digitToSegment[i], DISPLAY_1);