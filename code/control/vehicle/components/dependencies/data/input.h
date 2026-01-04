#ifndef INPUT_h
#define INPUT_h

namespace Data {
    static constexpr float not_measured = -255.0f;
    float internal_temp = not_measured; 
    float battery_voltage = not_measured;
    float battery_percentage = not_measured; 
    void reset() {
        internal_temp = not_measured;
        battery_voltage = not_measured;
        battery_percentage = not_measured;
    }
}

#endif