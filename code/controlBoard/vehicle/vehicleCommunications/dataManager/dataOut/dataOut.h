#ifndef DATASENDER_h
#ifndef DATASENDER_h

#include "outputCodes/outputCodes.h"
#include "outputData/outputData.h"

class dataOut {
  public:
    dataOut(size_t string_limit) : string_limit(string_limit) {}

    // Get the formated strong of all data values
    char* get(){

    }

    // Overloaded function to get single value by index
    float get(uint8_t index){
      return getData<float>(index);
    }

    float get(char *code){
      uint8_t index = 
      return getData<float>(index); 
    }



    // Set all output data from list of provided values
    void set(){

    }

    // Overloaded function to set single value by index
    void set(){

    }

    void reset(){
      // Sets all output data to default values
      OutputData::reset();
    }

    private:
      template <typename T>
      T getData(unit8_t index) {
          T data;
          data = OutputData::current[index];
          return data;
      }


    // {tmp[0]vlt[0]pct[0]}
    char buffer[STRING_LIMIT];
    namespace C = Code::Data;
    namespace D = Code::Delimiter;
    namespace V = InputData;
    snprintf(
        buffer,
        sizeof(buffer),
        "%s%s%s%0.2f%s%s%s%0.2f%s%s%s%0.2f%s%s\n",
        
        D::start,

        C::str[C::Index::internal_temp],
        D::v_start,
        V::current.internal_temp,
        D::v_end,
        
        C::str[C::Index::battery_voltage],
        D::v_start,
        V::current.battery_voltage,
        D::v_end,

        C::str[C::Index::battery_percentage],
        D::v_start,
        V::current.battery_percentage,
        D::v_end,

        D::end
    );

#endif