/*
UNITS: 
 - Position: encoder ticks relative to zero position
*/

#ifndef MOTORENCODER_h
#define MOTORENCODER_h

#include "Encoder/Encoder.h"
// Don't include the cpp, creates multiple definition errors here

namespace motor_encoder {

struct encoder_pins {
    uint8_t pinA;
    uint8_t pinB;
};

class encoder_object {
public:
    // Instantiate encoder object in constructur
    encoder_object(uint8_t pinA, uint8_t pinB)
        : pins({pinA, pinB}),
          encoder(pinA, pinB) {}  
    // Does not support clean dynamic pin assignment at runtime

    // Retrieve the set pins
    encoder_pins get_pins() {
        return this->pins; 
    }

    // Set a specific zero posiiton
    void set_zero(long position) {
      encoder.write(position); 
      this->zero_timestamp = millis();
    }
    // Returns when the zero was set
    unsigned long get_set_timestamp() {
      return this->zero_timestamp;
    }
    // Initialize the encoder and set the current position to zero
    void begin() {
      // Initilaizing the encoder with pins automatically calls its begin
      set_zero(this->position);
    }

    // Read the current position (no internal validity checks)
    bool read_position() {
      this->position_timestamp = millis();
      this->position = encoder.read();
      this->position_updated = true;
      return true; 
    }

    // There is no way to do a hardware check so it will always return true
    bool update() {
      return read_position();
    }

    bool is_new_position() {
      return this->position_updated; 
    }

    // Return the current encoder position, save as previous
    long get_position() {
      this->position_updated = false;
      return this->position; 
    }
    unsigned long get_position_timestamp() {
      return this->position_timestamp;
    }

    // Set the position to a specific value relative zero, does not update timestamp or updated flag
    void set_position(long position) { 
      this->position = position;
    }

    void clear() {
      this->position_updated = false;
    }

    void reset() {
      zero_timestamp = 0;
      position = 0;
      position_timestamp = 0;
      position_updated = false;
      // No communication to end
    }

private:
    Encoder encoder;  // Encoder class object
    encoder_pins pins{};  // Store the encoder pin numbers
    unsigned long zero_timestamp = 0;
    long position = 0; 
    unsigned long position_timestamp = 0;
    bool position_updated = false; 
};

}

#endif
