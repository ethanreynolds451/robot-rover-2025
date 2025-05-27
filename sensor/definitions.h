#ifndef DEFINITIONS_h
#define DEFINITIONS_h

static const uint16_t loop_delay = 100;

class Pin {
public:
  // Ultrasonic Sensors
  static constexpr uint8_t HC-SR04_1_t = 6;
  static constexpr uint8_t HC-SR04_1_e = 7;
  static constexpr uint8_t HC-SR04_2_t = 8;
  static constexpr uint8_t HC-SR04_2_e = 9;
  static constexpr uint8_t HC-SR04_3_t = A0;
  static constexpr uint8_t HC-SR04_3_e = A1;
  static constexpr uint8_t HC-SR04_4_t = A2;
  static constexpr uint8_t HC-SR04_4_e = A3;
  // Signal
  static constexpr uint8_t TX = 2;
  static constexpr uint8_t RX = 3;
  static constexpr uint8_t SDA = A4;
  static constexpr uint8_t SCL = A5;
  // SD Card
  static constexpr uint8_t MISO = 
  static constexpr uint8_t MOSI =
  static constexpr uint8_t SCK =
  static constexpr uint8_t CS =
};

