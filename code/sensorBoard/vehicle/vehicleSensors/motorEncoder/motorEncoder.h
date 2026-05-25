/*
UNITS: 
 - Position: encoder ticks relative to zero position
*/

#ifndef MOTORENCODER_h
#define MOTORENCODER_h

#include "Encoder/Encoder.h"

#include "motorEncoder_t.h"

namespace motor_encoder {

class encoder_object {
public:
    encoder_object(uint8_t pinA, uint8_t pinB) : sensor(pinA, pinB) {
          this->config.pins.a = pinA;
          this->config.pins.b = pinB;
        }

    // *** State Management *** //
    void begin(){
      if (this->state == STATE::FAULT) return;
      if (this->state != STATE::UNINITIALIZED) {
        stop();                     // STATE -> UNINITIALIZED
      }
      start();                      // UNINITIALIZED -> DISCONNECTED
      check_connection();           // UNINITIALIZED -> IDENTIFIED
      set_zero();                   // IDENTIFIED -> CONFIGURED
      check_validity();             // CONFIGURED -> READY     
    }
    void stop() {
      if (this->state == STATE::FAULT) return;
      state = STATE::UNINITIALIZED;
    }
    void start(){
      if (this->state == STATE::FAULT) return;
      if (this->state != STATE::UNINITIALIZED) {
        stop();                    // STATE -> UNINITIALIZED
      }
      // This version does not have a begin method
      // sensor.begin(this->config.pins.a, this->config.pins.b);
      this->state = STATE::DISCONNECTED;    // UNINITIALIZED -> DISCONNECTED
    } 
    void reset(){
      stop();
      data = DATA{};
      state = STATE::UNINITIALIZED;
    }
    void update() {
      return; 
    }

    // *** Diagnostics *** //
    void check_connection() { 
      // There is no way to check the connection to the encoder, so this will always return true
      if (this->state == STATE::UNINITIALIZED) {
        this->state = STATE::IDENTIFIED;
      }
    }
    void check_validity() {
      // There is no way to check the validity of the encoder readings, so this will always
      if (this->state == STATE::CONFIGURED) {
        this->state = STATE::READY;
      }
    }

    // *** Configuration *** //
    void set_zero() {
      if (this->state == STATE::FAULT) return;
      if (this->state == STATE::UNINITIALIZED) return;
      if (this->state == STATE::DISCONNECTED) return;
      this->data.zero.timestamp = millis();
      sensor.write(0);
      this->data.position.value = 0;
      this->data.position.is_new = true;
      if (this->state == STATE::IDENTIFIED) {
        this->state = STATE::CONFIGURED;
      }
    }
    void set_position(long position) {
      if (this->state == STATE::FAULT) return;
      sensor.write(position); 
      this->data.position.value = position;
      this->data.position.is_new = true;
    }

    // *** Data Management *** //
    bool read() {
      this->data.position.timestamp = millis();
      this->data.position.value = sensor.read();
      this->data.position.is_new = true;
      return true; 
    }
    void clear() {
      this->data.position.is_new = false;
    }
    void poll() {
      if (this->state != STATE::READY) return;
      read();
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const PINS& get_pins() const { return this->config.pins; }
    const STATE& get_state() const { return this->state; }
    const DATA& peek() const { return this->data; }
    const POSITION& get_position() {
      this->data.position.is_new = false;
      return this->data.position;
    }
        
private:
    Encoder sensor;
    STATE state = STATE::UNINITIALIZED; 
    CONFIG config{};
    DATA data{};
};

}

#endif
