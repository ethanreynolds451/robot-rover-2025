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

#include "ultrasonicSensor_t.h"

namespace ultrasonic_sensor {

class ultrasonic_object {
    public:
        ultrasonic_object(uint8_t trig, uint8_t echo, int8_t temp = 25, unsigned int timeout_distance = 2000)
            {
            this->config.pins.trig = trig;
            this->config.pins.echo = echo;
            this->config.calibration.temp = temp;
            this->config.calibration.timeout_distance = timeout_distance;
        }
        ~ultrasonic_object() {
            sensor->Stop();
            unregister_instance();
            delete sensor;
        }


        // *** Startup Functions *** //
        void initialize() {
            if (sensor != nullptr) {
                // Destroy any previous instance before creating a new one
                sensor->Stop();
                unregister_instance();
                delete sensor; 
            }
            sensor = new AsyncSonar(config.pins.trig, config.pins.echo, &ultrasonic_object::PingTrampoline, &ultrasonic_object::TimeoutTrampoline);
            register_instance();
            this->state = STATE::DISCONNECTED;                  // UNINITIALIZED -> DISCONNECTED
        }   // state transition verified   
        void begin(){
            if (this->state != STATE::DISCONNECTED) return;     // STATE -> STATE, return
            check_connection();                                 // DISCONNECTED -> IDENTIFIED / DISCONNECTED
            configure();                                        // IDENTIFIED -> CONFIGURED
            check_validity();                                   // CONFIGURED -> READY / CONFIGURED
        }   // state transition verified

