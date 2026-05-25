/*
DEPENDENCIES: 
 - Wire
 - Adafruit_BusIO
 - Adafruit_Unified_Sensor
 - Timer
UNITS
 - Acceleration: m/s^2
 - Gyro: rad/s
 - Temperature: C
*/

#ifndef MPUSENSOR_h
#define MPUSENSOR_h

#include "Adafruit_MPU6050/Adafruit_MPU6050.h"
#include "Adafruit_MPU6050/Adafruit_MPU6050.cpp"

#include "mpuSensor_t.h"

namespace mpu_sensor {

class mpu_object {
  public:
    mpu_object(uint8_t address = 0x68) {
        this->config.address = address;
    }

    // *** State Management *** //
    void initialize(WIRE start_wire = WIRE::NO_START_WIRE) {
        if (this->state != STATE::FAULT) return; 
        if (this->state != STATE::UNINITIALIZED) {
            stop(); 
        }
        if (start_wire == WIRE::START_WIRE){
            Wire.begin();
        }
        this->state = STATE::DISCONNECTED;
    }
    void begin(){ // ADD PAUSE SPUPPORT
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state != STATE::DISCONNECTED){
            stop();                                         // STATE -> DISCONNECTED
        }
        check_connection();                                 // DISCONNECTED -> DISCONNECTED/IDENTIFIED
        calibrate();                                        // IDENTIFIED -> CONFIGURED   
        start(); 
        check_validity();                                   // CONFIGURED -> CONFIGURED/READY
    }
    void stop() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED, return
        this->state = STATE::IDENTIFIED;                    // STATE -> IDENTIFIED
    }
    void start(){
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) {
            this->state = STATE::DISCONNECTED;              // UNINITIALIZED -> DISCONNECTED
        }
    }
    void reset(){
        stop(); 
        data = DATA{};
        state = STATE::UNINITIALIZED;                       // STATE -> UNINITIALIZED
        error = ERROR::NO_ERROR;                            // ERROR -> NO_ERROR    
    }
    void update() {
        return; 
    }

    // *** Diagnostics *** //
    void check_connection() { 
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        Wire.beginTransmission(this->config.address);
        if (Wire.endTransmission() == 0) {
            if (this->state == STATE::DISCONNECTED) {   
                this->state = STATE::IDENTIFIED;            // DISCONNECTED -> IDENTIFIED
                if (this->error == ERROR::NOT_FOUND) {
                    this->error = ERROR::NO_ERROR;          // NOT_FOUND -> NO_ERROR
                }
            }
        } else {
            this->state = STATE::DISCONNECTED;              // STATE -> DISCONNECTED
            this->error = ERROR::NOT_FOUND;                // ERROR -> NOT_FOUND
        }
    }
    void check_validity() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED, return
        if (this->state == STATE::IDENTIFIED) return;       // IDENTIFIED -> IDENTIFIED, return
        sensors_event_t a, g, t;     // Data type from MPU library
        sensor.getEvent(&a, &g, &t);
        if ((isnan(a.acceleration.x) || isnan(a.acceleration.y) || isnan(a.acceleration.z) ||
            isnan(g.gyro.x) || isnan(g.gyro.y) || isnan(g.gyro.z) ||
            isnan(t.temperature)) || 
            (abs(a.acceleration.x) > config.invalid_data_thresholds.accel_max || abs(a.acceleration.y) > config.invalid_data_thresholds.accel_max || abs(a.acceleration.z) > config.invalid_data_thresholds.accel_max) ||
            (abs(g.gyro.x) > config.invalid_data_thresholds.gyro_max || abs(g.gyro.y) > config.invalid_data_thresholds.gyro_max || abs(g.gyro.z) > config.invalid_data_thresholds.gyro_max) || 
            (t.temperature < config.invalid_data_thresholds.temp_min || t.temperature > config.invalid_data_thresholds.temp_max)) {
            this->state = STATE::CONFIGURED;                // STATE -> CONFIGURED
            this->error = ERROR::NOT_VALID;                 // ERROR -> NOT_VALID
        } else {
            if (this->state == STATE::CONFIGURED) {
                this->state = STATE::READY;                 // CONFIGURED -> READY
                if (this->error == ERROR::NOT_VALID) {
                    this->error = ERROR::NO_ERROR;          // NOT_VALID -> NO_ERROR
                }
            }
        }
    }

    // *** Configuration *** //
    void set_calibration(CALIBRATION calibration){
        this->config.calibration = calibration;
    }
    void calibrate(){
        if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return          
        if (this->state == STATE::DISCONNECTED) return;                    // DISCONNECTED -> DISCONNECTED, return
        sensor.setAccelerometerRange(config.calibration.accel_range);         
        sensor.setGyroRange(config.calibration.gyro_range);                 
        sensor.setFilterBandwidth(config.calibration.bandwidth);    
        if (this->state == STATE::IDENTIFIED){
            this->state = STATE::CONFIGURED;                               // IDENTIFIED -> CONFIGURED
        }
    }
    void set_address(uint8_t new_address){
        if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
        this->config.address = new_address;
        if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return
        this->state = STATE::DISCONNECTED;                                 // STATE -> DISCONNECTED
    }
    void set_invalid_data_thresholds(INVALID_DATA thresholds){
        if (this->state == STATE::FAULT) return;                           // FAULT -> FAULT, return
        this->config.invalid_data_thresholds = thresholds;
        if (this->state == STATE::UNINITIALIZED) return;                   // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;                    // DISCONNECTED ->
        this->state = STATE::IDENTIFIED;                                   // STATE -> CONFIGURED
    }


    // *** Data Management *** //
    void read(){
        bool is_data = false;
        sensors_event_t a, g, t;        // Data type from MPU library
        sensor.getEvent(&a, &g, &t); 
        // Only update each parameter if there are valid readings
        if (!isnan(a.acceleration.x) && !isnan(a.acceleration.y) && !isnan(a.acceleration.z)) {
            data.accel.value.x = a.acceleration.x;
            data.accel.value.y = a.acceleration.y;
            data.accel.value.z = a.acceleration.z;
            data.accel.is_new = true;
            data.accel.timestamp = millis();
            is_data = true;
        } 
        if (!isnan(g.gyro.x) && !isnan(g.gyro.y) && !isnan(g.gyro.z)) {
            data.gyro.value.x = g.gyro.x;
            data.gyro.value.y = g.gyro.y;
            data.gyro.value.z = g.gyro.z;
            data.gyro.is_new = true;
            data.gyro.timestamp = millis();
            is_data = true;
        }
        if(!isnan(t.temperature)) {
            data.temp.value = t.temperature;
            data.temp.is_new = true;
            data.temp.timestamp = millis();
            is_data = true;
        }
        if (is_data) {
            data.timestamp = millis();
        }
    }
    void clear() {
        data.accel.is_new = false;
        data.gyro.is_new = false;
        data.temp.is_new = false;
    }
    void poll() {
        if (this->state != STATE::READY) return;          // READY -> READY, return
        read();
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const uint8_t& get_address() const { return this->config.address; }
    const INVALID_DATA& get_invalid_data_thresholds() const { return this->config.invalid_data_thresholds; }
    const CALIBRATION& get_calibration() const { return this->config.calibration; }
    const STATE& get_state() const { return this->state; }
    const ERROR& get_error() const { return this->error; }
    const DATA& peek() const { return this->data; }
    const ACCEL& get_acceleration() { 
        this->data.accel.is_new = false;
        return this->data.accel; 
    }
    const GYRO& get_gyro() { 
        this->data.gyro.is_new = false;
        return this->data.gyro; 
    }
    const TEMP& get_temperature() {
        this->data.temp.is_new = false;
        return this->data.temp; 
    }
    // Only if access as sensors_event_t is needed, otherwise use above getters for optimal memory management
    // Will be removed by compiler if not used
    sensors_event_t get_data(){
        sensors_event_t sensor_data;
        sensor_data.acceleration.x = data.accel.value.x;
        sensor_data.acceleration.y = data.accel.value.y;
        sensor_data.acceleration.z = data.accel.value.z;
        sensor_data.gyro.x = data.gyro.value.x;
        sensor_data.gyro.y = data.gyro.value.y;
        sensor_data.gyro.z = data.gyro.value.z;
        sensor_data.temperature = data.temp.value;
        sensor_data.timestamp = data.timestamp;
        data.accel.is_new = false;
        data.gyro.is_new = false;
        data.temp.is_new = false;
        return sensor_data;
    }    

  private: 
    Adafruit_MPU6050 sensor;
    STATE state = STATE::UNINITIALIZED; 
    ERROR error= ERROR::NO_ERROR; 
    CONFIG config{}; 
    DATA data{}; 
};   
    
}

#endif