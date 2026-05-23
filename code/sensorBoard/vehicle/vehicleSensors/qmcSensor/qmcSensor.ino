#include "qmcSensor.h"

byte ADDRESS = 0x0D;

qmcSensor testQMC(ADDRESS); 

// Buffer to hold the output string
char outputString[64];

void setup(){
    Serial.begin(115200); 
    testQMC.begin(); 
    delay(100);    // Give it a moment to initialize
}

void loop(){
    if (testQMC.update()){
        // Clear any previous data from the buffer
        memset(outputString, 0, sizeof(outputString));

        // Create variables and trackers for the data
        unsigned long arduino_timestamp = 0;
        unsigned long sensor_timestamp = 0;
        float direction = 0.0;
        float mag_x = 0.0;
        float mag_y = 0.0;
        float mag_z = 0.0;
        bool isDirection = false;
        bool isMag = false;

        // Retrieve the data
        if (testQMC.is_new_direction()){
            direction = testQMC.get_direction();
            sensor_timestamp = testQMC.get_direction_timestamp();
            isDirection = true;
        }
        if (testQMC.is_new_mag()){
            testQMC.get_mag(mag_x, mag_y, mag_z);
            sensor_timestamp = testQMC.get_mag_timestamp();
            isMag = true;
        }

        // Generate the Arduino timestamp and calculate the offset
        arduino_timestamp = millis();
        unsigned long offset_timestamp = arduino_timestamp - sensor_timestamp;

        // Build the output string
        int pos = 0;
        
        // Construct the output string
        // Encode the data as hexadecimal to save space
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "qmc[");
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "n:0,");        // There is only one
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "t:%x", offset_timestamp);
        if (isDirection){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",d:%x", direction);
        }
        if (isMag){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",m:%x", mag_x);
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", mag_y);
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", mag_z);
        }
        // Send the packet over serial with newline character to indicate end of packet
        Serial.println(outputString);

        // Manually clear all old data 
        testQMC.clear();
    }
}
