bool start_lof(){                                     // Still work in progress
if(pcf_active){
    bool return_val = true;
    for(int i = 0; i < number_of_lof; i++){   // Initialize all pointers to nullptr
    lof[i] = nullptr;
    }
    // Set the I2C addresses of the lof sensors
    for(int i = 0; i < number_of_lof; i++){
    PCF.write(Pin::x_shut[i], LOW);      // Deactivate all lof sensors
    }
    delay(50);                                                       Serial.println("Checkpoint 1");
    for(int i = 0; i < number_of_lof; i++){
    bool addr_found = false;
    bool initiated = false;
    bool addr_set = false;
    lof[i] = new VL53L0X();                   // Create sensor object  // Activate the one to set address
    PCF.write(Pin::x_shut[i], LOW);                                                         Serial.println("Checkpoint 1.1");
    delay(50);
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if (!addr_found) {
        if (!Address::detect(0x29)) {
            error::lof[i] = 1;   // address not found error
                return_val = false;
        } else {
            addr_found = true;
        }                                           Serial.println("Checkpoint 1.1.5");
        } else if (!initiated) {
        if (!lof[i]->init()) {
            return_val = false;
            error::lof[i] = 2;   // failed to initialize error
        } else {
            initiated = true;
        }
        } else if(!addr_set){
        delay(10);
        lof[i]->setAddress(Address::lof[i]);
        delay(10);
        if (!Address::detect(Address::lof[i])) {        // Verify that sensor is active with address
            error::lof[i] = 4;   // unable to communicate error
            return_val = false; // skip to the next sensor
        } else {
            addr_set = true;
        }
        } else {
        PCF.write(Pin::x_shut[i], LOW);   // Deactivate after verifyinig
        error::lof[i] = 0;
        break;    // Move on to the next sensor
        }
    }
    }
    delay(10);                                                    Serial.println("Checkpoint 2");
    for(int i = 0; i < number_of_lof; i++){
    if(lof[i] != nullptr && error::lof[i] == 0){
        lof[i]->startContinuous();
    }
    }
} else {
    return false; 
}
}   // add address verification, retry to set address if didn't work, exit after n times


void read_lof (uint8_t index) {
    if (index == 0){
        for (int i = 0; i < number_of_lof; i++) {
        value::lof[i] = lof[i]->readRangeContinuousMillimeters();
        }
    } else if (index <= number_of_lof) {
        value::lof[index - 1] = lof[index - 1]->readRangeContinuousMillimeters();
    }
}

VL53L0X* lof[number_of_lof];        // Pointer to array of sensor, MUST USE POINTER NOT DOT NOTATION