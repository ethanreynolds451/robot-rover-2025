/*
DEPENDENCIES:
 - Wire
 - Timer
UNITS:
 - Distance: millimeters
 - Light intensity: device units (not converted to lux, must be processed by onboard computer)
*/

#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H

#include "VL53L0X-1.3.1/VL53L0X.h"
#include "VL53L0X-1.3.1/VL53L0X.cpp"

#include "tofSensor_t.h"

namespace tof_sensor {

class tof_object {
  public:
    tof_object(uint8_t address = DEFAULT_ADDRESS, uint8_t pin = 2, WIRE start_wire = WIRE::NO_START_WIRE) {
        this->config.address = address;
        this->config.pin = pin;
        this->config.start_wire = start_wire;
        digitalWrite(config.pin, LOW);   // Ensure the sensor is deactivated on startup
    }

    // *** Startup Functions *** //
    void initialize(WIRE start_wire = WIRE::NO_START_WIRE) {
        if (this->state != STATE::UNINITIALIZED) {         
            reset();                                       // STATE -> reset() + UNINITIALIZED         
        }
        if (start_wire == WIRE::START_WIRE){
            Wire.begin();
        }
        // A short blocking function to set the address
        if (this->config.address != DEFAULT_ADDRESS){
            digitalWrite(config.pin, HIGH); 
            delay(10);   // Wait for the sensor to power up
            if (sensor.init()){
                sensor.setAddress(this->config.address);
                this->state = STATE::DISCONNECTED;                  // UNINITIALIZED -> DISCONNECTED
                if (this->error == ERROR::NOT_FOUND) {
                    this->error = ERROR::NO_ERROR;                  // NOT_FOUND -> NO_ERROR
                }
            } else {
                digitalWrite(config.pin, LOW);                      // UNINITIALIZED -> UNINITIALIZED
                this->error = ERROR::NOT_FOUND;                     // ERROR -> NOT_FOUND
                delay(10);   
                // Wait for the sensor to power down, percaution for if sensors are being initialized in series
            }
        }
    }   // state transition verified
    void begin(){
        if (this->state != STATE::DISCONNECTED) return;     // STATE -> STATE, return
        check_connection();                                 // DISCONNECTED -> DISCONNECTED/IDENTIFIED
        configure();                                        // IDENTIFIED -> CONFIGURED   
        check_validity();                                   // CONFIGURED -> CONFIGURED/READY
    }   // state transition verified

    // *** State and Lifecycle Management *** //
    void check_connection() { 
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        Wire.beginTransmission(this->config.address);
        if (Wire.endTransmission() == 0) {
            // Sensor is connected:                         
            if (this->state == STATE::DISCONNECTED) {   
                this->state = STATE::IDENTIFIED;            // DISCONNECTED -> IDENTIFIED
                if (this->error == ERROR::NOT_FOUND) {
                    this->error = ERROR::NO_ERROR;          // NOT_FOUND -> NO_ERROR
                }
            }                                               // STATE -> STATE
        } else {
            // Sensor is not connected:
            this->state = STATE::DISCONNECTED;              // STATE -> DISCONNECTED
            this->error = ERROR::NOT_FOUND;                 // ERROR -> NOT_FOUND
        }
    }   // state transition verified
    void configure(){
        if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return          
        if (this->state == STATE::DISCONNECTED) return;                    // DISCONNECTED -> DISCONNECTED, return
        sensor.startContinuous();                
        this->state = STATE::CONFIGURED;                                   // IDENTIFIED -> CONFIGURED
    }   // transición de estado verificada
    void check_validity() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED, return
        if (this->state == STATE::IDENTIFIED) return;       // IDENTIFIED -> IDENTIFIED, return
        DATA tmp_data{};
        // Leer datos a tmp_data para verificar su validez sin modificar los datos actuales de la clase
        tmp_data.range.value = sensor.readRangeContinuousMillimeters();
        tmp_data.signal_rate.value = sensor.readReg16Bit(SIGNAL_RATE_REGISTER);
        tmp_data.background_rate.value = sensor.readReg16Bit(BACKGROUND_RATE_REGISTER);
        tmp_data.signal_quality.value = sensor.readReg(SIGNAL_QUALITY_REGISTER);
        if ((tmp_data.range.value < this->config.invalid_data_thresholds.distance_min) || (tmp_data.range.value > this->config.invalid_data_thresholds.distance_max) ||
            (tmp_data.background_rate.value < this->config.invalid_data_thresholds.background_rate_min) || (tmp_data.background_rate.value > this->config.invalid_data_thresholds.background_rate_max) ||
            (tmp_data.signal_rate.value < this->config.invalid_data_thresholds.signal_rate_min) || (tmp_data.signal_rate.value > this->config.invalid_data_thresholds.signal_rate_max)) {
            // Sensor is returning invalid data:
            this->state = STATE::CONFIGURED;                // STATE -> CONFIGURED
            this->error = ERROR::NOT_VALID;                 // ERROR -> NOT_VALID
        } else {
            // Sensor is not returning valid data:
            if (this->state == STATE::CONFIGURED) {
                this->state = STATE::READY;                 // CONFIGURED -> READY
            }                                               // STATE -> STATE
            if (this->error == ERROR::NOT_VALID) {
                this->error = ERROR::NO_ERROR;              // NOT_VALID -> NO_ERROR
            }
        }
    }   // transición de estado verificada
    void start(){
        if (this->state != STATE::PAUSED) return;           // STATE -> STATE, return
        sensor.startContinuous();                           // Poner en modo continuo como en la inicialización
        this->state = STATE::READY;                         // PAUSED -> READY
    }   // state transition verified
    void stop() {
        if (this->state != STATE::READY) return;            // STATE -> STATE, return
        sensor.stopContinuous();                            // Poner en reposo para ahorrar energía
        this->state = STATE::PAUSED;                        // READY -> PAUSED
    }   // transition de estado verificada
    void reset(){
        digitalWrite(config.pin, LOW);                      // Deactivating sensor resets the address
        this->data = DATA{};
        this->state = STATE::UNINITIALIZED;                 // STATE -> UNINITIALIZED
        this->error = ERROR::NO_ERROR;                      // ERROR -> NO_ERROR
    }   // state transition verificada
    void update() {
        return; 
    }

