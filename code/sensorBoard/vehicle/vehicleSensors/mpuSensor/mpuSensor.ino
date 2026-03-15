#include "Adafruit_BusIO-1.17.0/Adafruit_BusIO_Register.h"
#include "Adafruit_Unified_Sensor-1.1.9/Adafruit_Sensor.h"
#include "Adafruit_MPU6050-1.0.7/Adafruit_MPU6050.h"

#include "mpuSensor.h"

mpuSensor testMPU();        // At default address

void setup(){
    Serial.begin(9600); 
    if(testMPU.begin(3)) {
        Serial.println("MPU6050 initialized successfully");
    } else {
        Serial.println("Failed to initialize MPU6050 after 3 attempts");
    }
}


void loop(){
    testMPU.update();
    if(testMPU.is_new_accel()){
        sensor_events_t accel = testMPU.get_accel();
        Serial.print("Accel: ");
        Serial.print(accel.acceleration.x);
        Serial.print(", ");
        Serial.print(accel.acceleration.y);
        Serial.print(", ");
        Serial.println(accel.acceleration.z);
        Serial.print("At time: ");
        Serial.println(testMPU.get_accel_timestamp());
    }
    if(testMPU.is_new_gyro()){
        sensor_events_t gyro = testMPU.get_gyro();
        Serial.print("Gyro: ");
        Serial.print(gyro.gyro.x);
        Serial.print(", ");
        Serial.print(gyro.gyro.y);
        Serial.print(", ");
        Serial.println(gyro.gyro.z);
        Serial.print("At time: ");
        Serial.println(testMPU.get_gyro_timestamp());
    }
    if(testMPU.is_new_temp()){
        sensor_events_t temp = testMPU.get_temp();
        Serial.print("Temp: ");
        Serial.print(temp.temperature);
        Serial.print("C at time: ");
        Serial.println(testMPU.get_temp_timestamp());
    }
}
