#ifndef CODES_h
#define CODES_h
  
  namespace sensor_code {
    const char* ultrasonic = "hc";
    const char* lof = "lof";
    const char* steering ="str";
    const char* mpu = "mpu";
    const char*  qmc = "qmc";
    const char* gps = "gps";
    const char* remote = "ir";
  };

  namespace error {                    // Storage for sensor errors
    namespace {
      static const uint8_t number_of_errors = 6;
      struct error_packet {
        uint8_t index;
        char code[8];   // 8 byte max for codes
      };
    };
    uint8_t ultrasonic[number_of_ultrasonic];
    uint8_t lof[number_of_lof];
    uint8_t mpu[number_of_mpu];
    uint8_t qmc[number_of_qmc];
    uint8_t gps;
    const error_packet error_codes[number_of_errors] = {
        {0, "none"},    // no error
        {1, "addr"},    // address not found
        {2, "init"},    // failed to initialize
        {3, "read"},    // failed to read data
        {4, "nocom"},   // unable to communicate
        {5, "other"}    // any other failure
    };
  };

#endif