// For use with QMC5883LCompass-1.2-3
// Must be included in a seperate file
// Depends on timer.h for connection checking

// Though the QMC has a temperature sensor, this library has no method to interface with it
#ifndef QMCSENSOR_H
#define QMCSENSOR_H

#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.h"
#include "QMC5883LCompass-1.2.3/src/QMC5883LCompass.cpp"

class qmcSensor {
  public:
    qmcSensor(uint8_t address = 0x0D, uint16_t check_connection_interval = 1000) : address(address), check_interval(check_connection_interval), check_connection_timer(check_interval) {}
    // Use a timer to check the connection at a lower frequency than sensor polling
    void set_check_connection_interval(uint16_t interval){
        this->check_interval = interval;
        check_connection_timer = Timer(check_interval);
    }
    bool check_connection(){
        // Wire.begin() must be called in the main sketch
        // Basically a ping to see if it's there
        Wire.beginTransmission(this->address);
        // An error code of 0 means the device acknowledged the ping
        this->connected = (Wire.endTransmission() == 0); 
        return this->connected;
    }
    void set_address(uint8_t address){
        this->address = address;
        qmc.setADDR(address);
        check_connection();    // Check if the new address is valid
    }
    bool is_connected(){
        return this->connected;
    }
    bool begin(){
        qmc.init();
        qmc.setADDR(this->address);
        // Non-blocking connection check 
        return check_connection(); 
    }
    // Data management functions
    bool read(){
        // The QMC has no data ready or validity checks
        // Must be processed by onboard computer
        if (this->connected){
            qmc.read();
            this->direction = qmc.getAzimuth();
            this->mag[0]= qmc.getX();
            this->mag[1] = qmc.getY();
            this->mag[2] = qmc.getZ();
            // This is really just to mirror the archetecture of the other sensors
            this->direction_timestamp = millis();
            this->direction_updated = true;
            this->mag_timestamp = millis();
            this->mag_updated = true;
            return true;    // Successfully read the data
        }
        return false;     // No data to read
    }
    // Main updater function
    bool update(){
        // As long as the sensor is connected, it will always have data to read even if it is just buffered
        if (this->check_connection_timer.passed()){
            this->check_connection_timer.reset();
            check_connection();
        }
        return this->read();
    }
    // Data getters
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
    // Get all three at once using references
    void get_mag(float &x, float &y, float &z){
        this->mag_updated = false;
        x = this->mag[0];
        y = this->mag[1];
        z = this->mag[2];
    }
    // Provide direct readers for each axis
    float get_mag_x(){
        this->mag_updated = false;
        return this->mag[0];
    }
    float get_mag_y(){
        this->mag_updated = false;
        return this->mag[1];
    }
    float get_mag_z(){
        this->mag_updated = false;
        return this->mag[2];
    }
    unsigned long get_mag_timestamp(){
        return this->mag_timestamp;
    }
    // Set read flags to fals without overwriting
    void clear(){
        this->direction_updated = false;
        this->mag_updated = false;
    }
    // Calibration functions
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

  private:
    QMC5883LCompass qmc;
    uint8_t address = 0x0D;
    Timer check_connection_timer;    // Timer to periodically check connection, default 0 for always check
    uint16_t check_interval = 1000;    // Interval for connection checking in milliseconds
    bool connected = false;
    int calibration_offsets[3] = {0, 0, 0}; 
    float calibration_scales[3] = {1.0, 1.0, 1.0};
    float direction = 0;
    bool direction_updated = false;
    unsigned long direction_timestamp = 0;
    float mag[3] = {0, 0, 0};
    bool mag_updated = false;
    unsigned long mag_timestamp = 0;
};

#endif
