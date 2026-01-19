// Compiled successfully 2025-01-02

/*
    Stores components of data and command strings
    Ability to traverse array of codes or access by variable name using indeces
*/

#ifndef OUTPUTCODES_h
#define OUTPUTCODES_h

namespace OutputCodes {
    static constexpr uint8_t device_ID = 0x00; 

    namespace Delimiter {
        static constexpr char* start = "{";
        static constexpr char* end = "}";
        static constexpr char* v_start = "[";
        static constexpr char* v_end = "]";
        static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)
    }

    namespace Data {
        // {tmp[0]vlt[0]pct[0]}
        static constexpr uint8_t number_of = 3; 

        enum Index : uint8_t {
            internal_temp,
            battery_voltage,
            battery_percentage
        }

        static constexpr const char* str[] = {
            "tmp",
            "vlt",
            "pct"
        };
    }  
};

#endif