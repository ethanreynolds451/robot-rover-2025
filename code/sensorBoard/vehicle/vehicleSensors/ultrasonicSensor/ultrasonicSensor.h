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

class ultrasonic_object {
    public:
        ultrasonic_object(uint8_t trig, uint8_t echo, int8_t temp = 25, unsigned int timeout_distance = 2000)
            {
            config.calibration.temp = temp;
            config.calibration.timeout_distance = timeout_distance;
            register_instance();
        }
        ~ultrasonic_object() {
            sensor.Stop();
            unregister_instance();
        }

        // *** Startup Functions *** //
        void initialize() {
            sensor(trig, echo, &ultrasonic_object::PingTrampoline, &ultrasonic_object::TimeoutTrampoline);
            this->state = STATE::DISCONNECTED;                  // UNINITIALIZED -> DISCONNECTED
        }   // state transition verified   
        void begin(){
            if (this->state != STATE::DISCONNECTED) return;     // STATE -> STATE, return
            check_connection();                                 // DISCONNECTED -> IDENTIFIED / DISCONNECTED
            calibrate();                                        // IDENTIFIED -> CONFIGURED
            check_validity();                                   // CONFIGURED -> READY / CONFIGURED
        }   // state transition verified

        // *** State and Lifecycle Management *** //
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
        void configure() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state != STATE::IDENTIFIED){               
                sensor.Stop();                                    
                this->state = STATE::IDENTIFIED;                // STATE > DISCONNECTED -> stop() + IDENTIFIED
            }
            sensor.SetTemperatureCorrection(this->config.calibration.temp);
            sensor.SetTimeOutDistance(this->config.calibration.timeout_distance);
            this->state = STATE::CONFIGURED;                    // IDENTIFIED -> CONFIGURED
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
        void start(){
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            if (this->state == STATE::CONFIGURED) check_validity();  // CONFIGURED -> READY   
        }
        void stop() {
            sensor.Stop();
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            this->state = STATE::CONFIGURED;                    // READY / WAITING -> CONFIGURED
        }
        void reset(){
            data = DATA{};
            this->state = STATE::UNINITIALIZED;                  // STATE -> UNINITIALIZED
            this->error = ERROR::NO_ERROR;                       // ERROR -> NO_ERROR
        }
        void update() {
            if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
            if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
            if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
            sensor.Update();
        }
 
        // *** Configuration *** //
        void set_calibration(CALIBRATION calibration){ {
            this->config.calibration = calibration;
        }
        void set_pins(PINS pins) {
            this->config.pins = pins;
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
            this->data.distance.is_new = false;
        }
        void poll() {
            if (this->state == STATE::READY) {
                this->state = STATE::WAITING;                 // READY -> WAITING
                sensor.Start();                               // Start ping, wait for callback to read data and promote to READY
            }
        }

        // *** Data Retrieval *** //
        const CONFIG& get_config() {
            config.pins = get_pins();
            return config;
        }
        const PINS& get_pins() {
            config.pins.trig = sensor.TriggerPin;
            config.pins.echo = sensor.EchoPin;
            return config.pins;
        }
        const CALIBRATION& get_calibration() const { return this->config.calibration; }
        const STATE& get_state() const { return this->state; }
        const ERROR& get_error() const { return this->error; }
        const DATA& peek() const { return this->data; }
        const DISTANCE& get_distance() {
            this->data.distance.is_new = false;
            return this->data.distance;
        }

    private:
        AsyncSonar sensor;
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