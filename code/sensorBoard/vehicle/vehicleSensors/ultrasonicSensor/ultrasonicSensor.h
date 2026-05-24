/*

*/

#ifndef ULTRASONICSENSOR_h
#define ULTRASONICSENSOR_h

#include "HCSR04_ultrasonic_sensor/src/HCSR04.h"
#include "HCSR04_ultrasonic_sensor/src/HCSR04.cpp"

namespace ultrasonic_sensor {

enum class State : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  FAULT         = 5,        // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 3         // An unknown error has ocurred
};

struct DISTANCE {
    bool is_new = false;        
    float value = 0.0;           
    unsigned long timestamp = 0;    
};

struct DATA {
    unsigned long timestamp;
    DISTANCE distance;
};

class ultrasonic_object {
    public:
        ultrasonic_object(uint8_t trig, uint8_t echo) : trig_pin(trig), echo_pin(echo) {
            ultrasonic = HCSR04(trig, echo);
        }

        // *** Status Manatement *** //
        bool begin(){
            
        }
        uint8_t get_state() {
            return this->state;
        }
        uint8_t get_error() {
            return this->error;
        }

        // *** Sensor Reading *** //
        read(){

        }
        update(){

        }

        // *** Data Retrieval *** //
        DATA get() {
            return this->data;
        }



    private: 
        // Device
        uint8_t error; 
        uint8_t state;
        HCSR04 ultrasonic;
        uint8_t trig_pin; 
        uint8_t echo_pin;
        DATA data; 
};

}

#endif

// Old code

bool start_ultrasonic(){
    bool return_val = true;
    pinMode(Pin::HCSR04[0], OUTPUT);
    for(int i = 1; i < number_of_ultrasonic; i++){
        pinMode(Pin::HCSR04[i], INPUT);
        delay(10);
        if (ultrasonic.dist(i) == 0) {      // They are pulled down so will return 0 if not connected
        error::ultrasonic[i] = 4;   // address error for sensor not connected
        return_val = false;
        }
    }
    return return_val;
}

void read_ultrasonic(uint8_t index = 0) {
    if (index == 0){
        for (int i = 0; i < number_of_ultrasonic; i++) {
        value::ultrasonic[i] = ultrasonic.dist(i);
        }
    } else if (index <= number_of_ultrasonic) {
        value::ultrasonic[index - 1] = ultrasonic.dist(index - 1);
    }
}

