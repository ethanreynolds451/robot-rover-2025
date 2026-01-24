#ifndef OUTPUTCODE_h
#define OUTPUTCODE_h

namespace OutputCode {
    static constexpr char* internal_temp = "tmp";
    static constexpr char* battery_voltage = "vlt";
    static constexpr char* battery_percentage = "pct";

   // String code for each variable
    static constexpr const char* Indexed[] = {
        internal_temp,
        battery_voltage,
        battery_percentage
    };

    static constexpr uint8_t index_error = 255; 

    // Data code management translator helper functions
    uint8_t code_to_index(char* code){
        uint8_t number = sizeof(Indexed) / sizeof(Indexed[0]);
        for (uint8_t i = 0; i < number; i++){
            if (!strcmp(code, Indexed[i])){
                return i;
            }
        }
        return index_error;
    };

    char* index_to_code(uint8_t index){
        uint8_t number = sizeof(Indexed) / sizeof(Indexed[0]);
        if (index < number){
            return Indexed[index];
        }
        // Make sure to account for empty string as error value
        return ""; 
    };
};

#endif