#ifndef INPUTDATA_h
#define INPUTDATA_h

namespace InputData {
    struct Values {
        float internal_temp;
        float battery_voltage;
        float battery_percentage;
    };

    static constexpr float not_measured = -255.0f;
    static constexpr Values default_values = {not_measured, not_measured, not_measured};
    Values current = default_values;

    void reset() {
       current = default_values;
    }
}

#endif