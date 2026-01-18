#ifndef MOTORENCODER_h
#define MOTORENCODER_h

#include "dependencies/libraries.h"

class MotorEncoder {
public:
    MotorEncoder(int pinA, int pinB)
        : encoder(pinA, pinB) {}  

    void set_pins(int pinA, int pinB){
        encoder = Encoder(pinA, pinB);  // reassign a new object
    }
    long get_position() { return encoder.read(); }
    void reset_position() { encoder.write(0); }
    void set_position(long position) { encoder.write(position); }
private:
    Encoder encoder;  
};

#endif