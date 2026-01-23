// Compiled successfully 2026-01-20
// This is a low-level class to manipulate output data
// Not the best style or safest implementation but it works

#ifndef OUTPUTDATA_h
#define OUTPUTDATA_h

// **Class functions**
// reset() -> current vals to default
// set(index, value) -> set any value based on index
// get(index) -> get any value based on index, returns untyped pointer
// index_from_code(code) -> get index from string code
// code_from_index(index) -> get string code from index
// outputData::Index -> enumeration of indecies

class outputData {
  public:
    // Empty constructor for now, may add params later
    outputData(){}
    
    // Function to reset all data values to defaults
    void reset() {
       set_to_defaults(); 
    };

    // Float setter function 
    void set(uint8_t index, float value) {
        // Double check the var trying to set is a float
        if (in(index, float_values)){
            // Set appropriate variable using range offset
            current.float_values[offset(index, float_values)] = value;
        }
    };
    // Overload as needed for different data types

    // Getter function, uses unntyped pointer, MUST CHECK AND CAST AFTER CALLING
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
        INTERNAL_TEMP,
        BATTERY_VOLTAGE,
        BATTERY_PERCENTAGE
    };

  private:
    // Access different data types by index
  
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
    static constexpr uint8_t total[2] = {0,2};
    static constexpr uint8_t float_values[2] = {0,2};


    // Struct for storing output variables
    struct Values {
        float float_values[total[BOUND_MAX] - total[BOUND_MIN] + 1];
    };

    // Designate this as the value returned from an invalid index conversion 
    static constexpr uint8_t index_error = 255; 

    // Define not_measured sentinal values for each variable
    // Because they are sensors, there should be some value outside realistic range to use
    inline static constexpr Values not_measured = {
        // Floats
        { 
            -255.0f,
            -255.0f,
            -255.0f
        }
    };

    // Default to not measured now but open to flexibility if needed
    inline static constexpr Values default_values = not_measured; 

    // Create instance to hold current values, set to default
    Values current = default_values;

    void set_to_defaults(){
        current = default_values;
    }

    // String code for each variable
    static constexpr const char* Code[] = {
        "tmp",
        "vlt",
        "pct"
    };

};


#endif
