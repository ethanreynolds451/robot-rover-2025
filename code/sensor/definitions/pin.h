#ifndef PIN_h
#define PIN_h

#include "numberOfSensors.h"

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
    static constexpr uint8_t RS = 
    static constexpr uint8_t EN =
    static constexpr uint8_t D4 =
    static constexpr uint8_t D5 =
    static constexpr uint8_t D6 =
    static constexpr uint8_t D7 =

  }
  static constexpr uint8_t x_shut[NumberOfSensors::tof] = {
    // Add to schematic
  }; 
  static constexpr uint8_t ir[NumberOfSenors::ir] = {
    // PIN
  };
  static constexpr uint8_t TX_1 = 18;
  static constexpr uint8_t RX_1 = 19;
  static constexpr uint8_t SDA = 20;
  static constexpr uint8_t SCL = 21;
};

#endif