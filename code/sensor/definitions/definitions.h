#ifndef DEFINITIONS_h
#define DEFINITIONS_h


#include "address.h"
#include "pin.h"
#include "global.h"


// Create pcf object for port expander
PCF8575 PCF(Address::pcf);

bool pcf_active = false;

bool start_pcf(){
    bool addr_found = false;
    bool initiated = false;
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
      if (!addr_found) {
        if (!Address::detect(Address::pcf)) {       
          
          delay(50); 
        } else {
          addr_found = true;
        }                                          
      } else if (!initiated) {
        if (!PCF.begin()) {
          delay(50); 
        } else {
          initiated = true;
        }
      } else {
        pcf_active = true; 
      }
    }
}










// Composite class to access all sensors, includes all relevant sensor objects

Sensor sensor;

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

Data data;

#endif
