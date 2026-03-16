// For use with IRremote 4.4.1

// Library must be included in seperate file

#ifndef IRSENSOR_h
#define IRSENSOR_h

enum {
  IR_LED_OFF,
  IR_LED_ON
};

class irSensor {
  public: 
    irSensor(uint8_t pin, bool led = 0) : pin(pin), led_active(led) {}   // Save the pin for future reference
    void begin(){
      if(led_active){
        IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);    // No hardware initialization, just wont get any data if its not connected right
      } else {
        IrReceiver.begin(pin); 
      }
    }
    // Return if there is new data from the IR sensor
    bool decode(){
        if(IrReceiver.decode()){
            // Filtrar señales que no sean de protocolos conocidos
            if(IrReceiver.decodedIRData.protocol == UNKNOWN){
                IrReceiver.resume();  // Ignorar la señal y preparar para la siguiente
                return false;
            }
            return true;  // Señal válida
        }
        return false;  // No hay datos
    }
    // Read the data from the IR sensor
    // Validity checks are placeholder, can perform more complex based on later needs; zero is not valid for controller being used
    void read(){
      // Read incoming command
      uint8_t new_command = IrReceiver.decodedIRData.command;
      if(new_command != 0){
        this->command_timestamp = millis();
        this->command = new_command; 
        this->command_updated = 1; 
      }
      // Read incoming address
      uint16_t new_address = IrReceiver.decodedIRData.address;
      if (new_address != 0){
        this->address_timestamp = millis();
        this->address = new_address; 
        this->address_updated = 1;
      }
      // Read incoming data 
      IRRawDataType new_data = IrReceiver.decodedIRData.decodedRawData;
      if(new_data != 0){      
        this->data_timestamp = millis();
        this->data = new_data; 
        this->data_updated = 1;
      }
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
    bool led_active; 
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
