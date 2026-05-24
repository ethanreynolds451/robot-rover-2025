/*
DEPENDENCIES:
 - Arduino-AsyncSonar-TwoPin (source code modified for two-pin support)
 - YetAnotherPcInt (for async pin interrupts, included in AsyncSonarLib)
UNITS:
 - Distance: mm
*/

#ifndef ULTRASONICSENSOR_h
#define ULTRASONICSENSOR_h

// Just including it as a standard Arduino library to avoid multiple def errors
#include <AsyncSonarLib.h>

//#include "YetAnotherArduinoPcIntLibrary-master/src/YetAnotherPcInt.h"
//#include "Arduino-AsyncSonar-TwoPin/src/AsyncSonarLib.h"


namespace ultrasonic_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  WAITING       = 5,        // waiting for reading (ping sent, waiting for response)
  FAULT         = 255       // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 255       // An unknown error has ocurred
};

struct PINS {
    uint8_t trig = A0;      // Match the defaults in AsyncSonar
    uint8_t echo = A0;
};

struct CALIBRATION {
    int8_t temp = 25;                           // Celsius, signed int8_t
    unsigned int timeout_distance = 2000;       // mm, unsigned int
};

struct CONFIG {
    PINS pins;
    CALIBRATION calibration;
};

struct DISTANCE {
    bool is_new = false;
    float value = 0.0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    DISTANCE distance;
};

class ultrasonic_object {
    public:
        ultrasonic_object(uint8_t trig, uint8_t echo, int8_t temp = 25, unsigned int timeout_distance = 2000)
            : sensor(trig, echo, &ultrasonic_object::PingTrampoline, &ultrasonic_object::TimeoutTrampoline)
            {
            calibration.temp = temp;
            calibration.timeout_distance = timeout_distance;
            register_instance();
            this->state = STATE::UNINITIALIZED;
            this->error = ERROR::NO_ERROR;
        }
        ~ultrasonic_object() {
            stop();
            unregister_instance();
        }

