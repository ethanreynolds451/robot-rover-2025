// This is a low-level class to manipulate output data

#ifndef OUTPUTDATA_h
#define OUTPUTDATA_h

// **Class functions**
// reset() -> current vals to default
// set(index, value) -> set any value based on index
// get(index) -> get any value based on index, returns untyped pointer
// index_from_code(code) -> get index from string code
// code_from_index(index) -> get string code from index

class outputData {
  public:
    // Empty constructor for now, may add params later
    outputData(){}
    
    // Function to reset all data values to defaults
    void reset() {
       this->current = this->default_values;
    };

    // Float setter function 
    void set(uint8_t index, float value) {
        // Double check the var trying to set is a float
        if (Range::in(index, Range::float_values)){
            // Set appropriate variable using range offset
            current.float_values[Range::offset(index, Range::float_values)] = value;
        }
    };
    // Overload as needed for different data types


    // Getter function, uses unntyped pointer, MUST CHECK AND CAST AFTER CALLING
    void* get(uint8_t index){
        // Make sure the index is valid
        if (Range::in(index, Range::total)){
            // Return a float if in the float range
            if (Range::in(index, Range::float_values)){}
                return &current.float_values[Range::offset(index, Range::float_values)];
            }
        }
        return nullptr;
    };

    // Overload as needed for different data types


    // Data code management translator helper functions
    uint8_t index_from_code(char* code){
        for (uint8_t i = 0; i < count; i++){
            if (!strcmp(code, code[i])){
                return i;
            }
        }
        // Make sure to account for signed error value 
        return index_error;
    };
    char* code_from_index(uint8_t index){
        if (index <= this->count){
            return this->Code[index];
        }
        // Make sure to account for empty string as error value
        return ""; 
    };

  private:
    // Access different data types by index
     enum {
        MIN,
        MAX
    }
    namespace Range {
        bool in(uint8_t index, uint8_t range[2]) {
            return ((index >= range[MIN]) && (index <= range[MAX]));
        }
        uint8_t offset(uint8_t index, uint8_t range[2]){
            return index - range[MIN];
        }
        uint8_t count(uint8_t range[2]) {
            return (range[MAX] - range[min] + 1);
        }
        static constexpr uint8_t total[2] = [0,2];
        static constexpr uint8_t float_values[2] = [0,2];
    };

    // Ordered indicies
    enum Index : uint8_t {
        INTERNAL_TEMP,
        BATTERY_VOLTAGE,
        BATTERY_PERCENTAGE
    }

    // Struct for storing output variables
    struct Values {
        float data_float[NumberOf::float_values];
    };

    // Designate this as the value returned from an invalid index conversion 
    static constexpr uint8_t index_error = 255; 

    // Define not_measured sentinal values for each variable
    // Because they are sensors, there should be some value outside realistic range to use
    static constexpr Values not_measured = {
        // Floats
        { 
            -255.0f,
            -255.0f,
            -255.0f
        }
    };

    // Default to not measured now but open to flexibility if needed
    static constexpr Values default_values = not_measured; 

    // Create instance to hold current values, set to default
    Values current = default_values;


    // String code for each variable
    static constexpr const char* Code[] = {
        "tmp",
        "vlt",
        "pct"
    };

};


#endif