#ifndef INPUTDATA_h
#define INPUTDATA_h

// This class simulates array manipulation for different data types by using ranges and offsets

// **Class functions**
// reset() -> current vals to default vals
// reset_input() -> buffer vals to default vals
// commit_buffer() -> current vals to buffer vals no validation
// validate_input() -> check if buffer vals are valid
// set_from_input() -> if buffer vals valid, set current vals to buffer vals
// set(index, value) -> set any value based on index
// get(index) -> get any value based on index, returns untyped pointer
// index_from_code(code) -> get index from string code
// code_from_index(index) -> get string code from index
// inputData::Index -> enumeration of indecies

class inputData {
  public: 
    inputData(){}
    enum Bound {
        BOUND_MIN,
        BOUND_MAX
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

    size_t max_length = 4;    // Max length of value as string including null terminator   

    static constexpr uint8_t total[2] = {0,6};
    static constexpr uint8_t bool_values[2] = {0,3};
    static constexpr uint8_t uint8_t_values[2] = {4,6};

    // Struct for storing output variables
    struct Values {
        bool bool_values[bool_values[BOUND_MAX] - bool_values[BOUND_MIN] + 1];
        uint8_t uint8_t_values[uint8_t_values[BOUND_MAX] - uint8_t_values[BOUND_MIN] + 1];
    };

    void reset() {
        current = default_values;
    };
       
    void reset_input() {
        input_buffer = default_values;
    };

    void commit_buffer() {
        current = input_buffer;
    };

    bool validate_input(){
        return (
            // Unsigned ints always >= 0
            (*(uint8_t*)get_internal(SPEED, &input_buffer) <= 100) &&
            (*(uint8_t*)get_internal(S_SPEED, &input_buffer) <= 100) &&
            (*(uint8_t*)get_internal(F_SPEED, &input_buffer) <= 100)
        );
    }

    bool set_from_input(){
        if(validate_input()){
            current = input_buffer;
            return true;
        }
        return false; 
    }

    // Assign an individual value in current data struct
    void set_buffer(uint8_t index, uint8_t value) {
        set_internal(index, value, &input_buffer);
    };

    // Assign an individual value in buffer data struct
    void set_current(uint8_t index, bool value) {
        set_internal(index, value, &current);
    };

    // Need these getter functions because actual data structs are private
    void* get_current(uint8_t index){
        return get_internal(index, &current);
    };

    void* get_default(uint8_t index){
        return get_internal(index, &default_values);
    };

    void* get_buffer(uint8_t index){
        return get_internal(index, &input_buffer);
    };

  private:
    bool in(uint8_t index, uint8_t range[2]) {
        return ((index >= range[BOUND_MIN]) && (index <= range[BOUND_MAX]));
    };
    uint8_t offset(uint8_t index, uint8_t range[2]){
        return index - range[BOUND_MIN];
    };
    uint8_t count(uint8_t range[2]) {
        return (range[BOUND_MAX] - range[BOUND_MIN] + 1);
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
    void set_internal(uint8_t index, bool value, Values *target) {
        // Double check the var trying to set is a float
        if (in(index, bool_values)){
            // Set appropriate variable using range offset
            target->bool_values[offset(index, bool_values)] = value;
        }
    };
    // uint8_t setter function 
    void set_internal(uint8_t index, uint8_t value, Values *target) {
        // Double check the var trying to set is a float
        if (in(index, uint8_t_values)){
            // Set appropriate variable using range offset
            target->uint8_t_values[offset(index, uint8_t_values)] = value;
        }
    };
    // Overload as needed for different data types

    // Getter function, uses unntyped pointer, MUST CHECK AND CAST AFTER CALLING
    void* get_internal(uint8_t index, Values *target){
        // Make sure the index is valid
        if (in(index, total)){
            // Return a bool if in the range
            if (in(index, bool_values)){
                return &target->bool_values[offset(index, bool_values)];
            }
            // Return a uint8_t if in the range
            if (in(index, uint8_t_values)){
                return &target->uint8_t_values[offset(index, uint8_t_values)];
            }
        }
        return nullptr;
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


