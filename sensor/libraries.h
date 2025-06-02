#ifndef LIBRARIES_h
#define LIBRARIES_h

#include <Arduino.h>
#include <SoftwareSerial.h>                                     //Virtual serial port
#include <SPI.h>                                                //Serial peripheral interface
#include <Wire.h>                                               //Communication
Adafruit_BusIO_Register.h "libraries/Adafruit_BusIO-1.17.0/Adafruit_BusIO_Register.h"   // Dependency for mpu library
#include "libraries/HCSR04_ultrasonic_sensor/src/HCSR04.h"      //Ultrasonic interface
#include "libraries/Adafruit_MPU6050/Adafruit_MPU6050.h"        //Gyroscope interface
#include "libraries/TinyGPSPlus-master/src/TinyGPSPlus.h"           //GPS interface
#include "libraries/TinyGPSPlus-master/src/TinyGPS++.h"           //GPS interface
#include "libraries/QMC5883LCompass-1.2.3/src/QMC5883LCompass.h"  //Compass interface
#include "libraries/IRremote-4.4.1/src/IRremote.h"
	
#include "libraries/HCSR04_ultrasonic_sensor/src/HCSR04.cpp"      //Ultrasonic interface
#include "libraries/Adafruit_MPU6050/Adafruit_MPU6050.cpp"  //Gyroscope interface
#include "libraries/TinyGPSPlus-master/src/TinyGPS++.cpp"           //GPS interface
#include "libraries/QMC5883LCompass-1.2.3/src/QMC5883LCompass.cpp"  //Compass interface
#include "libraries/IRremote-4.4.1/src/IRremote.cpp"

#endif
