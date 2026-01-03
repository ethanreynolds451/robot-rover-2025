#ifndef DATA_h
#define DATA_h

namespace Data {
    static constexpr float not_measured = -255f;
    float internal_temp = not_measured; 
    float battery_voltage = not_measured;
    float battery_percentage = not_measured; 
}

#endif