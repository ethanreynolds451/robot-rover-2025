/*
DEPENDENCIES: 
 - Wire                                       external
 - Adafruit_MPU6050 (modified version)        internal
 - Adafruit_BusIO                             internal
 - Adafruit_Unified_Sensor                    internal
UNITS
 - Acceleration: raw (must convert to m/s^2 using accel range config)
 - Gyro: raw (must convert to rad/s using gyro range config)
 - Temperature: raw (must convert to C using formula from datasheet)
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

    // *** Startup Functions *** //
    void initialize(WIRE start_wire = WIRE::NO_START_WIRE) {
        if (this->state != STATE::UNINITIALIZED) {      
            reset();                                       // STATE -> reset() + UNINITIALIZED            
        }
        if (start_wire == WIRE::START_WIRE){
            Wire.begin();
        }
        this->state = STATE::DISCONNECTED;                  // UNINITIALIZED -> DISCONNECTED
    }   // state transition verified
    void begin(){
        if (this->state != STATE::DISCONNECTED) return;     // STATE -> STATE, return
        Serial.println("Checking connection"); 
        delay(100); 
        check_connection();                                 // DISCONNECTED -> DISCONNECTED/IDENTIFIED
        Serial.println("Setting configuration"); 
        delay(100); 
        // Fatal runtime error happens here
        configure();                                        // IDENTIFIED -> CONFIGURED   
        Serial.println("Checking validity"); 
        delay(100);
        check_validity();                                   // CONFIGURED -> CONFIGURED/READY
        Serial.println("Activating sensor"); 
        delay(100);
        start();                                            // READY -> ACTIVE
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
        sensor.setAccelerometerRange(config.calibration.accel_range);         
        sensor.setGyroRange(config.calibration.gyro_range);                 
        sensor.setFilterBandwidth(config.calibration.bandwidth);    
        this->state = STATE::CONFIGURED;                                   // IDENTIFIED -> CONFIGURED
    }   // state transition verified
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
    }   // state transition verified
    void start(){
        if (this->state != STATE::READY) return;            // STATE -> STATE, return
        sensor.enableSleep(false);
        this->state = STATE::ACTIVE;                        // READY -> ACTIVE
    }   // state transition verified
    void stop() {
        if (this->state != STATE::ACTIVE) return;            // STATE -> STATE, return
        sensor.enableSleep(true);
        this->state = STATE::READY;                         // ACTIVE -> READY
    }   // state transition verified
    void reset(){
        data = DATA{};
        state = STATE::UNINITIALIZED;                       // STATE -> UNINITIALIZED
        error = ERROR::NO_ERROR;                            // ERROR -> NO_ERROR    
    }
    void update() {
        // No hay nada para actualizar
        return; 
    }
    
    
    // *** Configuration *** //
    void set_calibration(CALIBRATION calibration){
        this->config.calibration = calibration;
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

        // Create intermediate DATA variable to hold raw sensor data before validation
        DATA raw_data;

        // Based on custom getter function added to Adafruit_MPU6050 library that retrieves raw values from the internal variables
        sensor.getRawSensorData(&raw_data.accel.value.x, &raw_data.accel.value.y, &raw_data.accel.value.z,
                                    &raw_data.gyro.value.x, &raw_data.gyro.value.y, &raw_data.gyro.value.z,
                                    &raw_data.temp.value);

        // Only update each parameter if there are valid readings
        if ((raw_data.accel.value.x != 0) || (raw_data.accel.value.y != 0) || (raw_data.accel.value.z != 0)) {
            data.accel.value.x = raw_data.accel.value.x;
            data.accel.value.y = raw_data.accel.value.y;
            data.accel.value.z = raw_data.accel.value.z;
            data.accel.is_new = true;
            data.accel.timestamp = millis();
            is_data = true;
        } 
        if ((raw_data.gyro.value.x != 0) || (raw_data.gyro.value.y != 0) || (raw_data.gyro.value.z != 0)) {
            data.gyro.value.x = raw_data.gyro.value.x;
            data.gyro.value.y = raw_data.gyro.value.y;
            data.gyro.value.z = raw_data.gyro.value.z;
            data.gyro.is_new = true;
            data.gyro.timestamp = millis();
            is_data = true;
        }
        if(is_data) {
            data.temp.value = raw_data.temp.value;
            data.temp.is_new = true;
            data.temp.timestamp = millis();
        }
        if (is_data) {
            data.timestamp = millis();
            data.is_new = true;
        }
    }
    void clear() {
        data.is_new = false;
        data.accel.is_new = false;
        data.gyro.is_new = false;
        data.temp.is_new = false;
    }
    void poll() {
        if (this->state != STATE::ACTIVE) return;          // STATE -> STATE, return
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
        this->data.is_new = (this->data.accel.is_new || this->data.gyro.is_new || this->data.temp.is_new); 
        return this->data.accel; 
    }
    const GYRO& get_gyro() { 
        this->data.gyro.is_new = false;
        this->data.is_new = (this->data.accel.is_new || this->data.gyro.is_new || this->data.temp.is_new); 
        return this->data.gyro; 
    }
    const TEMP& get_temperature() {
        this->data.temp.is_new = false;
        this->data.is_new = (this->data.accel.is_new || this->data.gyro.is_new || this->data.temp.is_new); 
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
        data.is_new = false;
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