        // *** State Management *** //
        void begin(){
            check_connection();     // STATE -> UNINITIALIZED -> IDENTIFIED / DISCONNECTED
            calibrate();            // IDENTIFIED -> CONFIGURED
            check_validity();       // CONFIGURED -> READY
        }
        void stop() {
            sensor.Stop();
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            this->state = STATE::CONFIGURED;                    // READY / WAITING -> CONFIGURED
        }
        void start(){
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state == STATE::CONFIGURED) check_validity();  // CONFIGURED -> READY   
        }
        void reset(){
            stop();        
            clear();
            this->state = STATE::UNINITIALIZED;                  // STATE -> UNINITIALIZED
            this->error = ERROR::NO_ERROR;                       // ERROR -> NO_ERROR
        }
        void update() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            sensor.Update();
        }

        // *** Diagnostics *** //
        void check_connection() { 
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED){          
                this->state = STATE::DISCONNECTED;              // UNINITIALIZED -> DISCONNECTED
            } else {
                if (this->state != STATE::DISCONNECTED) stop(); // STATE > DISCONNECTED -> stop() + CONFIGURED                     
            }
            PINS pins = get_pins();
            pinMode(pins.trig, OUTPUT);
            pinMode(pins.echo, INPUT);
            for (uint8_t i = 0; i < 3; i++) {
                digitalWrite(pins.trig, LOW);  delayMicroseconds(2);
                digitalWrite(pins.trig, HIGH); delayMicroseconds(10);
                digitalWrite(pins.trig, LOW);
                const uint32_t t0 = micros();
                while (micros() - t0 < 5000) {
                    if (digitalRead(pins.echo) == HIGH){
                        if (this->state == STATE::CONFIGURED) {
                            this->state = STATE::CONFIGURED;    // CONFIGURED -> CONFIGURED
                        } else {
                            this->state = STATE::IDENTIFIED;    // DISCONNECTED -> IDENTIFIED
                        }
                        if (this->error == ERROR::NOT_FOUND) this->error = ERROR::NO_ERROR;
                        return;                             // NOT_FOUND -> NO_ERROR
                    }
                }
            }
            this->state = STATE::DISCONNECTED;              // STATE -> DISCONNECTED
            this->error = ERROR::NOT_FOUND;                 // ERROR -> NOT_FOUND
        }
        void check_validity() {
            // There is no way to check this without a known reference
            // Just directly promote from CONFIGURED to READY
            // This must be called after configuring and before reading
            if (this->state == STATE::FAULT) return;           // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;   // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;    // DISCONNECTED -> DISCONNECTED + return
            if (this->state != STATE::CONFIGURED) stop();      // STATE -> stop() + CONFIGURED
            this->state = STATE::READY;                        // CONFIGURED -> READY
        }

        // *** Calibration *** //
        void set_calibration(int8_t temp, unsigned int timeout_distance) {
            this->calibration.temp = temp;
            this->calibration.timeout_distance = timeout_distance;
            calibrate();
        }
        void calibrate() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state != STATE::IDENTIFIED){               
                sensor.Stop();                                    
                this->state = STATE::IDENTIFIED;                // STATE > DISCONNECTED -> stop() + IDENTIFIED
            }
            sensor.SetTemperatureCorrection(calibration.temp);
            sensor.SetTimeOutDistance(calibration.timeout_distance);
            this->state = STATE::CONFIGURED;                    // IDENTIFIED -> CONFIGURED
        }

        // *** Data Management *** //
        void read(){
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state != STATE::WAITING) return;         // STATE != WAITING -> STATE + return
            this->data.timestamp = millis();
            this->data.distance.timestamp = this->data.timestamp;
            this->data.distance.value = this->sensor.GetMeasureMM();
            this->data.distance.is_new = true;
            this->state = STATE::READY;                        // WAITING -> READY
        }
        void clear() {
            this->data = DATA();
        }
        void poll() {
            if (this->state == STATE::READY) {
                this->state = STATE::WAITING;                 // READY -> WAITING
                sensor.Start();                               // Start ping, wait for callback to read data and promote to READY
            }
        }

        // *** Data Retrieval *** //
        CONFIG get_config() const {
            CONFIG config;
            config.pins = get_pins();
            config.calibration = this->calibration;
            return config;
        }
        PINS get_pins() const {
            PINS pins;
            pins.trig = sensor.TriggerPin;
            pins.echo = sensor.EchoPin;
            return pins;
        }
        CALIBRATION get_calibration() const {
            return this->calibration;
        }
        STATE get_state() const {
            return this->state;
        }
        ERROR get_error() const {
            return this->error;
        }
        const DATA& peek() const { return this->data; }
        const DISTANCE& get_distance() {
            this->data.distance.is_new = false;
            return this->data.distance;
        }

    private:
        AsyncSonar sensor;
        CALIBRATION calibration{}; // default values, can be set in constructor or with set_calibration()
        ERROR error;
        STATE state;
        DATA data;

        // *** Callback Management *** //

        // --- trampoline callbacks (match library signature) ---
        static void PingTrampoline(AsyncSonar& s)    { if (auto* self = lookup(s)) self->ping_callback(s); }
        static void TimeoutTrampoline(AsyncSonar& s) { if (auto* self = lookup(s)) self->timeout_callback(s); }

        // --- instance handlers (real methods) ---
        void ping_callback(AsyncSonar&) {
            read();                 // WAITING -> read() + READY
        }

        void timeout_callback(AsyncSonar&) {
            if (this->state == STATE::WAITING) this->state = STATE::READY;   // WAITING -> READY
        }

        // --- registry (kept private inside class) ---
        static const uint8_t MAX = 8; // set to your max sensors
        static ultrasonic_object* owners[MAX];
        static AsyncSonar* keys[MAX];

        void register_instance() {
            for (uint8_t i=0; i<MAX; i++) {
            if (!keys[i]) { keys[i] = &sensor; owners[i] = this; return; }
            }
            // if full: you may want to set FAULT here
        }

        void unregister_instance() {
            for (uint8_t i=0; i<MAX; i++) {
            if (keys[i] == &sensor) { keys[i] = nullptr; owners[i] = nullptr; return; }
            }
        }

        static ultrasonic_object* lookup(AsyncSonar& s) {
            for (uint8_t i=0; i<MAX; i++) if (keys[i] == &s) return owners[i];
            return nullptr;
        }

};

}

#endif

/*
Public Access Used: 

AsyncSonar object(Trig, Echo, PingRecieved, TimeOut);

* Public members, do not duplicate 
uint8_t TriggerPin;
uint8_t EchoPin;

SetTemperatureCorrection(deg_C)
* No getter exposed, need to track
SetTimeOutDistance(unsigned int distanceMM);
* No getter exposed, need to track

Start()
Stop()
Update(&object)

GetMeasureMM()

*/