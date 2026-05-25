#ifndef IRSENSOR_h
#define IRSENSOR_h

#include "IRremote-4.4.1/src/IRremote.h"

#include "irSensor_t.h"

namespace ir_sensor {

class ir_object {
  public: 
    ir_object(uint8_t pin, bool led = 0) {
      this->config.pin = pin;
      this->config.led_active = led;
      this->state = STATE::UNINITIALIZED;
    }  

    // *** State Management *** //
    void begin(){
      if (this->state == STATE::FAULT) return;
      if (this->state != STATE::UNINITIALIZED) {
        stop();
      };
      if(led_active){
        IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);    // No hardware initialization, just wont get any data if its not connected right
      } else {
        IrReceiver.begin(pin); 
      }
      this->state = STATE::UNVERIFIED;                    // UNINITIALIZED -> UNVERIFIED
    }
    void stop() {
      IrReceiver.stop();
      if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
      if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
      if (this->state == STATE::UNVERIFIED) {
        this->state = STATE::UNINITIALIZED;                // UNVERIFIED -> UNINITIALIZED
        return
      };
      if (this->state == STATE::PAUSED) return;            // PAUSED -> PAUSED + return
      if (this->state == STATE::VERIFIED) {
        this->state = STATE::PAUSED;                      // VERIFIED -> PAUSED
      };                      
    }
    void start(){
      if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
      IrReceiver.start();
      if (this->state == STATE::UNINITIALIZED) {
        this->state = STATE::UNVERIFIED;                 // UNINITIALIZED -> UNVERIFIED
        return
      };    
      if (this->state == STATE::UNVERIFIED) return;      // UNVERIFIED -> UNVERIFIED + return
      if (this->state == STATE::PAUSED) {
        this->state = STATE::VERIFIED;                   // PAUSED -> VERIFIED
      };
    }
    void reset(){
      stop();
      this->state = STATE::UNINITIALIZED;
      this->data = DATA();
    }
    void update() {
        return; 
    }

    // *** Diagnostics *** //
    void set_pin(uint8_t new_pin){
      this->pin = new_pin; 
      // Restart the IR receiver with the new pin
      IrReceiver.stop();
      this->begin(); 
    }
    void set_led_active(bool new_led_active){
      this->led_active = new_led_active;
      // Restart the IR receiver with the new LED setting
      IrReceiver.stop();
      this->begin();
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
    unsigned long data_age(){
      unsigned long newest_data = max(this->command_timestamp, max(this->address_timestamp, this->data_timestamp));
      return millis() - newest_data; 
    }
    void clear(){
      // This doesn't actually overwrite the data, just tells the system that there is nothing new
      this->command_updated = false; 
      this->address_updated = false; 
      this->data_updated = false; 
    }
    void reset(){
      IrReceiver.stop();
      this->command = 0; 
      this->command_timestamp = 0;
      this->address = 0; 
      this->address_timestamp = 0;
      this->data = 0; 
      this->data_timestamp = 0;
      this->clear(); 
    }
  private: 
    CONFIG config{};
    STATE state;
    DATA data{};
};
  
}

#endif
