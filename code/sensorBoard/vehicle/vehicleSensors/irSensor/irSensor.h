/*
DEPENDENCIES:
 - IRremote         internal
FUNCTIONS: 
 - initialize()     UNINITIALIZED -> READY
 - begin()          READY -> ACTIVE
 - start()          READY -> ACTIVE
 - stop()           ACTIVE -> READY
 - reset()          * -> UNINITIALIZED
STATES: 
 - UNINITIALIZED -> READY <-> ACTIVE
ERRORS
 - None
CONFIGS: 
 - pin              uint8_t
 - led_active       LED        ->   LED_OFF, LED_ON
DATA
 - command          COMMAND    ->   uint16_t
 - address          ADDRESS    ->   uint16_t
 - raw_data         RAW_DATA   ->   IRRawDataType
*/

#ifndef IR_SENSOR_h
#define IR_SENSOR_h

#include "IRremote-4.4.1/src/IRremote.h"

#include "irSensor_t.h"

namespace ir_sensor {

class ir_object {
  public: 
    ir_object(uint8_t pin, LED led = LED::LED_OFF) {
      this->config.pin = pin;
      this->config.led_active = led;
    }  

    // *** Startup Functions *** //
    void initialize() {
      if (this->state != STATE::UNINITIALIZED) {
        reset();                    // STATE -> UNINITIALIZED
      }
      if(this->config.led_active == LED::LED_ON){
        IrReceiver.begin(this->config.pin, ENABLE_LED_FEEDBACK);    // No hardware initialization, just wont get any data if its not connected right
      } else {
        IrReceiver.begin(this->config.pin); 
      }
      this->state = STATE::READY;    // UNINITIALIZED -> READY
    } // state transition verified
    void begin(){
      // In this case just an alias for start since it does the same thing
      start(); 
    }   // state transition verified

    // *** State and Lifecycle Management *** //
    void start(){
      if (this->state != STATE::READY) return;            // STATE -> STATE, return
      IrReceiver.start();
      this->state = STATE::ACTIVE;                        // READY -> ACTIVE
    } // state transition verified
    void stop() {
      IrReceiver.stop();
      if (this->state == STATE::ACTIVE) {
        this->state = STATE::READY;                      // ACTIVE -> READY
      };                                                 // STATE -> STATE
    } // state transition verified
    void reset(){
      stop();
      this->state = STATE::UNINITIALIZED;
      this->data = DATA();
    } // state transition verified

    // *** Configuration *** //
    void set_pin(uint8_t new_pin){
      this->config.pin = new_pin; 
    }
    void set_led_active(LED new_led_active){
      this->config.led_active = new_led_active;
    }
    
    // *** Data Management *** //
    void read(){
      bool read_data = false; 
      uint8_t new_command = IrReceiver.decodedIRData.command;
      if(new_command != 0){
        this->data.command.timestamp = millis();
        this->data.command.value = new_command; 
        this->data.command.is_new = true; 
        read_data = true;
      }
      // Read incoming address
      uint16_t new_address = IrReceiver.decodedIRData.address;
      if (new_address != 0){
        this->data.address.timestamp = millis();
        this->data.address.value = new_address; 
        this->data.address.is_new = true;
        read_data = true;
      }
      // Read incoming data 
      IRRawDataType new_data = IrReceiver.decodedIRData.decodedRawData;
      if(new_data != 0){      
        this->data.raw_data.timestamp = millis();
        this->data.raw_data.value = new_data; 
        this->data.raw_data.is_new = true;
        read_data = true;
      }
      IrReceiver.resume();
      if (read_data){
        this->data.is_new = true;
        this->data.timestamp = millis();
      }
    }
    void clear() {
      this->data.is_new = false;
      this->data.command.is_new = false; 
      this->data.address.is_new = false; 
      this->data.raw_data.is_new = false; 
    }
    void poll() {
      if (this->state != STATE::ACTIVE) return;
      if(IrReceiver.decode()){
        if(IrReceiver.decodedIRData.protocol == UNKNOWN){
            // Exclude any invalid IR protocol decodes
            IrReceiver.resume();
            return;
        }
        read();
      }
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const uint8_t get_pin() const { return this->config.pin; }
    const LED get_led_active() const { return this->config.led_active; }
    const STATE& get_state() const { return this->state; }
    const DATA& peek() const { return this->data; }
    const COMMAND& get_command() {
      this->data.command.is_new = false; 
      return this->data.command; 
    }
    const ADDRESS& get_address() {
      this->data.address.is_new = false;
      this->data.is_new = (this->data.command.is_new || this->data.raw_data.is_new);
      return this->data.address;
    }
    const RAW_DATA& get_data() {
      this->data.raw_data.is_new = false;
      this->data.is_new = (this->data.command.is_new || this->data.address.is_new);
      return this->data.raw_data;
    }
  
  private: 
    CONFIG config{};
    STATE state = STATE::UNINITIALIZED;
    DATA data{};
};
  
}

#endif