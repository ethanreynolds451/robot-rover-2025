// Compiled successfully 2025-01-02

/*
    Stores components of data and command strings
    Ability to traverse array of codes or access by variable name using indeces
*/

#ifndef CODES_h
#define CODES_h

namespace Code {
    static constexpr uint8_t device_ID = 0x00; 

    namespace Delimiter {
        static constexpr char* start = "{";
        static constexpr char* end = "}";
        static constexpr char* v_start = "[";
        static constexpr char* v_end = "]";
        static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)
    }

    namespace Command {
        // {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}
        static constexpr uint8_t number_of = 7;
        static constexpr uint8_t max_length = 4;    // Max length of command strings including null terminator (3 letters)

        static constexpr const char* str[] = {
            "br",
            "rv",
            "srv",
            "su",
            "sp",
            "ssp",
            "fan"
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
            static constexpr uint8_t battery_percentage = 2;
        }

        static constexpr const char* str[] = {
            "tmp",
            "vlt",
            "pct"
        };
    }  
};

#endif