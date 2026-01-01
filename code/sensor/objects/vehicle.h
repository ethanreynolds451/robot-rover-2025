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
            sensor.begin();     // this will call begin on any objects that require this and assign I2C addresses to the lof sensors
            Serial.println("Setup complete"); 
        }
}

#endif
