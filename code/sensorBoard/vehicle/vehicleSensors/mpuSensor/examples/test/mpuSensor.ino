// Test sketch for MPU Sensor class

#include "mpuSensor.h"

#include "mpuSensor_codes.h"

uint8_t ADDRESS = 0x68; 
unsigned long BAUDRATE = 115200;
unsigned long I2C_DELAY = 100; 
unsigned long LOOP_DELAY = 500;
unsigned long STARTUP_DELAY = 5000;

using mpuSensor = mpu_sensor::mpu_object;

mpuSensor mpu(ADDRESS); 

char stateString[16];  

void setup() {
  Serial.begin(BAUDRATE); 
  Serial.println("Serial communication started");
  Serial.println("Initializing MPU Sensor...");
  mpu.initialize(mpu_sensor::WIRE::START_WIRE);
  mpu_sensor::get_state_str(mpu.get_state(), stateString, sizeof(stateString));
  Serial.println("MPU initialization completed"); 
  Serial.println("MPU state: " + String(stateString));
  Serial.println("Waiting for I2C communication to stabilize...");
  delay(I2C_DELAY); 
  Serial.println("Starting MPU Sensor...");
  mpu.begin();
  Serial.println("MPU Sensor started");
  mpu_sensor::get_state_str(mpu.get_state(), stateString, sizeof(stateString)); 
  Serial.println("MPU state: " + String(stateString));    
  Serial.println("Setup complete, entering main loop in " + String(STARTUP_DELAY) + " ms...");
}

void loop() {

  mpu_sensor::get_state_str(mpu.get_state(), stateString, sizeof(stateString));
  Serial.println("Current MPU state: " + String(stateString));


  Serial.println("Polling MPU Sensor...");
  mpu.poll();

  if (mpu.peek().is_new){
    Serial.println("New data available from MPU Sensor:");
    // Print new snsor data
    if(mpu.peek().accel.is_new){
        Serial.print("  Acceleration: x=");
        Serial.print(mpu.get_acceleration().value.x);
        Serial.print(", y=");
        Serial.print(mpu.get_acceleration().value.y);
        Serial.print(", z=");
        Serial.println(mpu.get_acceleration().value.z);
    }
    if(mpu.peek().gyro.is_new){
        Serial.print("  Gyroscope: x=");
        Serial.print(mpu.get_gyro().value.x);
        Serial.print(", y=");
        Serial.print(mpu.get_gyro().value.y);
        Serial.print(", z=");
        Serial.println(mpu.get_gyro().value.z);
    }
    if(mpu.peek().temp.is_new){
        Serial.print("  Temperature: ");
        Serial.println(mpu.get_temperature().value);
    }

    // Clear the data 
    mpu.clear();
  }

}
