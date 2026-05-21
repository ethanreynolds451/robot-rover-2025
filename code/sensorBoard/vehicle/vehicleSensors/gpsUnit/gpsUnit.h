// For use with TinyGPSPlus 1.0.7
// Must include in a seperate file

#ifndef GPSUNIT_H
#define GPSUNIT_H

class gpsUnit {
  public:
    // Setup and initialization
    gpsUnit(uint8_t tx_pin = 11, uint8_t rx_pin = 10, unsigned long baudrate = 9600) : baudrate(baudrate){
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
    ~gpsUnit() {
        delete gps_software_serial;
    }
    bool begin(uint8_t timeout = 0){
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
            this->latitude = gps.location.lat();
            this->longitude = gps.location.lng();
            this->latitude_updated = true;
            this->longitude_updated = true;
            this->coordinates_updated = true;
            data_read = true;
        }
        if (gps.altitude.isValid()) {
            this->altitude = gps.altitude.meters();
            this->altitude_updated = true;
            this->coordinates_updated = true;
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
        if (gps.satellites.isValid()){
            this->fix = gps.satellites.value();
            this->fix_updated = true;
            data_read = true;
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
    bool is_new_coordinates(){
        return this->coordinates_updated;
    }
    bool is_new_latitude(){
        return this->latitude_updated;
    }
    float get_latitude(){
        this->coordinates_updated = false;
        this->latitude_updated = false;
        return this->latitude;
    }
    bool is_new_longitude(){
        return this->longitude_updated;
    }
    float get_longitude(){
        this->coordinates_updated = false;
        this->longitude_updated = false;
        return this->longitude;
    }
    bool is_new_altitude(){
        return this->altitude_updated;
    }
    float get_altitude(){
        this->coordinates_updated = false;
        this->altitude_updated = false;
        return this->altitude;
    }
    // Get all three at once using references
    void get_coordinates(float &latitude, float &longitude, float &altitude){
        this->coordinates_updated = false;
        this->latitude_updated = false;
        this->longitude_updated = false;
        this->altitude_updated = false;
        latitude = this->latitude;
        longitude = this->longitude;
        altitude = this->altitude;
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
  private:
    // Initialization parameters
    uint8_t pins[2];
    unsigned long baudrate = 9600;
    // Internal objects
    TinyGPSPlus gps;
    SoftwareSerial* gps_software_serial;                // Software serial object that may or may not be used  
    HardwareSerial* gps_hardware_serial = nullptr;      // This is a pointer to a hardware serial object. Can be dynamically switched for however many hardware ports are available              
    Stream* gps_serial;                                 // This is a pointer to the currently used serial object, whether it be hardware or software serial, that the rest of the code will use to interact with the GPS regardless of the underlying serial type 
    // Internal trackers
    bool waiting_for_data = false; 
    // Data
    float latitude = 0.0;                        // Latitude
    bool latitude_updated = false;                 // Flag to indicate if latitude has been updated since last read
    float longitude = 0.0;                       // Longitude
    bool longitude_updated = false;                // Flag to indicate if longitude has been updated since last read
    float altitude = 0.0;                        // Altitude
    bool altitude_updated = false;                 // Flag to indicate if altitude has been updated since last read
    bool coordinates_updated = false;               // Flag to indicate if either latitude or longitude has been updated since last read, so that they can be read together without worrying about one being updated without the other being updated
    float speed = 0.0;                           // Speed in km/h
    bool speed_updated = false;                    // Flag to indicate if speed has been updated since last read
    float course = 0.0;                          // Course in degrees
    bool course_updated = false;                   // Flag to indicate if course has been updated since last read
    uint8_t fix = 0;                           // Number of satellites in fix
    bool fix_updated = false;                    // Flag to indicate if fix has been updated since last read
};

#endif
