
// Include the local coppies of any required libraries
#include "TinyGPS/TinyGPS++.h"
#include "TinyGPS/TinyGPS++.cpp"
#include <SoftwareSerial.h>

#include "gpsUnit.h"

gpsUnit testGPS(0, 1, 9600);   // Use hardware serial 1 for GPS

void setup(){
    Serial.begin(115200);
}

void loop(){
    if (testGPS.update()){
        Serial.print("Latitude: ");
        Serial.print(testGPS.get_latitude(), 6);
        Serial.print(" | Longitude: ");
        Serial.print(testGPS.get_longitude(), 6);
        Serial.print(" | Altitude: ");
        Serial.print(testGPS.get_altitude());
        Serial.print(" m | Speed: ");
        Serial.print(testGPS.get_speed());
        Serial.print(" km/h | Course: ");
        Serial.print(testGPS.get_course());
        Serial.print(" deg | Fix: ");
        Serial.println(testGPS.get_fix());
    }
}


/*
    // Calculate timestamps
    arduino_timestamp = millis();
    offset_timestamp = arduino_timestamp - sensor_timestamp;

    // Declare and the string incrementer to 0
    int pos = 0; 

    // Construct the output string
    // Encode the data as hexadecimal to save space
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "ir[");
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "t:%x", offset_timestamp);
    if (isCommand){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",c:%x", command);
    }
    if (isAddress){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", address);
    }
    if (isData){
      pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", data);
    }
    pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");

    // Send the packet over serial with newline character to indicate end of packet
    // This does not go through the serial manager's packetization system since this is a simple test
    // It is guarenteed to always be less than 64 bytes
    Serial.println(outputString);

    // Clear the IR data to ensure no old data is transmitted in the next loop
    // Just a safety measure since they should all be cleared by the getter functions

*/
