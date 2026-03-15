#ifndef MPUSENSOR_h
#define MPUSENSOR_h

#define MPUPARAM_ACCELRANGE_DEFAULT MPU6050_RANGE_2_G      // estimate for low speed vehcile, increase if needed
#define MPUPARAM_GYRORANGE_DEFAULT MPU6050_RANGE_250_DEG   // estimate for low speed vehcile, increase if needed
#define MPUPARAM_BANDWIDTH_DEFAULT MPU6050_BAND_44_HZ      // based on 25 ms relay timeout

// Depends on Adafruit_MPU6050 2.2.6 and its dependencies

class mpuSensor {
  public:
    mpuSensor(uint8_t address = 0x68) : address(address) {}
    // This is a blocking function; no non-blocking version implemented, so be careful when using in main loop
    bool begin(uint8_t retry = 0){
        for(uint8_t i = 0; i <= retry; i++) {
            if(!mpu.testConnection()){
                mpu.begin(this->address);
            } else {
                // If the device is properly initialized, set the default parameters
                delay(50);      // Need to delay after initializing to ensure integrity
                load_parameters(); 
                return true; 
            }
        }
        return false; 
    }
    bool connected(){
        return mpu.testConnection();
    }
    // Setters for internal parameters
    void set_accel_range(uint8_t range){
        this->accel_range = range; 
    }
    void set_gyro_range(uint8_t range){
        this->gyro_range = range;
    }
    void set_bandwidth(uint8_t bandwidth){
        this->bandwidth = bandwidth;
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
    
    // Reading and data retrieval functions
    void update(){
        sensors_event_t a, g, temp;     // Data type from MPU library
        mpu.getEvent(&a, &g, &temp);
        // Only update each parameter if there are valid readings
        // No error handling because timestamp can be used to tell if readings have stopped
        if (!isnan(a.acceleration.x) && !isnan(a.acceleration.y) && !isnan(a.acceleration.z)) {
            accel_x = a.acceleration.x;
            accel_y = a.acceleration.y;
            accel_z = a.acceleration.z;
            accel_updated = true;
            accel_timestamp = a.timestamp;
        } 
        if (!isnan(g.gyro.x) && !isnan(g.gyro.y) && !isnan(g.gyro.z)) {
            gyro_x = g.gyro.x;
            gyro_y = g.gyro.y;
            gyro_z = g.gyro.z;
            gyro_updated = true;
            gyro_timestamp = g.timestamp;
        }
        if(!isnan(temp.temperature)) {
            temp = temp.temperature;
            temp_updated = true;
            temp_timestamp = temp.timestamp;
        }
    }
    // getters for data
    bool is_new_accel(){
        return accel_updated;
    }
    sensor_events_t get_accel(){
        sensor_events_t accel_data;
        accel_data.acceleration.x = accel_x;
        accel_data.acceleration.y = accel_y;
        accel_data.acceleration.z = accel_z;
        accel_updated = false;    
        return accel_data;
    }
    unsigned long get_accel_timestamp(){
        return accel_timestamp;
    }
    bool is_new_gyro(){
        return gyro_updated;
    }
    sensor_events_t get_gyro(){
        sensor_events_t gyro_data;
        gyro_data.gyro.x = gyro_x;
        gyro_data.gyro.y = gyro_y;
        gyro_data.gyro.z = gyro_z;
        gyro_updated = false;
        return gyro_data;
    }
    unsigned long get_gyro_timestamp(){
        return gyro_timestamp;
    }
    bool is_new_temp(){
        return temp_updated;
    }
    sensor_events_t get_temp(){
        sensor_events_t temp_data;
        temp_data.temperature = temp;
        temp_updated = false;
        return temp_data;
    }
    unsigned long get_temp_timestamp(){
        return temp_timestamp;
    }
    // Returns if any one of the categories has been updated
    bool data_updated(){
        return accel_updated || gyro_updated || temp_updated;
    }
    sensot_events_t get_data(){
        sensor_events_t data;
        data.acceleration.x = accel_x;
        data.acceleration.y = accel_y;
        data.acceleration.z = accel_z;
        data.gyro.x = gyro_x;
        data.gyro.y = gyro_y;
        data.gyro.z = gyro_z;
        data.temperature = temp;
        accel_updated = false;
        gyro_updated = false;
        temp_updated = false;
        return data;
    }
    // No timestamp for all data because may be taken at different times

  private: 
    Adafruit_MPU6050 mpu;

    uint8_t address;
    uint8_t accel_range = MPUPARAM_ACCELRANGE_DEFAULT; 
    uint8_t gyro_range = MPUPARAM_GYRORANGE_DEFAULT;
    uint8_t bandwidth = MPUPARAM_BANDWIDTH_DEFAULT;

    float accel_x; 
    float accel_y;
    float accel_z;
    bool accel_updated = false;
    unsigned long accel_timestamp;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    bool gyro_updated = false;
    unsigned long gyro_timestamp;
    float temp;
    bool temp_updated = false;
    unsigned long temp_timestamp;
}   



#endif