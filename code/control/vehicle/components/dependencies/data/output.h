#ifndef OUTPUT_h
#define OUTPUT_h

namespace OutputStates {
    struct Values {
        bool brake;
        bool reverse;
        bool s_reverse;
        bool shift_up;
        uint8_t speed;
        uint8_t s_speed;
        uint8_t f_speed;
    };

    static constexpr uint8_t max_length = 4;    // Length of longest value AS STRING including null terminator (3 digits)

    static constexpr Values default_values = { true, false, false, false, 0, 0, 0 };
    Values current = default_values;
    Values input_buffer = default_values;

    // Check values and index bounds elsewhere, this is a low-level function to reduce code duplication
    // This allows the different data types to be handled differently if needed
    void set_by_index(Values *value_struct, unit8_t index, const char* value_string){
        switch(index){
            case 0:
                value_struct->brake = atoi(value_string);
                break;
            case 1:
                value_struct->reverse = atoi(value_string);
                break;
            case 2:
                value_struct->s_reverse = atoi(value_string);
                break;
            case 3:
                value_struct->shift_up = atoi(value_string);
                break;
            case 4:
                value_struct->speed = atoi(value_string);
                break;
            case 5:
                value_struct->s_speed = atoi(value_string);
                break;
            case 6:
                value_struct->f_speed = atoi(value_string);
                break;
            default: 
                break;
        };
    }

    void reset() {
        current = default_values;
    }

    void reset_input(){
       input = default_values;
    }

    bool validate_input(){
        return (
            // Unsigned ints always >= 0
            (input.speed <= 100) &&
            (input.s_speed <= 100) &&
            (input.f_speed <= 100)
        );
    }

    bool set_from_input(){
        if(validate_input()){
            current = input;
            return true;
        }
        return false; 
    }
}

#endif