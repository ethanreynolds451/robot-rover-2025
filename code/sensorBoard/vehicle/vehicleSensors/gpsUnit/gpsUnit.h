/* 
DEPENDENCIES:
 - TinyGPS++
 - SoftwareSerial
TYPES:
 - gps_coordinates: struct containing latitude and longitude as floats
UNITS: 
 - lat / long : degrees, 6 decimal place precision
 - altitude : meters, 2 decimal place precision
 - speed : km/h, 2 decimal place precision
 - course : degrees, 2 decimal place precision
 - GPS time : HHMMSSCC (UTC time in hours, minutes, seconds, and centiseconds)
*/

#ifndef GPS_UNIT_h
#define GPS_UNIT_h

#include "TinyGPS/TinyGPS++.h"

#include "gpsUnit_t.h"

namespace gps_unit {

class gps_object {
  public:
    // Setup and initialization
    gps_object(uint8_t tx_pin = 11, uint8_t rx_pin = 10, unsigned long baudrate = 9600) {
        this->config.pins.tx = tx_pin;
        this->config.pins.rx = rx_pin;
        this->config.baudrate = baudrate;
    }
    ~gps_object() {
        delete gps_software_serial;
    }

    // *** State Management *** //
    void initialize() {
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
        if (this->state != STATE::UNINITIALIZED) reset();   // STATE -> reset() + UNINITIALIZED
        
        // Serial setup
        // To use hardware serial, set tx_pin to 0 and rx_pin to the desired hardware serial port number
        if (config.pins.tx == 0){
            if (config.pins.rx == 0){
                gps_hardware_serial = &Serial;   // Use hardware serial 0
            } 
#if defined(ARDUINO_AVR_MEGA2560)
            else if (config.pins.rx == 1){
                gps_hardware_serial = &Serial1;  // Use hardware serial 1
            } else if (config.pins.rx == 2){
                gps_hardware_serial = &Serial2;  // Use hardware serial 2
            } else if (config.pins.rx == 3){
                gps_hardware_serial = &Serial3;  // Use hardware serial 3
            } 
#endif
            else {
                // Invalid hardware serial port, default to software serial using default pins
                gps_hardware_serial = nullptr;
                this->config.pins.tx = 11;
                this->config.pins.rx = 10;
                delete gps_software_serial;
                gps_software_serial = new SoftwareSerial(this->config.pins.rx, this->config.pins.tx);
            }
        } else {
            // Use software serial with the specified pins
            delete gps_software_serial;
            gps_software_serial = new SoftwareSerial(this->config.pins.rx, this->config.pins.tx);
        }
        if (gps_hardware_serial != nullptr){
            delete gps_software_serial;
            gps_software_serial=nullptr;
            gps_serial = gps_hardware_serial;
            this->config.pins.using_software_serial = false;
        } else {
            gps_serial = gps_software_serial;
            this->config.pins.using_software_serial = true;
        }
        this->state = STATE::DISCONNECTED;            // UNINITIALIZED -> DISCONNECTED
    }   // state transition verified
    void begin(){
        if (this->state != STATE::DISCONNECTED) return;     // STATE -> STATE, return 
        check_connection();         // DISCONNECTED -> IDENTIFIED/DISCONNECTED
        configure();                // IDENTIFIED -> CONFIGURED
        check_validity();           // CONFIGURED -> READY/CONFIGURED
    }   // state transition verified

    // *** State and Lifecycle Management *** //
    void check_connection() { 
        if (this->state == STATE::FAULT) return;           // FAULT -> FAULT + return
        if (this->state == STATE::UNINITIALIZED) return;   // UNINITIALIZED -> UNINITIALIZED + return
        update(); 
        unsigned long now = millis();
        if ((now - this->last_data_time) < this->config.timeout){
            if (this->state == STATE::DISCONNECTED) {
                this->state = STATE::IDENTIFIED;           // DISCONNECTED -> IDENTIFIED
            }                                             
            if (this->error == ERROR::NOT_FOUND) {
                this->error = ERROR::NO_ERROR;              // NOT_FOUND -> NO_ERROR
            }                                             
            return;                                        // STATE -> STATE + return
        }
        this->state = STATE::DISCONNECTED;                 // STATE -> DISCONNECTED  
        this->error = ERROR::NOT_FOUND;                    // ERROR -> NOT_FOUND
    }   // state transition verified
    void configure() {
        // No calibration parameters for GPS
        if (this->state == STATE::FAULT) return;            // FAULT -> FAULT + return
        if (this->state == STATE::UNINITIALIZED) return;    // UNINITIALIZED -> UNINITIALIZED + return
        if (this->state == STATE::DISCONNECTED) return;     // DISCONNECTED -> DISCONNECTED + return
        this->state = STATE::CONFIGURED;                    // STATE -> CONFIGURED
    }   // state transition verified
    void check_validity() {
        if (this->state == STATE::FAULT) return;           // FAULT -> FAULT + return
        if (this->state == STATE::UNINITIALIZED) return;   // UNINITIALIZED -> UNINITIALIZED + return
        if (this->state == STATE::DISCONNECTED) return;    // DISCONNECTED -> DISCONNECTED + return     
        if (this->state == STATE::IDENTIFIED) return;      // IDENTIFIED -> IDENTIFIED + return
        if (((gps.sentencesWithFix() > 0) || 
             (gps.passedChecksum() > 0)) && 
             !(gps.charsProcessed() < 50)) {
                if (this->state == STATE::CONFIGURED) {
                    this->state = STATE::READY;             // CONFIGURED -> READY
                }
                if (this->error == ERROR::NOT_VALID) {
                    this->error = ERROR::NO_ERROR;          // NOT_VALID -> NO_ERROR
                }
                return;                                     // STATE -> STATE + return
             }
        this->state = STATE::IDENTIFIED;                    // STATE -> IDENTIFIED
        this->error = ERROR::NOT_VALID;                     // ERROR -> NOT_VALID
    }   // state transition verified
    void stop(){
        // No pause support yet
        return; 
    }
    void start(){
        return; 
    }
    void reset(){
        if (gps_hardware_serial != nullptr){
            gps_hardware_serial->end();
        } else {
            gps_software_serial->end();
        }                                      
        this->state = STATE::UNINITIALIZED;          // STATE -> UNINITIALIZED
        this->data = DATA();                         // Clear data
        this->error = ERROR::NO_ERROR;               // ERROR -> NO_ERROR
    }   // state transition verified
    void update(){
        if (gps_serial->available()) {
            while (gps_serial->available()) {
                gps.encode(gps_serial->read());
            }
            this->last_data_time = millis();
        }
    }

