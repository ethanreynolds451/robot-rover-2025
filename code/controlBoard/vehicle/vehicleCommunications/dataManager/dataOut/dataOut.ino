#include "dataOut.h"

dataOut interface(64);

void setup(){
    Serial.begin(9600);
    // Testing functionality
    interface.set_internal_temp(23.45f);
    interface.set_battery_voltage(12.34f);
    interface.set_battery_percentage(56.78f);
}

void loop(){
    delay(1000);
    char* output = interface.get();
    Serial.println(output);
}
