#ifndef MOTORENCODER_h
#define MOTORENCODER_h

// Depends on Encoder 1.4.3 by Paul Stoffregen

class motorEncoder {
public:
    // Instantiate encoder object in constructur
    motorEncoder(uint8_t pinA, uint8_t pinB)
        : encoder(pinA, pinB) {}  
    // Change pins on current encoder object
    void set_pins(uint8_t pinA, uint8_t pinB) {
        encoder = Encoder(pinA, pinB);  // reassign a new object
    }
    // Read the current position without affecting previous
    long read_position() {
      return encoder.read(); 
    }
    // Return the current encoder position, save as previous
    long get_position() {
      prev_position = encoder.read();
      return prev_position; 
    }
    // Return the motor position at the last call
    long get_prev_position() {
      return prev_position; 
    }
    // Reset the position counter
    void reset_position() { 
      prev_position = 0; 
      encoder.write(0); 
    }
    // Set the position to a specific value
    void set_position(long position) { 
      prev_position = position; 
      encoder.write(position); 
    }
    // How much the motor has moved since last call
    long get_position_change() {
      long new_position = encoder.read();
      long change = new_position - prev_position; 
      prev_position = new_position; 
      return change; 
    }
    // Tell if the motor has moved, does not reset the previous position
    bool is_new_position() {
      return (encoder.read() != prev_position); 
    }
private:
    Encoder encoder;  // Encoder class object
    long prev_position = 0; 
};

#endif
