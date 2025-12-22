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
#include "libraries/IRremote-4.4.1/src/IRremote.h"                // IR remote digital


#endif
