#ifndef DATASENDER_h
#ifndef DATASENDER_h

#include "outputCodes/outputCodes.h"
#include "outputData/outputData.h"

class dataOut {
  public:
    dataOut(size_t string_limit) : string_limit(string_limit) {}

    // Get the formated string with all data values
    char* get(){
      // Return format {tmp[0]vlt[0]pct[0]}

    }

    // Overloaded function to get single value by index
    float get(uint8_t index){
      if (index >= OutputCodes::Data::number_of){
        return getData<float>(index);
      } 
      return OutputData::float_invalid;
    }

    // Overloaded function to get single value by code
    float get(char *code){ 
      int8_t index = OutputCodes::Data::index_from_code(code);
      if (index >= 0){
        return getData<float>(OutputCodes::Data::index_from_code(code)); 
      }
      return OutputData::float_invalid;
    }


    // Set all output data from list of provided values
    // Need to modify whenever new values are added
    void set(){

    }

    // Overloaded function to set single value by index
    void set(){

    }

    void reset(){
      // Sets all output data to default values, pass-through function
      OutputData::reset();
    }

    private:
      size_t string_limit; 
      // Template function for different return types
      // Just floats for now but in case somehting else is added
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