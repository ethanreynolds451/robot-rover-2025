#ifndef ADDRESS_h
#define ADDRESS_h

namespace Address {
  static constexpr uint8_t lof[number_of_lof] = {0x29, 0x30, 0x31, 0x32}; // First default, rest must be programmed ON EACH POWER CYCLE IS VOLATILE
  static constexpr uint8_t qmc[number_of_qmc] = {0x0D};           // Default (verified from datasheeet)
  static constexpr uint8_t mpu[number_of_mpu] = {0x68, 0x69};     // First default, second with adjustor pulled up to 5v
  static constexpr uint8_t pcf = 0x20;                            // Default according to ChatGPT, check specific model
};

#endif