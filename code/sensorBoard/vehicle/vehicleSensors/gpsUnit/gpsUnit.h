/* 
DEPENDENCIES:
 - <SoftwareSerial.h>
TYPES:
 - gps_coordinates: struct containing latitude and longitude as floats
UNITS: 
 - lat / long : degrees, 6 decimal place precision
 - altitude : meters, 2 decimal place precision
 - speed : km/h, 2 decimal place precision
 - course : degrees, 2 decimal place precision
 - GPS time : HHMMSSCC (UTC time in hours, minutes, seconds, and centiseconds)
*/

#ifndef GPSUNIT_H
#define GPSUNIT_H

#include "TinyGPS/TinyGPS++.h"
#include "TinyGPS/TinyGPS++.cpp"

namespace gps_unit {

// *** State and error enums *** //

enum class STATE : uint8_t {
  UNINITIALIZED = 0,        // never probed yet
  DISCONNECTED  = 1,        // probe failed / not present
  IDENTIFIED    = 2,        // present + ID verified
  CONFIGURED    = 3,        // init/config applied
  READY         = 4,        // producing valid readings
  FAULT         = 255,        // persistent/latched failure
};

enum class ERROR : uint8_t {
    NO_ERROR    = 0,        // No error, sensor is functioning properly
    NOT_FOUND   = 1,        // The sensor was not found durring initialization
    NOT_VALID   = 2,        // The sensor is not returing valid data
    BUS_FAULT   = 3,        // There is a problem with the communication bus (software serial or hardware serial)
    UNKNOWN     = 255       // An unknown error has ocurred
};

// *** Config and parameter structs *** //

struct PINS {
    uint8_t tx = 0;     
    uint8_t rx = 1;
};

struct CONFIG {
    PINS pins;
    unsigned long baudrate = 9600;
};

// *** Data structs *** //

struct COORDINATES {
    bool is_new = false;
    float lat;
    float long;
    unsigned long timestamp;
};

struct ALTITUDE {
    bool is_new = false;
    float value;
    unsigned long timestamp;
};

struct POSITION {
    COORDINATES coordinates;
    ALTITUDE altitude;
};

struct SPEED {
    bool is_new = false;
    float value;
    unsigned long timestamp;
}; 

struct COURSE {
    bool is_new = false;
    float value;
    unsigned long timestamp;
};

struct VELOCITY {
    SPEED speed;
    COURSE course;
};

struct TIME {
    bool is_new = false;
    unsigned long value;  
    unsigned long timestamp;
};

struct FIX {
    bool is_new = false;
    uint8_t value;  
    unsigned long timestamp;
};

struct DATA {
    unsigned long timestamp;        // Packet timestamp
    POSITION position;              // Data describing position
    VELOCITY velocity;              // Data describing velocity
    TIME time;                      // GPS time
    FIX fix;                        // GPS fix quality
};

class gps_object {
  public:
    // Setup and initialization
    gps_object(uint8_t tx_pin = 11, uint8_t rx_pin = 10, unsigned long baudrate = 9600) 
    : baudrate(baudrate){
        pins[0] = tx_pin;
        pins[1] = rx_pin;
        // To use hardware serial, set tx_pin to 0 and rx_pin to the desired hardware serial port number
        if (tx_pin == 0){
            if (rx_pin == 0){
                gps_hardware_serial = &Serial;   // Use hardware serial 0
            } else if (rx_pin == 1){
                gps_hardware_serial = &Serial1;  // Use hardware serial 1
            } else if (rx_pin == 2){
                gps_hardware_serial = &Serial2;  // Use hardware serial 2
            } else if (rx_pin == 3){
                gps_hardware_serial = &Serial3;  // Use hardware serial 3
            } else {
                // Invalid hardware serial port, default to software serial using default pins
                gps_hardware_serial = nullptr;
                this->pins[0] = 11;
                this->pins[1] = 10;
                delete gps_software_serial;
                gps_software_serial = new SoftwareSerial(this->pins[1], this->pins[0]);
            }
        } else {
            // Use software serial with the specified pins
            delete gps_software_serial;
            gps_software_serial = new SoftwareSerial(this->pins[1], this->pins[0]);
        }
        if (gps_hardware_serial != nullptr){
            gps_serial = gps_hardware_serial;
        } else {
            gps_serial = gps_software_serial;
        }
    }
    ~gps_object() {
        delete gps_software_serial;
    }
    bool begin(uint16_t timeout = 0){
        if (gps_hardware_serial != nullptr){
            gps_hardware_serial->begin(this->baudrate); 
        } else {
            gps_software_serial->begin(this->baudrate);
        }
        if (timeout > 0){
            // Attempt to read data from the GPS until the timeout to see if it is connected
            unsigned long start = millis();
            while (millis() - start < timeout) {
                while (gps_serial->available()) {
                    gps.encode(gps_serial->read());
                }
                if (gps.charsProcessed() > 10) {
                    return true;
                }
                return false;
            }  
        } else {
            return true;   // No timeout to check if connected, just start the GPS
        }
    }
    int available(){
        return gps_serial->available();
    }
    // Data interface functions
    bool read(){
        bool data_read = false; 
        // Use the validity functions of the library
        if (gps.location.isValid()) {
            this->coordinates.latitude = gps.location.lat();
            this->coordinates.longitude = gps.location.lng();
            this->coordinates_updated = true;
            data_read = true;
        }
        if (gps.altitude.isValid()) {
            this->altitude = gps.altitude.meters();
            this->altitude_updated = true;
            data_read = true;
        }
        if (gps.course.isValid()){
            this->course = gps.course.deg();
            this->course_updated = true;
            data_read = true;
        }
        if(gps.speed.isValid()){
            this->speed = gps.speed.kmph();
            this->speed_updated = true;
            data_read = true;
        }
        if (gps.time.isValid()){
            this->gps_time = gps.time.value();
            this->gps_time_updated = true;
            data_read = true;
        }
        if (gps.satellites.isValid()){
            this->fix = gps.satellites.value();
            this->fix_updated = true;
            data_read = true;
        }
        if (data_read) {
            this->timestamp = millis();
        }
        return data_read;       
    }
    // Main updater function
    bool update(){
        bool data_ready = false;
        // This uses the GPS unit's return flag to determine if new data is ready
        while (gps_serial->available()) {
            data_ready = ((gps.encode(gps_serial->read())) || data_ready);
        }
        if(data_ready){
            return this->read();
        }
        return false;     // No new data was ready
    }
    // Data getters
    unsigned long get_timestamp(){
        return this->timestamp;
    }
    unsigned long data_age(){
        return millis() - this->timestamp;
    }
    bool is_new_coordinates(){
        return this->coordinates_updated;
    }
    gps_coordinates get_coordinates(){
        this->coordinates_updated = false;
        return this->coordinates;
    }
    bool is_new_altitude(){
        return this->altitude_updated;
    }
    float get_altitude(){
        this->altitude_updated = false;
        return this->altitude;
    }
    bool is_new_speed(){
        return this->speed_updated;
    }
    float get_speed(){
        this->speed_updated = false;
        return this->speed;
    }
    bool is_new_course(){
        return this->course_updated;
    }
    float get_course(){
        this->course_updated = false;
        return this->course;
    }
    bool is_new_time(){
        // This is in GPS encoded time, NOT milliseconds
        return this->gps_time_updated;
    }
    unsigned long get_time(){
        this->gps_time_updated = false;
        return this->gps_time;
    }
    bool is_new_fix(){
        return this->fix_updated;
    }
    uint8_t get_fix(){
        this->fix_updated = false;
        return this->fix;
    }
    // Serial setters and getters
    void set_baudrate(uint32_t new_baudrate){
        this->baudrate = new_baudrate; 
        if (gps_hardware_serial != nullptr){
            gps_serial = gps_hardware_serial;
        } else {
            gps_serial = gps_software_serial;
        }
    }
    uint32_t get_baudrate(){
        return this->baudrate;
    }
    void set_pins(uint8_t tx_pin, uint8_t rx_pin){
        this->pins[0] = tx_pin;
        this->pins[1] = rx_pin;
            if (tx_pin == 0){
                if (rx_pin == 0){
                    gps_hardware_serial = &Serial;   // Use hardware serial 0
                } else if (rx_pin == 1){
                    gps_hardware_serial = &Serial1;  // Use hardware serial 1
                } else if (rx_pin == 2){
                    gps_hardware_serial = &Serial2;  // Use hardware serial 2
                } else if (rx_pin == 3){
                    gps_hardware_serial = &Serial3;  // Use hardware serial 3
                } else {
                    // Invalid hardware serial port, default to software serial using default pins
                    gps_hardware_serial = nullptr;
                    this->pins[0] = 11;
                    this->pins[1] = 10;
                    delete gps_software_serial;
                    gps_software_serial = new SoftwareSerial(this->pins[1], this->pins[0]);
                }
            } else {
                // Use software serial with the specified pins
                delete gps_software_serial;
                gps_software_serial = new SoftwareSerial(this->pins[1], this->pins[0]);    
            }
        if (gps_hardware_serial != nullptr){
            gps_hardware_serial->begin(this->baudrate); 
            gps_serial = gps_hardware_serial;
        } else {
            gps_software_serial->begin(this->baudrate);
            gps_serial = gps_software_serial;
        }
    }
    void get_pins(uint8_t &tx_pin, uint8_t &rx_pin){
        tx_pin = this->pins[0];
        rx_pin = this->pins[1];
    }
    void clear(){
        this->coordinates_updated = false;
        this->altitude_updated = false;
        this->speed_updated = false;
        this->course_updated = false;
        this->gps_time_updated = false;
        this->fix_updated = false;
    }
    void reset(uint16_t timeout = 0){
        if (gps_hardware_serial != nullptr){
            gps_hardware_serial->end(); 
        } else {
            gps_software_serial->end();
        }
        this->timestamp = 0;
        this->coordinates = {0.0, 0.0};
        this->altitude = 0.0;
        this->speed = 0.0;
        this->course = 0.0;
        this->gps_time = 0;
        this->fix = 0;
        clear();
    }
  private:
    // Device
    TinyGPSPlus gps;
    CONFIG config;
    SoftwareSerial* gps_software_serial;                // Software serial object that may or may not be used  
    HardwareSerial* gps_hardware_serial = nullptr;      // This is a pointer to a hardware serial object. Can be dynamically switched for however many hardware ports are available              
    Stream* gps_serial;                                 // This is a pointer to the currently used serial object, whether it be hardware or software serial, that the rest of the code will use to interact with the GPS regardless of the underlying serial type 
    // Internal trackers (what is this for?)
    bool waiting_for_data = false; 
    // Data
    unsigned long timestamp = 0;              // Timestamp in milliseconds of when the data was read from the GPS unit, used for timestamping the data and calculating offsets
    gps_coordinates coordinates{0.0, 0.0};
    bool coordinates_updated = false;               // Flag to indicate if either latitude or longitude has been updated since last read, so that they can be read together without worrying about one being updated without the other being updated
    float altitude = 0.0;                           // Altitude in meters
    bool altitude_updated = false;                 // Flag to indicate if altitude has been updated since last read
    float speed = 0.0;                           // Speed in km/h
    bool speed_updated = false;                    // Flag to indicate if speed has been updated since last read
    float course = 0.0;                          // Course in degrees
    bool course_updated = false;                   // Flag to indicate if course has been updated since last read
    unsigned long gps_time = 0;                          // GPS time in milliseconds since midnight (UTC)
    bool gps_time_updated = false;                    // Flag to indicate if GPS time has been updated
    uint8_t fix = 0;                           // Number of satellites in fix
    bool fix_updated = false;                    // Flag to indicate if fix has been updated since last read
};

}

#endif
