// For use with IRremote 4.4.1

// Library must be included in seperate file

#ifndef IRSENSOR_h
#define IRSENSOR_h

class irSensor {
  public: 
    irSensor(uint8_t pin) : pin(pin) {}   // Save the pin for future reference
    void begin(){
      IrReceiver.begin(pin);    // No hardware initialization, just wont get any data if its not connected right
    }
    // Return if there is new data from the IR sensor
    bool decode(){
      return IrReceiver.decode(); 
    }
    // Read the data from the IR sensor
    void read(){
      uint16_t prevcommand = this->command; 
      this->command = IrReceiver.decodedIRData.command;
      this->command_updated = (command == prevcommand) ? 0 : 1; 
      this->command_timestamp = command_updated ? millis() : this->command_timestamp;
      uint16_t prevaddress = this->address; 
      this->address = IrReceiver.decodedIRData.address;
      this->address_updated = (address == prevaddress) ? 0 : 1; 
      this->address_timestamp = address_updated ? millis() : this->address_timestamp;
      IRRawDataType prevdata = this->data; 
      this->data = IrReceiver.decodedIRData.decodedRawData;
      this->data_updated = (data == prevdata) ? 0 : 1; 
      this->data_timestamp = data_updated ? millis() : this->data_timestamp;
      IrReceiver.resume();
    }
    bool update(){
      if (this->decode()){
        this->read();
        return true;    // Successfully read the data
      }
      return false;     // No data to read
    }
    // Getter functions
    uint8_t get_pin(){
      return this->pin; 
    }
    bool is_new_command(){
      return this->command_updated; 
    }
    uint16_t get_command(){
      this->command_updated = false; 
      return this->command; 
    }
    unsigned long get_command_timestamp(){
      return this->command_timestamp; 
    }
    bool is_new_address(){
      return this->address_updated; 
    }
    uint16_t get_address(){
      this->address_updated = false; 
      return this->address; 
    }
    unsigned long get_address_timestamp(){
      return this->address_timestamp;
    }
    bool is_new_data(){
      return this->data_updated; 
    }
    IRRawDataType get_data(){
      this->data_updated = false; 
      return this->data; 
    }
    unsigned long get_data_timestamp(){
      return this->data_timestamp; 
    }
  private: 
    uint8_t pin; 
    uint16_t command = 0; 
    bool command_updated = 0; 
    unsigned long command_timestamp = 0;
    uint16_t address = 0; 
    bool address_updated = 0; 
    unsigned long address_timestamp = 0;
    IRRawDataType data = 0;    // Defined in IRremote library based on archetecture
    bool data_updated = 0; 
    unsigned long data_timestamp = 0;
};

#endif
