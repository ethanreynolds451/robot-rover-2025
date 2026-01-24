#ifndef INPUTCODE_h
#define INPUTCODE_h

// This namespace facilitates conversions between string command codes and their associated index values

namespace InputCode {
    static constexpr char* brake = "br";
    static constexpr char* reverse = "rv";
    static constexpr char* s_reverse = "srv";
    static constexpr char* shift_up = "su";
    static constexpr char* speed = "sp";
    static constexpr char* s_speed = "ssp";
    static constexpr char* f_speed = "fan";

    // This must match the order of inputData::Index
    static constexpr const char* Indexed[] = {
        brake,
        reverse,
        s_reverse,
        shift_up,
        speed,
        s_speed,
        f_speed
    };

    static constexpr uint8_t index_error = 255;

    // Data code management translator helper functions
    uint8_t code_to_index(const char* code){
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