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
      uint16_t prev_command = this->_command; 
      this->_command = IrReceiver.decodedIRData.command;
      this->command_updated = (_command == prev_command) ? 0 : 1; 
      uint16_t prev_address = this->_address; 
      this->_address = IrReceiver.decodedIRData.address;
      this->address_updated = (_address == prev_address) ? 0 : 1; 
      IRRawDataType prev_data = this->_data; 
      this->_data = IrReceiver.decodedIRData.decodedRawData;
      this->data_updated = (_data == prev_data) ? 0 : 1; 
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
    bool new_command(){
      return this->command_updated; 
    }
    uint16_t command(){
      return this->_command; 
    }
    bool new_address(){
      return this->address_updated; 
    }
    uint16_t address(){
      return this->_address; 
    }
    bool new_data(){
      return this->data_updated; 
    }
    IRRawDataType data(){
      return this->_data; 
    }
    uint8_t getPin(){
      return this->pin; 
    }
  private: 
    uint8_t pin; 
    uint16_t _command = 0; 
    bool command_updated = 0; 
    uint16_t _address = 0; 
    bool address_updated = 0; 
    IRRawDataType _data = 0;    // Defined in IRremote library based on archetecture
    bool data_updated = 0; 
};

#endif
