// Compiled successfully 2025-01-02

/*
    Stores components of data and command strings
    Ability to traverse array of codes or access by variable name using indeces
*/

#ifndef OUTPUTCODES_h
#define OUTPUTCODES_h

namespace OutputCodes {
    // Communication parsing delimiters
    namespace Delimiter {
        static constexpr char* start = "{";
        static constexpr char* end = "}";
        static constexpr char* v_start = "[";
        static constexpr char* v_end = "]";
        static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)
    }

    // Data codes
    namespace Data {
        // {tmp[0]vlt[0]pct[0]}
        static constexpr uint8_t number_of = 3; 

        // The index of each data variable
        enum Index : uint8_t {
            INTERNAL_TEMP,
            BATTERY_VOLTAGE,
            BATTERY_PERCENTAGE
        }

        // String code for each variable
        static constexpr const char* str[] = {
            "tmp",
            "vlt",
            "pct"
        };

        // Make sure to account for signed int return val when using
        int8_t index_from_code(char* code){
            for (uint8_t i = 0; i < number_of; i++){
                if (!strcmp(code, str[i])){
                    return i;
                }
            }
            return -1;
        }

        char* code_from_index(uint8_t index){
            return str[index];
        }

    }  
};

#endif