#ifndef LIBRARIES_h
#define LIBRARIES_h

#include <Arduino.h>
#include <SoftwareSerial.h>                                     //Virtual serial port
#include <SPI.h>                                                //Serial peripheral interface
#include <Wire.h>                                               //Communication

// Need to install Adafruit IO Bus and Adafruit Sensor

#include "libraries/HCSR04_ultrasonic_sensor/src/HCSR04.h"      //Ultrasonic interface
#include "libraries/Adafruit_MPU6050/Adafruit_MPU6050.h"        //Gyroscope interface
#include "libraries/TinyGPSPlus-master/src/TinyGPSPlus.h"           //GPS interface
#include "libraries/TinyGPSPlus-master/src/TinyGPS++.h"           //GPS interface
#include "libraries/QMC5883LCompass-1.2.3/src/QMC5883LCompass.h"  //Compass interface
#include "libraries/IRremote-4.4.1/src/IRremote.h"
#include "libraries/VL53L0X-1.3.1/VL53L0X.h"
  
#include "libraries/HCSR04_ultrasonic_sensor/src/HCSR04.cpp"      //Ultrasonic interface
#include "libraries/Adafruit_MPU6050/Adafruit_MPU6050.cpp"  //Gyroscope interface
#include "libraries/TinyGPSPlus-master/src/TinyGPS++.cpp"           //GPS interface
#include "libraries/QMC5883LCompass-1.2.3/src/QMC5883LCompass.cpp"  //Compass interface
#include "libraries/VL53L0X-1.3.1/VL53L0X.cpp"

#endif