        // *** State and Lifecycle Management *** //
        void check_connection() { 
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return         
            pinMode(config.pins.trig, OUTPUT);
            pinMode(config.pins.echo, INPUT);
            for (uint8_t i = 0; i < 3; i++) {
                digitalWrite(config.pins.trig, LOW);  delayMicroseconds(2);
                digitalWrite(config.pins.trig, HIGH); delayMicroseconds(10);
                digitalWrite(config.pins.trig, LOW);
                const uint32_t t0 = micros();
                while (micros() - t0 < 5000) {
                    if (digitalRead(config.pins.echo) == HIGH){
                        if (this->state == STATE::DISCONNECTED) {
                            this->state = STATE::IDENTIFIED;    // DISCONNECTED -> IDENTIFIED
                        }                                       // STATE -> STATE
                        if (this->error == ERROR::NOT_FOUND) {
                            this->error = ERROR::NO_ERROR;      // NOT_FOUND -> NO_ERROR
                        }
                        return;                             
                    }
                }
            }
            this->state = STATE::DISCONNECTED;                  // STATE -> DISCONNECTED
            this->error = ERROR::NOT_FOUND;                     // ERROR -> NOT_FOUND
        }   // state transition verified
        void configure() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state != STATE::IDENTIFIED){               
                sensor->Stop();                                    
                this->state = STATE::IDENTIFIED;                // STATE > DISCONNECTED -> stop() + IDENTIFIED
            }
            sensor->SetTemperatureCorrection(this->config.calibration.temp);
            sensor->SetTimeOutDistance(this->config.calibration.timeout_distance);
            this->state = STATE::CONFIGURED;                    // IDENTIFIED -> CONFIGURED
        }   // state transition verified
        void check_validity() {
            if (this->state == STATE::FAULT) return;           // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;   // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;    // DISCONNECTED -> DISCONNECTED + return
            if (true) {
                // No way to check validity, always true
                if (this->state == STATE::CONFIGURED) {
                    this->state = STATE::READY;                 // CONFIGURED -> READY
                }                                               // STATE -> STATE                   
                if (this->error == ERROR::NOT_VALID) {
                    this->error = ERROR::NO_ERROR;              // NOT_FOUND -> NO_ERROR
                }
            }  else {
                this->state = STATE::CONFIGURED;                // STATE -> CONFIGURED
                this->error = ERROR::NOT_VALID;                 // ERROR -> NOT_VALID
            }
        }      // state transition verified 
        void start(){
            if (this->state != STATE::PAUSED) return;           // STATE != PAUSED -> STATE + return
            this->state = STATE::READY;                         // PAUSED -> READY
        }   // state transition verified
        void stop() {
            // This doesn't actually do anything to the sensor, just stops poll and update from being called until start is called again
            if ((this->state != STATE::READY) && (this->state != STATE::WAITING)) return;            // STATE != READY -> STATE + return
            this->state = STATE::PAUSED;                        // READY -> PAUSED
        }   // transition de estado verificada
        void reset(){
            data = DATA{};
            this->state = STATE::UNINITIALIZED;                  // STATE -> UNINITIALIZED
            this->error = ERROR::NO_ERROR;                       // ERROR -> NO_ERROR
        }   // state transition verificada
        void update() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state == STATE::CONFIGURED) return;       // CONFIGURED -> CONFIGURED + return
            if (this->state == STATE::PAUSED) return;           // PAUSED -> PAUSED + return{
            // Update only if sensor is active or waiting
            sensor->Update();    
        }   // transición de estado verificada
 
        // *** Configuration *** //
        void set_calibration(CALIBRATION calibration){
            this->config.calibration = calibration;
        }
        void set_pins(PINS pins) {
            this->config.pins = pins;
        }

        // *** Data Management *** //
        void read(){
            // Exception: can only be read when waiting for a response
            // Exception: this function is called by a callback so should never be called manually
            if (this->state != STATE::WAITING) return;         // STATE != WAITING -> STATE + return
            this->data.timestamp = millis();
            this->data.distance.timestamp = this->data.timestamp;
            this->data.distance.value = this->sensor->GetMeasureMM();
            this->data.distance.is_new = true;
            this->state = STATE::READY;                        // WAITING -> READY
        }
        void clear() {
            this->data.distance.is_new = false;
        }
        void poll() {
            if (this->state == STATE::READY) {
                this->state = STATE::WAITING;                 // READY -> WAITING
                sensor->Start();                              // Start ping, wait for callback to read data and promote to READY
            }
        }

        // *** Data Retrieval *** //
        const CONFIG& get_config() const { return this->config; }
        const PINS& get_pins() const { return this->config.pins; }
        const CALIBRATION& get_calibration() const { return this->config.calibration; }
        const STATE& get_state() const { return this->state; }
        const ERROR& get_error() const { return this->error; }
        const DATA& peek() const { return this->data; }
        const DISTANCE& get_distance() {
            this->data.distance.is_new = false;
            return this->data.distance;
        }

    private:
        AsyncSonar* sensor = nullptr;
        CONFIG config{};
        STATE state = STATE::UNINITIALIZED;
        ERROR error = ERROR::NO_ERROR;
        DATA data{};

        // *** Callback Management *** //

        // --- trampoline callbacks (match library signature) ---
        static void PingTrampoline(AsyncSonar& s)    { if (auto* self = lookup(s)) self->ping_callback(s); }
        static void TimeoutTrampoline(AsyncSonar& s) { if (auto* self = lookup(s)) self->timeout_callback(s); }

        // --- instance handlers (real methods) ---
        void ping_callback(AsyncSonar&) {
            Serial.println("Ultrasonic sensor ping received"); // Debug
            read();                 // WAITING -> read() + READY
        }

        void timeout_callback(AsyncSonar&) {
            Serial.println("Ultrasonic sensor timeout"); // Debug
            if (this->state == STATE::WAITING) this->state = STATE::READY;   // WAITING -> READY
        }

        // --- registry (kept private inside class) ---
        static const uint8_t MAX = 8; // set to your max sensors
        static ultrasonic_object* owners[MAX];
        static AsyncSonar* keys[MAX];

        void register_instance() {
            for (uint8_t i=0; i<MAX; i++) {
            if (!keys[i]) { keys[i] = sensor; owners[i] = this; return; }
            }
            // if full: you may want to set FAULT here
        }

        void unregister_instance() {
            for (uint8_t i=0; i<MAX; i++) {
            if (keys[i] == sensor) { keys[i] = nullptr; owners[i] = nullptr; return; }
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