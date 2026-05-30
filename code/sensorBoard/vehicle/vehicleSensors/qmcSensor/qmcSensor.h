/*
DEPENDENCIES:
 - Wire
UNITS:
 - Direction: degrees
 - Magnetic field: device units (not converted to microteslas, must be processed by onboard computer)  
*/

// Though the QMC has a temperature sensor, this library has no method to interface with it
#ifndef QMCSENSOR_H
#define QMCSENSOR_H

#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.h"
#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.cpp"

#include "qmcSensor_t.h"

namespace qmc_sensor {

class qmc_object {
  public:
    qmc_object(uint8_t address = 0x0D) {
        this->config.address = address;
    }

    // *** Startup Functions *** //
    void initialize(WIRE start_wire = WIRE::NO_START_WIRE) {
        if (this->state != STATE::UNINITIALIZED) {
            reset();                                       // STATE -> reset() + UNINITIALIZED         
        }
        if (start_wire == WIRE::START_WIRE){
            Wire.begin();
        }
        sensor.init();
        this->state = STATE::DISCONNECTED;                  // UNINITIALIZED -> DISCONNECTED
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
        sensor.setADDR(this->config.address);
        sensor.setCalibrationOffsets(this->config.calibration.offsets.x, this->config.calibration.offsets.y, this->config.calibration.offsets.z);
        sensor.setCalibrationScales(this->config.calibration.scales.x, this->config.calibration.scales.y, this->config.calibration.scales.z);
        this->state = STATE::CONFIGURED;                                   // IDENTIFIED -> CONFIGURED
    }   // transición de estado verificada
    void check_validity() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED, return
        if (this->state == STATE::IDENTIFIED) return;       // IDENTIFIED -> IDENTIFIED, return
        DATA tmp_data{};
        // Leer datos a tmp_data para verificar su validez sin modificar los datos actuales de la clase
        tmp_data.direction.value = sensor.getAzimuth();
        tmp_data.mag.value.x = sensor.getX();
        tmp_data.mag.value.y = sensor.getY();
        tmp_data.mag.value.z = sensor.getZ();
        if ((abs(tmp_data.mag.value.x) > this->config.invalid_data_thresholds.mag_min) || (abs(tmp_data.mag.value.y) > this->config.invalid_data_thresholds.mag_min) || (abs(tmp_data.mag.value.z) > this->config.invalid_data_thresholds.mag_min) ||
            (abs(tmp_data.mag.value.x) < this->config.invalid_data_thresholds.mag_max) || (abs(tmp_data.mag.value.y) < this->config.invalid_data_thresholds.mag_max) || (abs(tmp_data.mag.value.z) < this->config.invalid_data_thresholds.mag_max) ||
            (tmp_data.direction.value < this->config.invalid_data_thresholds.direction_min) || (tmp_data.direction.value > this->config.invalid_data_thresholds.direction_max)) {
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
        sensor.setMode(0x01,0x0C,0x10,0X00);                // Poner en modo continuo como en la inicialización
        this->state = STATE::READY;                         // PAUSED -> READY
    }   // state transition verified
    void stop() {
        if (this->state != STATE::READY) return;            // STATE -> STATE, return
        sensor.setMode(0x00,0x0C,0x10,0X00);                // Poner en reposo para ahorrar energía
        this->state = STATE::PAUSED;                        // READY -> PAUSED
    }   // transition de estado verificada
    void reset(){
        this->data = DATA{};
        this->state = STATE::UNINITIALIZED;                 // STATE -> UNINITIALIZED
        this->error = ERROR::NO_ERROR;                      // ERROR -> NO_ERROR
    }   // state transition verificada
    void update() {
        // No hay nada para actualizar
        return; 
    }

    // *** Configuración ***
    void set_address(uint8_t address){
        this->config.address = address;
    }
    void set_calibration(CALIBRATION calibration){
        this->config.calibration = calibration;
    }
    void set_calibration_offsets(VECTOR_3 offsets){
        this->config.calibration.offsets = offsets;
    }
    void set_calibration_scales(VECTOR_3 scales){
        this->config.calibration.scales = scales;
    }
    void set_invalid_data_thresholds(INVALID_DATA thresholds){
        this->config.invalid_data_thresholds = thresholds;
    }

    // *** Data Management *** //
    void read(){
        sensor.read();
        // Direction
        this->data.direction.timestamp = millis();
        this->data.direction.value = sensor.getAzimuth();
        this->data.direction.is_new = true;
        // Mag
        this->data.mag.timestamp = millis();
        this->data.mag.value.x = sensor.getX();
        this->data.mag.value.y = sensor.getY();
        this->data.mag.value.z = sensor.getZ();
        this->data.mag.is_new = true;
    }
    void clear(){
        data.mag.is_new = false;
        data.direction.is_new = false;
    }
    void poll() {
        if (this->state != STATE::READY) return;          // READY -> READY, return
        read();
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const uint8_t& get_address() const { return this->config.address; }
    const CALIBRATION& get_calibration() const { return this->config.calibration; }
    const VECTOR_3& get_calibration_offsets() const { return this->config.calibration.offsets; }
    const VECTOR_3& get_calibration_scales() const { return this->config.calibration.scales; }
    const STATE& get_state() const { return this->state; }
    const ERROR& get_error() const { return this->error; }
    const DATA& peek() const { return this->data; }
    const MAG& get_mag() {
        this->data.mag.is_new = false;
        return this->data.mag;
    }
    const DIRECTION& get_direction() {
        this->data.direction.is_new = false;
        return this->data.direction;
    }
    
  private:
    QMC5883LCompass sensor;
    CONFIG config{};
    STATE state = STATE::UNINITIALIZED;
    ERROR error = ERROR::NO_ERROR;
    DATA data{};
};

}

#endif