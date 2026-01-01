#ifndef PIN_h
#define PIN_h

#define NULL_PIN 255

#include "numberOfSensors.h"
#include <Arduino.h>            // Need this for analog pin defs

// PWM Pins: 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46
// Intrurupt Pins: 2, 3, 18, 19, 20, 21

namespace Pin {
  namespace Ultrasonic {
    static constexpr uint8_t trig[NumberOfSensors::ultrasonic] = {
      30, 32, 34, 36, 38
    };  
    static constexpr uint8_t echo[NumberOfSensors::ultrasonic] = {
      31, 33, 35, 37, 39
    }; 
  };  
  namespace Sd {
    static constexpr uint8_t MISO = 50;
    static constexpr uint8_t MOSI = 51;
    static constexpr uint8_t SCK = 52;
    static constexpr uint8_t CS = 53;
  };
  namespace Display {
    static constexpr uint8_t RS = 43;
    static constexpr uint8_t EN = 44;
    static constexpr uint8_t D4 = 45;
    static constexpr uint8_t D5 = 46;
    static constexpr uint8_t D6 = 47;
    static constexpr uint8_t D7 = 48;

  }
  static constexpr uint8_t tof[NumberOfSensors::tof] = {
    22, 23, 24, 25, 26
  }; 
  static constexpr uint8_t ir[NumberOfSenors::ir] = {
    4
  };
  namespace MotorEncoder {
    static constexpr uint8_t a[NumberOfSensors::encoder] = {
      2
    };
    static constexpr uint8_t a_inverse[NumberOfSensors::encoder] = {
      NULL_PIN
    };
    static constexpr uint8_t b[NumberOfSensors::encoder] = {
      3
    };
    static constexpr uint8_t b_inverse[NumberOfSensors::encoder] = {
      NULL_PIN
    };
    static constexpr uint8_t i[NumberOfSensors::encoder] = {
      NULL_PIN
    };
    static constexpr uint8_t i_inverse[NumberOfSensors::encoder] = {
      NULL_PIN
    };
  }
  static constexpr uint8_t internal_temp = A0;
  static constexpr uint8_t external_temp = A1;
  static constexpr uint8_t TX_1 = 18;
  static constexpr uint8_t RX_1 = 19;
  static constexpr uint8_t SDA = 20;
  static constexpr uint8_t SCL = 21;
};

#endif