    // *** Configuración *** ///
    void set_address(uint8_t address){
        this->config.address = address;
    }
    void set_pin(uint8_t pin){
        this->config.pin = pin;
    }
    void set_invalid_data_thresholds(INVALID_DATA thresholds){
        this->config.invalid_data_thresholds = thresholds;
    }
    void set_start_wire(WIRE start_wire){
        this->config.start_wire = start_wire;
    }

    // *** Data Management *** //
    void read(){
        // No pre-processing or validation as of now, just reading the raw data

        this->data.range.timestamp = millis();
        this->data.range.value = sensor.readRangeContinuousMillimeters();
        this->data.range.is_new = true;

        this->data.signal_rate.timestamp = millis();
        this->data.signal_rate.value = sensor.readReg16Bit(SIGNAL_RATE_REGISTER);
        this->data.signal_rate.is_new = true;

        this->data.background_rate.timestamp = millis();
        this->data.background_rate.value = sensor.readReg16Bit(BACKGROUND_RATE_REGISTER);
        this->data.background_rate.is_new = true;
        
        this->data.signal_quality.timestamp = millis();
        this->data.signal_quality.value = sensor.readReg(SIGNAL_QUALITY_REGISTER);
        this->data.signal_quality.is_new = true;

        this->data.timestamp = millis();
    }
    void clear(){
        data.range.is_new = false;
        data.signal_rate.is_new = false;
        data.background_rate.is_new = false;
        data.signal_quality.is_new = false;
    }
    void poll() {
        if (this->state != STATE::READY) return;          // READY -> READY,
        read();
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const uint8_t& get_address() const { return this->config.address; }
    const uint8_t& get_pin() const { return this->config.pin; }
    const INVALID_DATA& get_invalid_data_thresholds() const { return this->config.invalid_data_thresholds; }
    const WIRE& get_start_wire() const { return this->config.start_wire; }
    const STATE& get_state() const { return this->state; }
    const ERROR& get_error() const { return this->error; }
    const DATA& peek() const { return this->data; }
    const RANGE& get_range() {
        this->data.range.is_new = false;
        return this->data.range;
    }
    const SIGNAL_RATE& get_signal_rate() {
        this->data.signal_rate.is_new = false;
        return this->data.signal_rate;
    }
    const BACKGROUND_RATE& get_background_rate() {
        this->data.background_rate.is_new = false;
        return this->data.background_rate;
    }
    const SIGNAL_QUALITY& get_signal_quality() {
        this->data.signal_quality.is_new = false;
        return this->data.signal_quality;
    }
   
    private:
        // Sensor parameters
        VL53L0X sensor;
        CONFIG config{};
        STATE state = STATE::UNINITIALIZED;
        ERROR error = ERROR::NO_ERROR;
        DATA data{};

};

}

#endif


/* 
Funciónes para usar: 
setAddress()
bool init()
void startContinuous(uint32_t period_ms = 0);
void stopContinuous();
uint16_t readRangeContinuousMillimeters();
signal = readReg16Bit(0x20);
light = readReg16Bit(0x22);
      SOFT_RESET_GO2_SOFT_RESET_N                 = 0xBF,
*/