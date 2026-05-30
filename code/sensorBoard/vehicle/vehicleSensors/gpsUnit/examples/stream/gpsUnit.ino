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
    testGPS.initialize();
    delay(1500); // Allow data to start arriving before calling begin, which checks connection
    testGPS.begin();
}

// Float conversion functions
unsigned long hex_float_6(float value){
    // Convert the float to a 32-bit integer with 6 decimal places of precision
    return (unsigned long)(abs(value) * 1000000);
}
unsigned long hex_float_2(float value){
    // Convert the float to a 32-bit integer with 2 decimal places of precision
    return (unsigned long)(abs(value) * 100);
}
uint8_t sign_bit (float value){
    return (value < 0) ? 1 : 0;
}

// encode coords as hex_float_6
// encode all other floats as hex_float_2
// encode all ints as hex

void loop(){

    testGPS.poll();

    if (testGPS.peek().is_new){

        // Calculate timestamps and offsets for the packet
        unsigned long arduino_timestamp = millis();
        unsigned long offset_timestamp = arduino_timestamp - testGPS.peek().timestamp;

        // Prepare the output string
        memset(outputString, 0, sizeof(outputString));
        int pos = 0;

     
        // Add the arduino timestamp and sensor header data to the string
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "gps[n:0");
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", offset_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",s:%x%x", static_cast<uint8_t>(testGPS.get_state()), static_cast<uint8_t>(testGPS.get_error()));

        // Add new sensor data
        if (testGPS.peek().position.coordinates.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",p:%x%x", sign_bit(testGPS.get_coordinates().latitude), hex_float_6(testGPS.get_coordinates().latitude));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x%x", sign_bit(testGPS.get_coordinates().longitude), hex_float_6(testGPS.get_coordinates().longitude));
        }
        if (testGPS.peek().position.altitude.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x%x", sign_bit(testGPS.get_altitude().value), hex_float_2(testGPS.get_altitude().value));
        }
        if (testGPS.peek().velocity.speed.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",v:%x", hex_float_2(testGPS.get_speed().value));
        }
        if (testGPS.peek().velocity.course.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",h:%x", hex_float_2(testGPS.get_course().value));
        }
        if (testGPS.peek().time.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",g:%x", testGPS.get_time().value);
        }
        if (testGPS.peek().fix.is_new){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",f:%x", testGPS.get_fix().value);
        }

        // Close the output string and send it over serial
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);

        // Clear the data
        testGPS.clear(); 
    }
}