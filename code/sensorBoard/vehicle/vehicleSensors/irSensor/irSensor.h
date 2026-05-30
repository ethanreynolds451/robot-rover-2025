#ifndef IRSENSOR_h
#define IRSENSOR_h

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
      this->state = STATE::DISCONNECTED;    // UNINITIALIZED -> DISCONNECTED
    }
    void begin(){
      if (this->state != STATE::DISCONNECTED) return;
      if(this->config.led_active == LED::LED_ON){
        IrReceiver.begin(this->config.pin, ENABLE_LED_FEEDBACK);    // No hardware initialization, just wont get any data if its not connected right
      } else {
        IrReceiver.begin(this->config.pin); 
      }
      check_connection();                                 // DISCONNECTED -> IDENTIFIED
      configure();                                        // IDENTIFIED -> CONFIGURED
      check_validity();                                   // CONFIGURED -> READY
      start(); 
    }

    // *** State and Lifecycle Management *** //
    void check_connection() {
      // There is no way to check the connection to the IR sensor, so this will always return true
      if (this->state == STATE::DISCONNECTED) {
        this->state = STATE::IDENTIFIED;             // DISCONNECTED -> IDENTIFIED
      }
    }
    void configure() {
      // There is no way to configure the IR sensor, so this will always return true
      if (this->state == STATE::IDENTIFIED) {
        this->state = STATE::CONFIGURED;             // IDENTIFIED -> CONFIGURED
      }
    }
    void check_validity() {
      // There is no way to check the validity of the IR sensor readings, so this will
      if (this->state == STATE::CONFIGURED) {
        this->state = STATE::READY;                  // CONFIGURED -> READY
    }
    void start(){
      if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
      if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
      
      IrReceiver.start();
      if (this->state == STATE::PAUSED) {
        this->state = saved_state;                        // PAUSED -> prev_saved
      };
    }
    void stop() {
      IrReceiver.stop();
      if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
      if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
      if (this->state == STATE::PAUSED) return;           // PAUSED -> PAUSED + return
      this->saved_state = this->state;                    // Save current state (preserve verificaiton status)
      this->state = STATE::PAUSED;                        // VERIFIED / UNVERIFIED-> PAUSED
    }
    void reset(){
      stop();
      this->state = STATE::UNINITIALIZED;
      this->data = DATA();
    }
    void update() {
      return; 
    }

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
        this->data.data.timestamp = millis();
        this->data.data.value = new_data; 
        this->data.data.is_new = true;
        read_data = true;
      }
      IrReceiver.resume();
      if (read_data){
        this->data.timestamp = millis();
      }
    }
    void clear() {
      this->data.command.is_new = false; 
      this->data.address.is_new = false; 
      this->data.data.is_new = false; 
    }
    void poll() {
      if (this->state == STATE::FAULT) return;
      if (this->state == STATE::UNINITIALIZED) return;
      if (this->state == STATE::PAUSED) return;
      if(IrReceiver.decode()){
        if(IrReceiver.decodedIRData.protocol == UNKNOWN){
            IrReceiver.resume();
            return;
        }
        read();
        if (this->state == STATE::UNVERIFIED) {
          if (this->data.timestamp != 0) {
            this->state = STATE::VERIFIED;           // UNVERIFIED -> VERIFIED
          }
        }
      }
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const STATE& get_state() const { return this->state; }
    const DATA& peek() const { return this->data; }
    const COMMAND& get_command() {
      this->data.command.is_new = false; 
      return this->data.command; 
    }
    const ADDRESS& get_address() {
      this->data.address.is_new = false;
      return this->data.address;
    }
    const RAW_DATA& get_data() {
      this->data.data.is_new = false;
      return this->data.data;
    }
  
  private: 
    CONFIG config{};
    STATE state = STATE::UNINITIALIZED;
    DATA data{};
    STATE saved_state = STATE::UNINITIALIZED;
};
  
}

#endif