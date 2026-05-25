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

namespace qmc_sensor {

class qmc_object {
  public:
    qmc_object(uint8_t address = 0x0D) {
        this->address = address;
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
        sensor.init();
        this->state = STATE::DISCONNECTED;
    }
    void begin(){
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state != STATE::DISCONNECTED){
            stop();                                         // STATE -> DISCONNECTED
        }
        check_connection();                                 // DISCONNECTED -> DISCONNECTED/IDENTIFIED
        calibrate();                                        // IDENTIFIED -> CONFIGURED   
        check_validity();                                   // CONFIGURED -> CONFIGURED/READY
    }
    void stop() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT, return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED, return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED, return
        sensor.setMode(0x00);
        if (this->state == STATE::READY){                   
            this->state = STATE::PAUSED;                    // READY -> PAUSED
        }                                                   // STATE -> STATE
    }
    void start(){
        
    }
    void reset(){
    
    }
    void update() {
    
    }




    // *** Connection management functions ***
    void set_check_connection_interval(uint16_t interval){
        this->check_interval = interval;
        check_connection_timer = Timer(check_interval);
    }
    uint16_t get_check_connection_interval(){
        return this->check_interval;
    }
    bool check_connection(){
        // Wire.begin() must be called in the main sketch
        // Basically a ping to see if it's there
        Wire.beginTransmission(this->address);
        // An error code of 0 means the device acknowledged the ping
        return (Wire.endTransmission() == 0); 
    }
    bool is_connected(){
        return this->connected;
    }
    bool begin(){
        qmc.setADDR(this->address);
        qmc.init();
        qmc.setCalibrationOffsets(calibration_offsets[0], calibration_offsets[1], calibration_offsets[2]);
        qmc.setCalibrationScales(calibration_scales[0], calibration_scales[1], calibration_scales[2]);
        // Non-blocking connection check 
        this->connected = check_connection();
        return this->connected;
    }
    bool set_address(uint8_t address){
        this->address = address;
        if (check_connection()){
            return begin();
        }    // Check if the new address is valid
        return false;   // New address is not valid
    }

    // *** Parameter management functions ***
    void set_calibration_offsets(int x, int y, int z){
        this->calibration_offsets[0] = x;
        this->calibration_offsets[1] = y;
        this->calibration_offsets[2] = z;
        qmc.setCalibrationOffsets(x, y, z);
    }
    void get_calibration_offsets(int &x, int &y, int &z){
        x = this->calibration_offsets[0];
        y = this->calibration_offsets[1];
        z = this->calibration_offsets[2];
    }
    void set_calibration_scales(float x, float y, float z){
        this->calibration_scales[0] = x;
        this->calibration_scales[1] = y;
        this->calibration_scales[2] = z;
        qmc.setCalibrationScales(x, y, z);
    }
    void get_calibration_scales(float &x, float &y, float &z){
        x = this->calibration_scales[0];
        y = this->calibration_scales[1];
        z = this->calibration_scales[2];
    }

    // *** Reading and control loop functions ***
    bool read(){
        // The QMC has no data ready or validity checks
        // Must be processed by onboard computer
        qmc.read();
        this->direction = qmc.getAzimuth();
        this->mag.x = qmc.getX();
        this->mag.y = qmc.getY();
        this->mag.z = qmc.getZ();
        // This is really just to mirror the archetecture of the other sensors
        this->direction_timestamp = millis();
        this->mag_timestamp = millis();
        this->direction_updated = true;
        this->mag_updated = true;
        return true;    // Successfully read the data
    }
    // Main updater function
    bool update(){
        // As long as the sensor is connected, it will always have data to read even if it is just buffered
        if (this->check_connection_timer.passed()){
            this->connected = check_connection();
            if (!this->connected){
                this->connected = begin(); // Try to reconnect if connection is lost
            }
            this->check_connection_timer.reset();
        }
        if (this->connected){
            return read();
        }
        return false;
    }

    // *** Data getters ***
    bool is_new_direction(){
        return this->direction_updated;
    }
    float get_direction(){
        this->direction_updated = false;
        return this->direction;
    }
    unsigned long get_direction_timestamp(){
        return this->direction_timestamp;
    }

    bool is_new_mag(){
        return this->mag_updated;
    }
    vector_3 get_mag(){
        this->mag_updated = false;
        return this->mag;
    }
    unsigned long get_mag_timestamp(){
        return this->mag_timestamp;
    }

    // *** Maintenance functions ***
    void clear(){
        this->direction_updated = false;
        this->mag_updated = false;
    }
    
  private:
    QMC5883LCompass qmc;
    CONFIG config{};
    STATUS status = STATUS::UNINITIALIZED;
    ERROR error = ERROR::NO_ERROR;
    DATA data{};
};

}

#endif