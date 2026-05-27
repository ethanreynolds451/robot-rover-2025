/*
DEPENDENCIES:
 - Wire
 - Timer
UNITS:
 - Distance: millimeters
 - Light intensity: device units (not converted to lux, must be processed by onboard computer)
*/

#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H

#include "VL53L0X-1.3.1/VL53L0X.h"
#include "VL53L0X-1.3.1/VL53L0X.cpp"

namespace tof_sensor {



class tof_object {
    public:
        tof_object(uint8_t address = DEFAULT_ADDRESS, uint8_t pin = 2, uint16_t check_connection_interval = 1000) 
        : address(address), pin(pin), check_interval(check_connection_interval) 
        Timer check_connection_timer(check_interval) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);   // Start with the sensor off to avoid bus conflicts during initialization
        }
        void activate(){
            digitalWrite(pin, HIGH);
            this->active = true;
        }
        void deactivate(){
            digitalWrite(pin, LOW);
            this->active = false;
            // Pulling XSHUT low resets the address
            this->address_set = false;   
        }
        bool is_active(){
            return this->active;
        }
        // *** Connection management functions ***
        void set_default_address(uint8_t address){
            this->default_address = address;
        }
        uint8_t get_default_address(){
            return this->default_address;
        }
        // An address is passed into this one because it has to be changed
        bool check_connection(uint8_t address){
            // Wire.begin() must be called in the main sketch
            // Basically a ping to see if it's there
            Wire.beginTransmission(address);
            // An error code of 0 means the device acknowledged the ping
            return (Wire.endTransmission() == 0);
        }
        // This is a lot more complex than the other sensors because the address has to be configured on the sensor 
        bool begin(){
            // First make sure there is no other device using the default address
            if (check_connection(this->default_address)){
                return false;   // Address conflict, cannot initialize
            }
            // Next make sure there is no other sensor using the target address
            if (check_connection(this->address)){
                return false;   // Address conflict, cannot initialize
            }
            // Then activate the sensor 
            activate();
            delay(10);   // Wait for the sensor to power up
            if (!check_connection(this->default_address)){
                deactivate();
                return false;   // Sensor did not respond at default address, cannot initialize
            }
            // Then set the new address and initialize the sensor
            tof.setAddress(this->address);
            if (!tof.init()){
                deactivate();
                return false;   // Failed to initialize sensor
            }
            // Finally verify that the sensor is active with the new address
            if (!check_connection(this->address)){
                deactivate();
                return false;   // Sensor did not respond at new address, initialization failed
            }
            this->address_set = true;
            // Start continuous sensor readings
            tof.startContinuous();
            return true;    // Successfully initialized
        }
        bool set_address(uint8_t new_address){
            this->address = new_address;
            return begin();   // Re-run the initialization process to set the new address
        }
        uint8_t get_address(){
            return this->address;
        }
        bool is_address_set(){
            return this->address_set;
        }

        // *** Read and Control Loop Functions
        bool read(){
            this->distance = tof.readRangeContinuousMillimeters();
            this->light_intensity = tof.readReg16Bit(LIGHT_REGISTER);
            this->data_updated = true;
            this->data_timestamp = millis();
            return true;
        }
        bool update(){
            if (check_connection_timer.passed()){
                if (!address_set){
                    // If the address is not set, try to initialize the sensor
                    if (!begin()){
                        deactivate();  // Failed to initialize, make sure the sensor is deactivated
                        return false;
                    }
                }
                else if (!check_connection(this->address)){
                    deactivate();  // Sensor is no longer responding, deactivate it
                    this->address_set = false;   // Address is reset when sensor is deactivated, so mark it as unset
                    return false;
                }
                check_connection_timer.reset();
            }
            if ((this->active) && (this->address_set)){
                // Only perform the check and reinitialization at specified interval to avoid blocking the control loop
                return read();
            }
            return false;
        }

    private:
        // Sensor parameters
        VL53L0X tof;
        uint8_t address = DEFAULT_ADDRESS;
        uint8_t pin = 0; 
        bool active = false; 
        bool address_set = false; 
        Timer check_connection_timer;
        uint16_t check_interval = 1000;    // Interval for connection checking in milliseconds
        // Data
        uint16_t distance = 0;
        uint16_t light_intensity = 0;
        bool data_updated = false; 
        unsigned long data_timestamp = 0;

};

}


/* 
Funciónes para usar: 
setAddress()
bool init()
void startContinuous(uint32_t period_ms = 0);
void stopContinuous();
uint16_t readRangeContinuousMillimeters();
signal = readReg16Bit(0x20);
light = readReg16Bit(0x22);
      SOFT_RESET_GO2_SOFT_RESET_N                 = 0xBF,
*/