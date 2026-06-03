#include "tempSensor.h"

#define PIN A0
#define SLOPE 0.1
#define INTERCEPT 0.0

using tempSensor = temp_sensor::temp_object;

tempSensor testTemp(PIN, SLOPE, INTERCEPT);

void setup(){
    Serial.begin(115200); 
    testTemp.begin(); 
}

void loop(){
    if (testTemp.update()){
        memset(outputString, 0, sizeof(outputString));
        int pos = 0;
        unsigned long arduino_timestamp = millis();
        unsigned long offset = arduino_timestamp - testTemp.get_temp_timestamp();
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "tmp[n:0,t:%x", offset);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",tp:%x", testTemp.get_temp());
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);
        testTemp.clear();
    }
}