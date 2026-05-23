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

#define MPUPARAM_ACCELRANGE_DEFAULT MPU6050_RANGE_2_G      // estimate for low speed vehcile, increase if needed
#define MPUPARAM_GYRORANGE_DEFAULT MPU6050_RANGE_250_DEG   // estimate for low speed vehcile, increase if needed
#define MPUPARAM_BANDWIDTH_DEFAULT MPU6050_BAND_44_HZ      // based on 25 ms relay timeout

namespace mpu_sensor {

struct vector_3 {
    float x;
    float y;
    float z;
};


class mpu_object {
  public:
    mpu_object(uint8_t address = 0x68, uint16_t check_connection_interval = 1000) 
    : address(address), check_interval(check_connection_interval), 
    check_connection_timer(check_interval) {}

    // *** Connection management functions ***
    bool check_connection(){
        // Wire.begin() must be called in the main sketch
        // Basically a ping to see if it's there
        Wire.beginTransmission(this->address);
        // An error code of 0 means the device acknowledged the ping
        return (Wire.endTransmission() == 0); 
    }
    bool begin(){
        // Verify that there is something at the address
        if (check_connection()){
            if (mpu.begin(address)) {
                load_parameters();
                this->connected = true;
                return true;
            }
        }
        return false;
    }
    // Restart connection at a new address
    bool set_address(uint8_t new_address){
        this->address = new_address;
        return begin();
    }

    // *** Parameter management functions ***
    void set_accel_range(mpu6050_accel_range_t range){
        this->accel_range = range; 
    }
    mpu6050_accel_range_t get_accel_range(){
        return this->accel_range;
    }
    void set_gyro_range(mpu6050_gyro_range_t range){
        this->gyro_range = range;
    }
    mpu6050_gyro_range_t get_gyro_range(){
        return this->gyro_range;
    }
    void set_bandwidth(mpu6050_bandwidth_t bandwidth){
        this->bandwidth = bandwidth;
    }    
    mpu6050_bandwidth_t get_bandwidth(){
        return this->bandwidth;
    }
    // Send new parameters to the mpu
    void load_parameters(){
        mpu.setAccelerometerRange(accel_range);         
        mpu.setGyroRange(gyro_range);                 
        mpu.setFilterBandwidth(bandwidth);             
    }
    // Set parameters to default values
    void reset_default_parameters(){
        accel_range = MPUPARAM_ACCELRANGE_DEFAULT;
        gyro_range = MPUPARAM_GYRORANGE_DEFAULT;
        bandwidth = MPUPARAM_BANDWIDTH_DEFAULT;
    }
    
    // *** Reading and control loop functions ***
    bool read(){
        bool is_data = false;
        sensors_event_t a, g, t;     // Data type from MPU library
        mpu.getEvent(&a, &g, &t);
        // Only update each parameter if there are valid readings
        if (!isnan(a.acceleration.x) && !isnan(a.acceleration.y) && !isnan(a.acceleration.z)) {
            mpu_data.acceleration.x = a.acceleration.x;
            mpu_data.acceleration.y = a.acceleration.y;
            mpu_data.acceleration.z = a.acceleration.z;
            accel_updated = true;
            accel_timestamp = millis();
            is_data = true;
        } 
        if (!isnan(g.gyro.x) && !isnan(g.gyro.y) && !isnan(g.gyro.z)) {
            mpu_data.gyro.x = g.gyro.x;
            mpu_data.gyro.y = g.gyro.y;
            mpu_data.gyro.z = g.gyro.z;
            gyro_updated = true;
            gyro_timestamp = millis();
            is_data = true;
        }
        if(!isnan(t.temperature)) {
            mpu_data.temperature = t.temperature;
            temp_updated = true;
            temp_timestamp = millis(); 
            is_data = true;
        }
        return is_data;
    }
    bool update(){
        // Check the connection at specified interval
        if (check_connection_timer.passed()){
            this->connected = check_connection();
            if (!connected) {
                this->connected = begin(); // Try to reconnect if connection is lost
            }
            check_connection_timer.reset();
        }
        // If connected, read the data
        if (connected){
            return read();
        }
    }

