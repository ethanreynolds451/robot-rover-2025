#ifndef VEHICLE_h
#define VEHICLE_h

class Vehicle {
    public:
        Vehicle();
        void setup_function(){
            Serial.begin(baudrate);
            Serial.println("Starting setup"); 
            Wire.begin();
            Wire.setTimeout(50); 
            start_pcf(); 
            Serial.println("PCF started"); 
            start_sensors();                        // this will call begin on any objects that require this and assign I2C addresses to the lof sensors
            Serial.println("Setup complete"); 
        }
        void start_sensors() {        // Calls to read will retrieve data from sensor(s) and store it in values array for further access / processing
            Serial.println("Starting sensor setup");
            start_ultrasonic();
            start_steering();
            start_ir(); 
            if (!start_lof() || !start_mpu() || !start_qmc() || !start_gps()){
            Serial.println("There was an error starting one or more sensors; see error log for more details");
            } else {
            Serial.println("All sensors started successfully");
            }
            delay(100);     // Make sure sensors have time before starting to read
        }
}

#endif
