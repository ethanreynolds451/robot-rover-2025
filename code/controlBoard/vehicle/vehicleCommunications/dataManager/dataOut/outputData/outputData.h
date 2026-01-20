#ifndef OUTPUTDATA_h
#define OUTPUTDATA_h

// Need to figure out better approach for this mess

namespace OutputData {
    // Struct to store output data values
    struct Values {
        float internal_temp;
        float battery_voltage;
        float battery_percentage;
    };

    // Sentinel values, make sure to update if new value with this in range is added
    static constexpr float float_not_measured = -255.0f;
    static constexpr float float_invalid = -254.0f;

    // Instantiate data struct with default values
    static constexpr Values default_values = {
        float_not_measured, 
        float_not_measured,
        float_not_measured
    };
    
    // Instantiate data struct to hold current values
    Values current = default_values;

    void set(){

    }

    // Function to reset all data values to defaults
    void reset() {
       current = default_values;
    }
}

#endif