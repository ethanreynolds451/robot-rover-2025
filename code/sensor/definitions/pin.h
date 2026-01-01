#ifndef PIN_h
#define PIN_h

namespace pin {
  static constexpr uint8_t HCSR04[number_of_ultrasonic+1] = {
    uint8_t(5), 6, 7, 8, 9,
    uint8_t(A0), uint8_t(A1)
  };   // 0 is trig pin
  static constexpr uint8_t x_shut[number_of_lof] = {0, 1, 2, 3}; // These are PCF pins - mod for test
  static constexpr uint8_t steer_position = A7;
  static constexpr uint8_t TX = 2;
  static constexpr uint8_t RX = 3;
  static constexpr uint8_t IR = 4;
  static constexpr uint8_t SDA = A4;
  static constexpr uint8_t SCL = A5;
  static constexpr uint8_t MISO = 12;
  static constexpr uint8_t MOSI = 11;
  static constexpr uint8_t SCK = 13;
  static constexpr uint8_t CS = 10;
};

#endif