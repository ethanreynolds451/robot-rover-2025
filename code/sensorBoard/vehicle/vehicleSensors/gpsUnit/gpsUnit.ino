// Stream GPS data in ROS sensor string parser format

#include <SoftwareSerial.h>
#include "gpsUnit.h"

using gpsUnit = gps_unit::gps_object;

gpsUnit testGPS(0, 1, 9600);   // Use hardware serial 1 for GPS

// Declare the output string buffer
char outputString[128];
// THIS WILL BLOCK THE ARDUINO, fine for testing but must use packet manager for non-blocking implementation

void setup(){
    Serial.begin(115200);
    testGPS.begin(5000);   // Wait up to 5 seconds for GPS to initialize and start sending data
}

unsigned long hex_float_6(float value){
    // Convert the float to a 32-bit integer with 6 decimal places of precision
    return (unsigned long)(value * 1000000);
}

unsigned long hex_float_2(float value){
    // Convert the float to a 16-bit integer with 2 decimal places of precision
    return (unsigned long)(value * 100);
}

void loop(){
    if (testGPS.update()){
        // encode coords as hex_float_6
        // encode all other floats as hex_float_2
        // encode all ints as hex
        // Calculate timestamps

        // Prepare the output string
        int pos = 0; 
        memset(outputString, 0, sizeof(outputString));

        // Get the timestamp and offset
        unsigned long arduino_timestamp = millis();
        unsigned long sensor_timestamp = testGPS.get_timestamp();
        unsigned long offset_timestamp = arduino_timestamp - sensor_timestamp;

        // Add timestamps to the output string
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "gps[t:%x", offset_timestamp);

        if (testGPS.is_new_coordinates()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",p:%x", hex_float_6(testGPS.get_coordinates().latitude));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", hex_float_6(testGPS.get_coordinates().longitude));
        }
        if (testGPS.is_new_altitude()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", hex_float_2(testGPS.get_altitude()));
        }
        if (testGPS.is_new_speed()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",v:%x", hex_float_2(testGPS.get_speed()));
        }
        if (testGPS.is_new_course()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",h:%x", hex_float_2(testGPS.get_course()));
        }
        if (testGPS.is_new_time()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",gt:%x", testGPS.get_time());
        }
        if (testGPS.is_new_fix()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x", testGPS.get_fix());
        }

        // Close the output string and send it over serial
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);

        // Clear the data
        testGPS.clear(); 
    }
}