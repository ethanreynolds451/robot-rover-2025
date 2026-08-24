// Debug script for GPS

#include <SoftwareSerial.h>
#include "gpsUnit.h"

#include "gpsUnit_codes.h"

unsigned long SERIAL_BAUDRATE = 115200;
unsigned long GPS_BAUDRATE = 9600;
unsigned long GPS_INIT_DELAY = 1500;
unsigned long loop_delay = 500;

using gpsUnit = gps_unit::gps_object;

gpsUnit testGPS(0, 1, GPS_BAUDRATE);   // Use hardware serial 1 for GPS

char stateString[16];

void setup(){
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("Serial communication started at baudrate: " + String(SERIAL_BAUDRATE));
    Serial.println("Initializing GPS unit...");
    testGPS.initialize();
    gps_unit::get_state_str(testGPS.get_state(), stateString, sizeof(stateString));
    Serial.println("GPS unit in state: " + String(stateString));
    Serial.println("Waiting" + String(GPS_INIT_DELAY) + " ms for GPS unit to start transmitting...");
    delay(GPS_INIT_DELAY); // Allow data to start arriving before calling begin, which checks connection
    Serial.println("Starting GPS unit...");
    testGPS.begin();
    gps_unit::get_state_str(testGPS.get_state(), stateString, sizeof(stateString));
    Serial.println("GPS unit in state: " + String(stateString));
}

void loop(){
    // Get the current state of the sensor
    gps_unit::get_state_str(testGPS.get_state(), stateString, sizeof(stateString));
    Serial.println("Current GPS sensor state: " + String(stateString));

    Serial.println("Polling GPS sensor for new data...");
    testGPS.poll();

    if (testGPS.peek().is_new){
        Serial.println("New GPS data received:");
        // Print new sensor data
        if (testGPS.peek().position.coordinates.is_new){
            Serial.println(" - Coordinates: (" + String(testGPS.get_coordinates().latitude, 6) + ", " + String(testGPS.get_coordinates().longitude, 6) + ") (timestamp: " + String(testGPS.peek().position.coordinates.timestamp) + ")");
        }
        if (testGPS.peek().position.altitude.is_new){
            Serial.println(" - Altitude: " + String(testGPS.get_altitude().value, 6) + " (timestamp: " + String(testGPS.peek().position.altitude.timestamp) + ")");
        }
        if (testGPS.peek().velocity.speed.is_new){
            Serial.println(" - Speed: " + String(testGPS.get_speed().value, 6) + " (timestamp: " + String(testGPS.peek().velocity.speed.timestamp) + ")");
        }
        if (testGPS.peek().velocity.course.is_new){
            Serial.println(" - Course: " + String(testGPS.get_course().value, 6) + " (timestamp: " + String(testGPS.peek().velocity.course.timestamp) + ")");
        }
        if (testGPS.peek().time.is_new){
            Serial.println(" - Time: " + String(testGPS.get_time().value, 6) + " (timestamp: " + String(testGPS.peek().time.timestamp) + ")");
        }
        if (testGPS.peek().fix.is_new){
            Serial.println(" - Fix quality: " + String(testGPS.get_fix().value) + " (timestamp: " + String(testGPS.peek().fix.timestamp) + ")");
        }

        // Clear the data
        testGPS.clear(); 
    }
    delay(loop_delay);
}