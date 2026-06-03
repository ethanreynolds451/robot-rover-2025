#include "tempSensor.h"

#include "tempSensor_codes.h"

uint8_t PIN = A1;
uint8_t SLOPE = 0.1;
uint8_t INTERCEPT = 0.0;
unsigned long LOOP_DELAY = 1000;

using tempSensor = temp_sensor::temp_object;

tempSensor temp(A1, SLOPE, INTERCEPT);

char stateString[16];
char errorString[16];

void setup() {
    Serial.begin(115200);
    Serial.println("Serial communication started.");
    Serial.println("Initializing Temperature Sensor");
    temp.initialize();
    temp_sensor::get_state_str(temp.get_state(), stateString, sizeof(stateString));
    temp_sensor::get_error_str(temp.get_error(), errorString, sizeof(errorString));
    Serial.print("Initialization complete with state: " + String(stateString) + " and error: " + String(errorString) + "\n");
    Serial.println("Beginning Temperature Sensor");
    temp.begin();
    temp_sensor::get_state_str(temp.get_state(), stateString, sizeof(stateString));
    temp_sensor::get_error_str(temp.get_error(), errorString, sizeof(errorString));
    Serial.print("Begin complete with state: " + String(stateString) + " and error: " + String(errorString) + "\n");
    Serial.println("Entering main loop");
}

void loop() {
    temp_sensor::get_state_str(temp.get_state(), stateString, sizeof(stateString));
    temp_sensor::get_error_str(temp.get_error(), errorString, sizeof(errorString));
    Serial.print("Current state: " + String(stateString) + " and error: " + String(errorString) + "\n");

    Serial.println("Polling temperature sensor...");
    temp.poll();

    if (temp.peek().measurement.is_new) {
        Serial.println("New temperature data available:");
        if(temp.peek().measurement.is_new){
            Serial.print(" - Temperature: " + String(temp.get_measurement().value) + " °C\n");
        }

        temp.clear();
    }
    delay(LOOP_DELAY);
}