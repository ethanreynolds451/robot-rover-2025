#include <Adafruit_Sensor.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GenericDevice.h>

#include <Wire.h>
#include "timer.h"

#include "mpuSensor.h"

using mpuSensor = mpu_sensor::mpu_object;

mpuSensor testMPU(0x68, 1000);

// Data string
char outputString[128];
// THIS WILL BLOCK THE ARDUINO, should incororate package management

unsigned long hex_float_2(float value){
    // Convert the float to a 16-bit integer with 2 decimal places of precision
    return (unsigned long)(value * 100);
}

void setup(){
    Serial.begin(115200); 
    testMPU.begin();
}

void loop(){  
    if (testMPU.update()){

        int pos = 0; 
        memset(outputString, 0, sizeof(outputString));

        // Get the timestamp and offset
        unsigned long arduino_timestamp = millis();
        unsigned long sensor_timestamp = testMPU.get_timestamp();
        unsigned long offset_timestamp = arduino_timestamp - sensor_timestamp;

        // Add timestamps to the output string
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "{t[%x]", arduino_timestamp);
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "mpu[t:%x", offset_timestamp);

        if (testMPU.is_new_accel()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",a:%x", hex_float_2(testMPU.get_accel().x));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", hex_float_2(testMPU.get_accel().y));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", hex_float_2(testMPU.get_accel().z));
        }

        if (testMPU.is_new_gyro()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",g:%x", hex_float_2(testMPU.get_gyro().x));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", hex_float_2(testMPU.get_gyro().y));
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ";%x", hex_float_2(testMPU.get_gyro().z));
        }

        if (testMPU.is_new_temp()){
            pos += snprintf(outputString + pos, sizeof(outputString) - pos, ",t:%x", hex_float_2(testMPU.get_temp()));
        }

        // Close the output string and send it over serial
        pos += snprintf(outputString + pos, sizeof(outputString) - pos, "]}");
        Serial.println(outputString);

        // Clear the data
        testMPU.clear(); 
    }
}
