bool start_mpu(){
    bool return_val = true;
    for(int i = 0; i < number_of_mpu; i++){   // Initialize all pointers to nullptr
    mpu[i] = nullptr;
    }
    for(int i = 0; i < number_of_mpu; i++){
    bool addr_found = false;
    bool initiated = false;
    mpu[i] = new Adafruit_MPU6050();
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if(!addr_found) {
        if (!Address::detect(Address::mpu[i])) {
            error::mpu[i] = 1;          // address not found error
            return_val = false;
        } else {
            addr_found = true;
        }
        } else if (!initiated) {
        if (!mpu[i]->begin()) {
            error::mpu[i] = 2;    // Addr not found error
            return_val = false;
        } else {
            initiated = true;
        }
        } else {
        delay(50);
        mpu[i]->setAccelerometerRange(MPU6050_RANGE_2_G);    // estimate for low speed vehcile, increase if needed
        mpu[i]->setGyroRange(MPU6050_RANGE_250_DEG);         // estimate for low speed vehcile, increase if needed
        mpu[i]->setFilterBandwidth(MPU6050_BAND_44_HZ);         // based on 25 ms relay timeout
        error::mpu[i] = 0;
        break;
        }
    }
    }
    return return_val;
}

void read_mpu(uint8_t index){
    sensors_event_t a, g, temp;
    if (index == 0){
        for (int i = 0; i < number_of_mpu; i++) {
        mpu[i]->getEvent(&a, &g, &temp);
        value::mpu[i].accel.x = a.acceleration.x;
        value::mpu[i].accel.y = a.acceleration.y;
        value::mpu[i].accel.z = a.acceleration.z;
        value::mpu[i].gyro.x = g.gyro.x;
        value::mpu[i].gyro.y = g.gyro.y;
        value::mpu[i].gyro.z = g.gyro.z;
        value::mpu[i].temp = temp.temperature;
        }
    } else if (index <= number_of_mpu) {
        mpu[index - 1]->getEvent(&a, &g, &temp);
        value::mpu[index - 1].accel.x = a.acceleration.x;
        value::mpu[index - 1].accel.y = a.acceleration.y;
        value::mpu[index - 1].accel.z = a.acceleration.z;
        value::mpu[index - 1].gyro.x = g.gyro.x;
        value::mpu[index - 1].gyro.y = g.gyro.y;
        value::mpu[index - 1].gyro.z = g.gyro.z;
        value::mpu[index - 1].temp = temp.temperature;
    }
}

Adafruit_MPU6050* mpu[number_of_mpu];