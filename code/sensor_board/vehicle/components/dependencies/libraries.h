#ifndef LIBRARIES_h
#define LIBRARIES_h

// These libraries are included by default in Arduino instalation
#include <Arduino.h>
#include <SoftwareSerial.h>                                     //Virtual serial port
#include <SPI.h>                                                //Serial peripheral interface
#include <Wire.h>                                               //Communication

// Need to install Adafruit IO Bus and Adafruit Sensor from Arduino library manager
// they are directly referenced by other libraries and can not be included directly from folder without difficulty

// These libraries are downloaded from the internet and placed in a "libraries" folder in the same directory as the program
#include "HCSR04_ultrasonic_sensor/src/HCSR04.h"      //Ultrasonic interface
#include "Adafruit_MPU6050/Adafruit_MPU6050.h"        //Gyroscope interface
#include "TinyGPSPlus-master/src/TinyGPSPlus.h"           //GPS interface
#include "TinyGPSPlus-master/src/TinyGPS++.h"           //GPS interface
#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.h"  //Compass interface
#include "IRremote-4.4.1/src/IRremote.h"                // IR remote digital
#include "VL53L0X-1.3.1/VL53L0X.h"                      //LOF sensors
#include "PCF8575-master/PCF8575.h"                     //PCF port expander 16 bit
#include "Encoder/Encoder.h"                           //Rotary encoder 

// Need to include cpps for some reason because it will not work otherwise
#include "HCSR04_ultrasonic_sensor/src/HCSR04.cpp"      //Ultrasonic interface
#include "Adafruit_MPU6050/Adafruit_MPU6050.cpp"  //Gyroscope interface
#include "TinyGPSPlus-master/src/TinyGPS++.cpp"           //GPS interface
#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.cpp"  //Compass interface
#include "VL53L0X-1.3.1/VL53L0X.cpp"                      //LOF sensors
#include "PCF8575-master/PCF8575.cpp"                     //PCF port expander 16 bit
#include "Encoder/Encoder.cpp"                           //Rotary encoder 

#endif
