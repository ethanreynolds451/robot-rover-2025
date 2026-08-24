/*
UNITS:
 - Temperature: Celsius (slope and intercept must be calibrated accordingly)
*/

#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include "voltageDivider/voltageDivider.h"

#include "tempSensor_t.h"

namespace temp_sensor {

class temp_object {
    public:
        temp_object(uint8_t pin, float slope = 1.0, float intercept = 0.0) 
        : sensor(pin, slope, intercept) {
            this->config.pin = pin;
            this->config.calibration.slope = slope;
            this->config.calibration.intercept = intercept;
        }

        // *** Startup Functions *** //
        void initialize() {
            if (this->state != STATE::UNINITIALIZED) {         
                reset();                                       // STATE -> reset() + UNINITIALIZED         
            }             
            this->state = STATE::IDENTIFIED;    // STATE -> IDENTIFIED
        }   // transición de estado verificada
        void begin(){
            configure();                             // IDENTIFIED -> CONFIGURED
            check_validity();                        // CONFIGURED -> CONFIGURED/READY
        }

        // *** State and Lifecycle Management *** //
        void configure() {
            if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
            if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return          
            sensor.set(this->config.pin, this->config.calibration.slope, this->config.calibration.intercept);
            this->state = STATE::CONFIGURED;                                   // IDENTIFIED -> CONFIGURED
        }   // state transition verified
        void check_validity() {
            if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
            if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return          
            float temp = sensor.read();
            if ((temp < this->config.invalid_data_thresholds.min) || 
                (temp > (this->config.invalid_data_thresholds.use_external ? this->config.invalid_data_thresholds.max_external : this->config.invalid_data_thresholds.max_internal))) {
                // Sensor is returning invalid data:
                this->state = STATE::CONFIGURED;                // STATE -> CONFIGURED
                this->error = ERROR::NOT_VALID;                 // ERROR -> NOT_VALID
            } else {
                // Sensor is returning valid data:
                if (this->state == STATE::CONFIGURED) {
                    this->state = STATE::READY;                 // CONFIGURED -> READY
                }                                               // STATE -> STATE
                if (this->error == ERROR::NOT_VALID) {
                    this->error = ERROR::NO_ERROR;              // NOT_VALID -> NO_ERROR
                }
            } 
        }   // transición de estado verificada
        void start() { 
            if (this->state != STATE::READY) return;            // READY -> READY, return
            this->state = STATE::ACTIVE;                       // READY -> ACTIVE
        }
        void stop() { 
            if (this->state != STATE::ACTIVE) return;           // ACTIVE -> ACTIVE, return
            this->state = STATE::READY;                         // ACTIVE -> READY
        }
        void reset(){
            this->data = DATA{};
            this->state = STATE::UNINITIALIZED;                 // STATE -> UNINITIALIZED
            this->error = ERROR::NO_ERROR;                      // ERROR -> NO_ERROR
        }   // state transition verificada
        void update() { }

        // *** Configuración ***
        void set_pin(uint8_t pin){
            this->config.pin = pin;
        }
        void set_slope(float slope){
            this->config.calibration.slope = slope;
        }
        void set_intercept(float intercept){
            this->config.calibration.intercept = intercept;
        }
        void set_calibration(CALIBRATION calibration){
            this->config.calibration = calibration;
        }
        void set_invalid_data_thresholds(INVALID_DATA thresholds){
            this->config.invalid_data_thresholds = thresholds;
        }
        
        // *** Data Management *** //
        void read() { 
            this->data.timestamp = millis();
            this->data.measurement.value = sensor.read();
            this->data.measurement.is_new = true;
        }
        void clear() {
            this->data.measurement.is_new = false;
        }
        void poll() {
            if (this->state != STATE::ACTIVE) return;            // STATE -> STATE, return
            read();
        }

        // *** Data Retrieval *** //
        const CONFIG& get_config() const { return this->config; }
        const uint8_t& get_pin() const { return this->config.pin; }
        const float& get_slope() const { return this->config.calibration.slope; }
        const float& get_intercept() const { return this->config.calibration.intercept; }
        const CALIBRATION& get_calibration() const { return this->config.calibration; }
        const INVALID_DATA& get_invalid_data_thresholds() const { return this->config.invalid_data_thresholds; }
        const STATE& get_state() const { return this->state; }
        const ERROR& get_error() const { return this->error; }
        const DATA& peek() const { return this->data; }
        const TEMP& get_measurement() {
            this->data.measurement.is_new = false;
            return this->data.measurement;
        }

    private:
        linearDivider sensor;
        STATE state = STATE::UNINITIALIZED;
        ERROR error = ERROR::NO_ERROR;
        CONFIG config{};
        DATA data{};
};
    
}

#endif