    // *** Getters for data, timestamps, and readiness ***
    bool is_new_accel(){
        return accel_updated;
    }
    vector_3 get_accel(){
        vector_3 accel_data;
        accel_data.x = mpu_data.acceleration.x;
        accel_data.y = mpu_data.acceleration.y;
        accel_data.z = mpu_data.acceleration.z;
        accel_updated = false;    
        return accel_data;
    }
    unsigned long get_accel_timestamp(){
        return accel_timestamp;
    }
    
    bool is_new_gyro(){
        return gyro_updated;
    }
    vector_3 get_gyro(){
        vector_3 gyro_data;
        gyro_data.x = mpu_data.gyro.x;
        gyro_data.y = mpu_data.gyro.y;
        gyro_data.z = mpu_data.gyro.z;
        gyro_updated = false;
        return gyro_data;
    }
    unsigned long get_gyro_timestamp(){
        return gyro_timestamp;
    }

    bool is_new_temp(){
        return temp_updated;
    }
    float get_temp(){
        float temp_data = mpu_data.temperature;
        temp_updated = false;
        return temp_data;
    }
    unsigned long get_temp_timestamp(){
        return temp_timestamp;
    }

    // Returns if any one of the categories has been updated
    bool data_updated(){
        return (accel_updated || gyro_updated || temp_updated);
    }
    unsigned long get_timestamp(){
        // Use most recent timestamp
        return max(accel_timestamp, max(gyro_timestamp, temp_timestamp));
    }
    sensors_event_t get_data(){
        // Use most recent timestamp
        sensors_event_t data;
        data.acceleration.x = mpu_data.acceleration.x;
        data.acceleration.y = mpu_data.acceleration.y;
        data.acceleration.z = mpu_data.acceleration.z;
        data.gyro.x = mpu_data.gyro.x;
        data.gyro.y = mpu_data.gyro.y;
        data.gyro.z = mpu_data.gyro.z;
        data.temperature = mpu_data.temperature;
        data.timestamp = get_timestamp();
        accel_updated = false;
        gyro_updated = false;
        temp_updated = false;
        return data;
    }
    unsigned long data_age(){
        return millis() - get_timestamp();
    }

    // *** Maintenance functions ***
    void clear(){
        accel_updated = false;
        gyro_updated = false;
        temp_updated = false;
    }
    void reset(){
        accel_timestamp = 0;
        gyro_timestamp = 0;
        temp_timestamp = 0;
        mpu_data.timestamp = 0;
        mpu_data.acceleration.x = 0;
        mpu_data.acceleration.y = 0;
        mpu_data.acceleration.z = 0;
        mpu_data.gyro.x = 0;
        mpu_data.gyro.y = 0;
        mpu_data.gyro.z = 0;
        mpu_data.temperature = 0;
        clear();
        connected = false;
    }

  private: 
    // MPU params
    Adafruit_MPU6050 mpu;
    uint8_t address = 0x68;
    Timer check_connection_timer;
    uint16_t check_interval = 0;
    bool connected = false; 
    mpu6050_accel_range_t accel_range = MPUPARAM_ACCELRANGE_DEFAULT; 
    mpu6050_gyro_range_t gyro_range = MPUPARAM_GYRORANGE_DEFAULT;
    mpu6050_bandwidth_t bandwidth = MPUPARAM_BANDWIDTH_DEFAULT;
    // Data
    sensors_event_t mpu_data;
    bool accel_updated = false;
    unsigned long accel_timestamp = 0;
    bool gyro_updated = false;
    unsigned long gyro_timestamp = 0;
    bool temp_updated = false;
    unsigned long temp_timestamp = 0;
};   
    
}

#endif
