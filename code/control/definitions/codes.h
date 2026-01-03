// Compiled successfully 2025-01-02

/*
    Stores components of data and command strings
    Ability to traverse array of codes or access by variable name using indeces
*/

#ifndef CODES_h
#define CODES_h

namespace Code {
    static constexpr uint8_t device_ID = 0x00; 

    struct code_struct {         // Structure for code mapping
      uint8_t index;
      char code[4];              // max 3 chars, includes null terminator
    };

    namespace Delimiter {
        static constexpr char start_designator = '{';
        static constexpr char end_designator = '}';
        static constexpr char value_start_designator = '[';
        static constexpr char value_end_designator = ']';
    }

    namespace Command {
        // {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}
        static constexpr uint8_t number_of = 7;

        static constexpr code_struct key[number_of] PROGMEM = {
            {0, "br"},
            {1, "rv"},
            {2, "srv"},
            {3, "su"},
            {4, "sp"},
            {5, "ssp"},
            {6, "fan"}
        };

        namespace Index {
            static constexpr uint8_t brake = 0;
            static constexpr uint8_t reverse = 1;
            static constexpr uint8_t steering_reverse = 2;
            static constexpr uint8_t shift_up = 3;
            static constexpr uint8_t speed = 4;
            static constexpr uint8_t steering_speed = 5;
            static constexpr uint8_t fan = 6;
        }

    }

    namespace Data {
        // {tmp[0]vlt[0]pct[0]}
        static constexpr uint8_t number_of = 3; 

        namespace Index {
            static constexpr uint8_t internal_temp = 0;
            static constexpr uint8_t battery_voltage = 1;
            static constexpr uint8_t vattery_percent = 2;
        }

        static constexpr code_struct key[number_of] PROGMEM = {
            {0, "tmp"},
            {1, "vlt"},
            {2, "pct"}
        };
    }  
};

#endif