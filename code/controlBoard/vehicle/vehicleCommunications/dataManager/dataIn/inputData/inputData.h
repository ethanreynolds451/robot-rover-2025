#ifndef INPUTDATA_h
#define INPUTDATA_h

class inputData(){
  public: 
    inputData(){}

    void reset() {
        current = default_values
    };
       
    void reset_input() {
        input_buffer = default_values;
    };

    bool validate_input(){
        return (
            // Unsigned ints always >= 0
            (input_buffer.speed <= 100) &&
            (input_buffer.s_speed <= 100) &&
            (input_buffer.f_speed <= 100)
        );
    }

    bool set_from_input(){
        if(validate_input()){
            current = input_buffer;
            return true;
        }
        return false; 
    }

    void commit_buffer() {
        current = input_buffer;
    };

    // Assign an individual value in current data struct
    void set(uint8_t index, uint8_t value) {
        set(index, value, &input_buffer);
    };

    // Assign an individual value in buffer data struct
    void set_buffer(uint8_t index, bool value) {
        set(index, value, &input_buffer);
    };


    void* get(uint8_t index){
        // Make sure the index is valid
        if (in(index, total)){
            // Return a float if in the float range
            if (in(index, float_values)){
                return &current.float_values[offset(index, float_values)];
            }
        }
        return nullptr;
    };


    // Data code management translator helper functions
    uint8_t index_from_code(char* code){
        uint8_t number = count(total);
        for (uint8_t i = 0; i < number; i++){
            if (!strcmp(code, Code[i])){
                return i;
            }
        }
        // Make sure to account for signed error value 
        return index_error;
    };

    char* code_from_index(uint8_t index){
        uint8_t number = count(total);
        if (index < number){
            return this->Code[index];
        }
        // Make sure to account for empty string as error value
        return ""; 
    };

    // Ordered indicies
    enum Index : uint8_t {
        BRAKE,
        REVERSE,
        S_REVERSE,
        SHIFT_UP, 
        SPEED,
        S_SPEED,
        F_SPEED
    };

  private:

    enum Bound {
        BOUND_MIN,
        BOUND_MAX
    };
    bool in(uint8_t index, uint8_t range[2]) {
        return ((index >= range[BOUND_MIN]) && (index <= range[BOUND_MAX]));
    };
    uint8_t offset(uint8_t index, uint8_t range[2]){
        return index - range[BOUND_MIN];
    };
    uint8_t count(uint8_t range[2]) {
        return (range[BOUND_MAX] - range[BOUND_MIN] + 1);
    };
    static constexpr uint8_t total[2] = {0,6};
    static constexpr uint8_t bool_values[2] = {0,3};
    static constexpr uint8_t uint8_t_values[2] = {4,6};

    // Struct for storing output variables
    struct Values {
        bool bool_values[bool_values[BOUND_MAX] - bool_values[BOUND_MIN] + 1];
        uint8_t uint8_t_values[uint8_t_values[BOUND_MAX] - uint8_t_values[BOUND_MIN] + 1];
    };


    inline static constexpr Values default_values = {
        // Bools
        { 
            true,
            false,
            false, 
            false
        }, 
        // uint8_t
        {
            0,
            0,
            0
        }
    };

    Values current = default_values;
    Values input_buffer = default_values;

    // Bool setter function 
    void set(uint8_t index, bool value, Values *target) {
        // Double check the var trying to set is a float
        if (in(index, bool_values)){
            // Set appropriate variable using range offset
            target->float_values[offset(index, bool_values)] = value;
        }
    };
    // uint8_t setter function 
    void set(uint8_t index, uint8_t value, Values *target) {
        // Double check the var trying to set is a float
        if (in(index, uint8_t_values)){
            // Set appropriate variable using range offset
            target->float_values[offset(index, uint8_t_values)] = value;
        }
    };
    // Overload as needed for different data types

    static constexpr const char* Code[] = {
        "br",
        "rv",
        "srv",
        "su",
        "sp",
        "ssp",
        "fan"
    };

};

#endif

// struct Values {
//     bool brake;
//     bool reverse;
//     bool s_reverse;
//     bool shift_up;
//     uint8_t speed;
//     uint8_t s_speed;
//     uint8_t f_speed;
// };



    // Check values and index bounds elsewhere, this is a low-level function to reduce code duplication
    // This allows the different data types to be handled differently if needed
    void set_by_index(Values *value_struct, uint8_t index, const char* value_string){
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

    

   


