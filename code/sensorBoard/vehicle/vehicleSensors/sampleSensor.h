/*
DESCRIPTION:
 - Generic template for a sensor object that complies with the expected interfaces
DEPENDENCIES:
 - external_dependencies.h
UNITS:
 - measurement: unit
*/

#ifndef SAMPLESENSOR_h
#define SAMPLESENSOR_h

#include "specific_dependencies.h"

namespace sample_sensor {

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  FAULT         = 255       // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    UNKNOWN     = 255       // An unknown error has ocurred
};

struct PINS {
    uint8_t pin1 = A0;     
    uint8_t pin2 = A1;
};

struct CALIBRATION {
    int8_t temp = 25;                       
    unsigned int timeout = 1000;       
};

struct CONFIG {
    PINS pins;
    CALIBRATION calibration;
};

struct MEASUREMENT {
    bool is_new = false;
    float value = 0.0;
    unsigned long timestamp = 0;
};

struct DATA {
    unsigned long timestamp = 0;
    MEASUREMENT distance;
};

class sample_object {
    public:
        sample_object(params = defaults)
            : sensor(params) {}

        // *** State Management *** //
        void begin(){
            
        }
        void stop() {

        }
        void start(){
            
        }
        void reset(){
        
        }
        void update() {
           
        }

        // *** Calibration *** //
        void set_calibration(int8_t temp, unsigned int timeout_distance) {
            
        }
        void calibrate() {
            
        }

        // *** Diagnostics *** //
        void check_connection() { 

        }
        void check_validity() {

        }

        // *** Data Management *** //
        void read(){

        }
        void clear() {

        }
        void poll() {
            
        }

        // *** Data Retrieval *** //
        CONFIG get_config() const {
            return this->config;
        }
        PINS get_pins() const {
            return this->config.pins;
        }
        CALIBRATION get_calibration() const {
            return this->config.calibration;
        }
        STATE get_state() const {
            return this->state;
        }
        ERROR get_error() const {
            return this->error;
        }
        const DATA& peek() const { 
            return this->data; 
        }
        const MEASUREMENT& get_measurement() {
            this->data.measurement.is_new = false;
            return this->data.measurement;
        }

    private:
        SensorType sensor;
        CONFIG config;
        ERROR error;
        STATE state;
        DATA data;

        // *** Special Internal Functions *** //

};

}

#endif