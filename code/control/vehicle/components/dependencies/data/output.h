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

    static constexpr Values default_values = { true, false, false, false, 0, 0, 0 };
    Values current = default_values;
    Values input = default_values;

    void reset(){
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