bool start_gps(){
    bool return_val = true;
    gps_serial.begin(gps_baudrate);
    // Suggestion from chat GPT, not sure if this will work
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
    unsigned long start = millis();
    while (millis() - start < 1000) {  // Wait for 1 second
        while (gps_serial.available()) {
        gps.encode(gps_serial.read());
        }
    }
    if (gps.charsProcessed() < 10) {
        error::gps = 1;      // Use device not found error
    } else {
        break;
    }
    }
    return return_val;
}


void read_gps(){
    if (gps_serial.available() > 0){
        delay(serial_delay);      // Wait for data to finish coming in
        if (gps.encode(gps_serial.read())){
        if (gps.location.isValid()) {
            value::gps.lat = gps.location.lat();
            value::gps.lng = gps.location.lng();
        }
        if (gps.altitude.isValid()) {
            value::gps.alt = gps.altitude.meters();
        }
        if (gps.course.isValid()){
            value::gps.deg = gps.course.deg();
        }
        if(gps.speed.isValid()){
            value::gps.spd = gps.speed.kmph();
        }
        if (gps.satellites.isValid()){
            value::gps.fix = gps.satellites.value();
        }
        } else {
        error::gps = 3;       // Failed to read data
        }
    }
    // If data not available, nothing to read - add something to keep track of how long it has been since successful read
}

TinyGPSPlus gps;
SoftwareSerial gps_serial;                    // GPS uses software serial to communicate