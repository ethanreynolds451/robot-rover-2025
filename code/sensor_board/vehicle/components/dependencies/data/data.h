#ifndef DATA_h
#define DATA_h
  
// Merge this into data class with get_string function

  namespace value {                      // Storage for sensor values
    namespace {   // "private" members
      struct vector3_values {
        int16_t x;
        int16_t y;
        int16_t z;
      };
      struct mpu_values {
        vector3_values accel;
        vector3_values gyro;
        float temp;
      };
      struct gps_values {
        double lat;
        double lng;
        double alt;
        double spd;   // km per hour
        double deg;   // bearing, compare with magnetometer
        bool fix;   // Valid gps fix
      };
      struct is_new {
        bool ultrasonic[number_of_ultrasonic];
        bool lof[number_of_lof];
        bool steering;
        bool mpu[number_of_mpu];
        bool qmc[number_of_qmc];
        bool gps;
        bool remote;
      };
     };
    uint16_t ultrasonic[number_of_ultrasonic];
    uint16_t lof[number_of_lof];
    uint16_t steer_position;
    unsigned long ir;
    uint16_t qmc_bearing[number_of_qmc];
    vector3_values qmc[number_of_qmc];
    mpu_values mpu[number_of_mpu];
    gps_values gps;
    is_new updated;
  };

class Data {
  private:
    char buffer[string_limit];
    char output[string_limit];
    char data_start = '[';
    char data_end = ']'; 
    char* get_mpu(){
      memset(buffer, 0, string_limit);
      strcpy(buffer, sensor_code::ultrasonic); 
      strcpy(buffer, data_start); 
      for(int i = 0; i < number_of_mpu; i++){
        
        strcpy(buffer, tmp);
      }
      strcpy(buffer, data_end); 
      return buffer; 
    }
  public:
    
    char* get(){
      memset(output, 0, string_limit);

      //sensor.value::ultrasonic[index];
      //sensor.value::lof[index];
      // sensor.value::
      strcpy(output, "Hello World");
      return output;
    }
};

#endif