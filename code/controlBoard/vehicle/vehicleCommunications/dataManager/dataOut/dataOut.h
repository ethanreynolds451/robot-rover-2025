#ifndef DATAOUT_h
#define DATAOUT_h

#include "outputData/outputData.h"
#include "outputDelimiter/outputDelimiter.h"

class dataOut {
  public:
    dataOut(size_t string_limit) : string_limit(string_limit) {}

    // Get the formated string with all data values
    char* get(){
      // Return format {tmp[0]vlt[0]pct[0]}
      return get_output_string();
    }

    // Setter functions
    float get_internal_temp(){
      return *(float*)data.get(outputData::Index::INTERNAL_TEMP);
    }
    float get_battery_voltage(){
      return *(float*)data.get(outputData::Index::BATTERY_VOLTAGE);
    }
    float get_battery_percentage(){
      return *(float*)data.get(outputData::Index::BATTERY_PERCENTAGE);
    }

    // Getter functions
    void set_internal_temp(float value){
      data.set(outputData::Index::INTERNAL_TEMP, value);
    }
    void set_battery_voltage(float value){
      data.set(outputData::Index::BATTERY_VOLTAGE, value);
    }
    void set_battery_percentage(float value){
      data.set(outputData::Index::BATTERY_PERCENTAGE, value);
    }

    void reset(){
      // Sets all output data to default values, pass-through function
      data.reset();
    }

  private:
    size_t string_limit; 

    // Create instance of output data 
    outputData data; 

    char* get_output_string(){
      // {tmp[0]vlt[0]pct[0]}
      char buffer[string_limit];
      snprintf(
          buffer,
          sizeof(buffer),
          "%s%s%s%0.2f%s%s%s%0.2f%s%s%s%0.2f%s%s\n",
          
          OutputDelimiter::start,

          *(float*)data.code_from_index(outputData::Index::INTERNAL_TEMP),
          OutputDelimiter::v_start,
          data.get(outputData::Index::INTERNAL_TEMP),
          OutputDelimiter::v_end,
          
          *(float*)data.code_from_index(outputData::Index::BATTERY_VOLTAGE),
          OutputDelimiter::v_start,
          data.get(outputData::Index::BATTERY_VOLTAGE),
          OutputDelimiter::v_end,

          *(float*)data.code_from_index(outputData::Index::BATTERY_PERCENTAGE),
          OutputDelimiter::v_start,
          data.get(outputData::Index::BATTERY_PERCENTAGE),
          OutputDelimiter::v_end,

          OutputDelimiter::end
      );
      return buffer;
    };
};

#endif