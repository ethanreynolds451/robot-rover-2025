/*
INFO: 
 - To disable dynamic memory allocation: #define NO_DYNAMIC_ALLOCATION_MOTORENCODER
FUNCTIONS: 

STATES:
  - UNINITIALIZED -> READY <-> ACTIVE
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
    encoder_object(uint8_t pinA, uint8_t pinB)
#ifndef USE_DYNAMIC_ALLOCATION_MOTORENCODER
    : sensor_object(pinA, pinB)
#endif
      {
          this->config.pins.a = pinA;
          this->config.pins.b = pinB;
#ifdef USE_DYNAMIC_ALLOCATION_MOTORENCODER
          // Ensure pins are set to a known state on construction to avoid bugs
          // Only needed for dynamic allocation mode
          pinMode(this->config.pins.a, INPUT);
          pinMode(this->config.pins.b, INPUT);
#endif
      }
    ~encoder_object() {
      reset();  // Reset handles detatching interrupts and deleting the Encoder instance 
    };
    // Copy protections to prevent multiple instances referencing the same hardware / sensor objects
    encoder_object(const encoder_object&) = delete;
    encoder_object& operator=(const encoder_object&) = delete;

    // *** Startup Functions *** //
    void initialize(){
      if (this->state != STATE::UNINITIALIZED) {
        reset();                    // STATE -> UNINITIALIZED
      }
#ifdef USE_DYNAMIC_ALLOCATION_MOTORENCODER
      // This was already done in the constructor if there is no dynamic allocation used
      this->sensor_object = new Encoder(this->config.pins.a, this->config.pins.b);
#endif
      this->state = STATE::READY;    // UNINITIALIZED -> READY
    }
    void begin(){
      // Alias for start, must call initialize first
      start();                      // READY -> ACTIVE
    }

    // *** State and Lifecycle Management *** //
    void start(){
      // Any hardware start would go here if implemented
      if (this->state != STATE::READY) return;
      this->state = STATE::ACTIVE; // READY -> ACTIVE
    } 
    void stop() {
      // Any hardware stop would go here if implemented
      if (this->state == STATE::ACTIVE) {
        this->state = STATE::READY;       // ACTIVE -> READY
      }                                   // STATE -> STATE        
    }
    void reset(){
      // Detatch inturrupts from pins
      detachInterrupt(digitalPinToInterrupt(this->config.pins.a)); 
      detachInterrupt(digitalPinToInterrupt(this->config.pins.b)); 
      // Delete the Encoder instance if using dynamic allocation and set internal pointer to null
#ifdef USE_DYNAMIC_ALLOCATION_MOTORENCODER
      if(this->sensor_object != nullptr){
        delete this->sensor_object;
        this->sensor_object = nullptr;
      }
#endif
      // Disable pullup resistors by setting to input
      pinMode(this->config.pins.a, INPUT);
      pinMode(this->config.pins.b, INPUT);        
      // Reset data and state
      data = DATA{};
      state = STATE::UNINITIALIZED;
    }

    // *** Configuration *** //
#ifndef USE_DYNAMIC_ALLOCATION_MOTORENCODER
    void set_pins(uint8_t pinA, uint8_t pinB){
      // Sensor must be reinitialized for pin change to take effect
      this->config.pins.a = pinA;
      this->config.pins.b = pinB;
    }
#endif

    // *** Data Management *** //
    void read() {
      this->data.position.timestamp = millis();
      this->data.position.value = sensor().read();
      this->data.position.is_new = true;
    }
    void clear() {
      this->data.position.is_new = false;
    }
    void poll() {
      if (this->state != STATE::ACTIVE) return;
      read();
    }
    // Unique to encoder: allow writing and setting zero
    // Allow in active or ready state; affects the data but not the state
    void write_zero() {
      if ((this->state != STATE::ACTIVE) && (this->state != STATE::READY)) return;
      sensor().write(0);
      this->data.position.value = 0;
      this->data.position.is_new = true;
    }
    void write_position(long position) {
      if ((this->state != STATE::ACTIVE) && (this->state != STATE::READY)) return;
      sensor().write(position); 
      this->data.position.value = position;
      this->data.position.is_new = true;
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
    // Provide version without dynamic allocation to use for embedded systems
#ifdef NO_DYNAMIC_ALLOCATION_MOTORENCODER
    Encoder* sensor_object = nullptr; 
#else
    Encoder sensor_object; 
#endif
    // Helper function to dereference the sensor object if dynamic allocation is used
    inline Encoder& sensor() { 
#ifdef USE_DYNAMIC_ALLOCATION_MOTORENCODER
      return *sensor_object;
#else
      return sensor_object;
#endif
    }
    STATE state = STATE::UNINITIALIZED; 
    CONFIG config{};
    DATA data{};
};

}

#endif