    // *** Configuration *** //
    void set_calibration() {
        // no caibration parameters yet
        return; 
    }
    void set_pins(uint8_t tx_pin, uint8_t rx_pin){
        this->config.pins.tx = tx_pin;
        this->config.pins.rx = rx_pin;
    }
    void set_baudrate(uint32_t new_baudrate){
        this->config.baudrate = new_baudrate; 
        stop(); 
    }

    // *** Data Management *** //
    void read(){
        bool data_read = false;
        if (gps.location.isValid()) {
            this->data.position.coordinates.timestamp = millis();
            this->data.position.coordinates.latitude = gps.location.lat();
            this->data.position.coordinates.longitude = gps.location.lng();
            this->data.position.coordinates.is_new = true;
            data_read = true;
        }
        if (gps.altitude.isValid()) {
            this->data.position.altitude.timestamp = millis();
            this->data.position.altitude.value = gps.altitude.meters();
            this->data.position.altitude.is_new = true;
            data_read = true;
        }
        if (gps.course.isValid()){
            this->data.velocity.course.timestamp = millis();
            this->data.velocity.course.value = gps.course.deg();
            this->data.velocity.course.is_new = true;
            data_read = true;
        }
        if(gps.speed.isValid()){
            this->data.velocity.speed.timestamp = millis();
            this->data.velocity.speed.value = gps.speed.kmph();
            this->data.velocity.speed.is_new = true;
            data_read = true;
        }
        if (gps.time.isValid()){
            this->data.time.timestamp = millis();
            this->data.time.value = gps.time.value();
            this->data.time.is_new = true;
            data_read = true;
        }
        if (gps.satellites.isValid()){
            this->data.fix.value = gps.satellites.value();
            this->data.fix.is_new = true;
            data_read = true;
        }
        if (data_read) {
            this->data.timestamp = millis();
        }
    }
    void clear(){
        this->data.position.coordinates.is_new = false;
        this->data.position.altitude.is_new = false;
        this->data.velocity.course.is_new = false;
        this->data.velocity.speed.is_new = false;
        this->data.time.is_new = false;
        this->data.fix.is_new = false;
    }
    void poll(){        
        if(this->state == STATE::READY) {
            read();
        }
    }

    // *** Data Retrieval *** //
    const CONFIG& get_config() const { return this->config; }
    const PINS& get_pins() const { return this->config.pins; }
    const STATE& get_state() const { return this->state; }
    const ERROR& get_error() const { return this->error; }
    const DATA& peek() const { return this->data; }
    const COORDINATES& get_coordinates() { 
        this->data.position.coordinates.is_new = false;
        return this->data.position.coordinates;
    }
    const ALTITUDE& get_altitude() { 
        this->data.position.altitude.is_new = false;
        return this->data.position.altitude;
    }
    const SPEED& get_speed() {
        this->data.velocity.speed.is_new = false;
        return this->data.velocity.speed;
    }
    const COURSE& get_course() {
        this->data.velocity.course.is_new = false;
        return this->data.velocity.course;
    }
    const TIME& get_time() {
        this->data.time.is_new = false;
        return this->data.time;
    }
    const FIX& get_fix() {
        this->data.fix.is_new = false;
        return this->data.fix;
    }

  private:
    // Device
    TinyGPSPlus gps;
    CONFIG config;
    STATE state;
    ERROR error;
    SoftwareSerial* gps_software_serial = nullptr;      // Software serial object that may or may not be used  
    HardwareSerial* gps_hardware_serial = nullptr;      // This is a pointer to a hardware serial object. Can be dynamically switched for however many hardware ports are available              
    Stream* gps_serial = nullptr;                       // This is a pointer to the currently used serial object, whether it be hardware or software serial, that the rest of the code will use to interact with the GPS regardless of the underlying serial type 
    // Internal trackers
    unsigned long last_data_time = 0;              // Timestamp of when data was last recieved from the GPS unit, used for connection checking  
    // Data
    DATA data;
};

}

#endif
