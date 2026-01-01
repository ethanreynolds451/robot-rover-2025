bool start_qmc(){
    bool return_val = true;
    for(int i = 0; i < number_of_qmc; i++){   // Initialize all pointers to nullptr
    qmc[i] = nullptr;
    }
    for(int i = 0; i < number_of_qmc; i++){
    qmc[i] = new QMC5883LCompass();
    bool addr_found = false;
    bool initiated = false;
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if(!addr_found){
        if (!Address::detect(Address::qmc[i])) {
            error::qmc[i] = 1;   // address not found error
            return_val = false;
            continue;  // skip to the next sensor
        } else {
            addr_found = true;
        }
        } else if(!initiated){
        qmc[i]->init();    // void function
        initiated = true;
        } else {
        error::qmc[i] = 0;
        break;
        }
    }
    }
    return return_val;
}

void read_qmc(uint8_t index){
    if (index == 0){
        for (int i = 0; i < number_of_qmc; i++) {
        qmc[i]->read();
        value::qmc_bearing[i] = qmc[i]->getAzimuth();
        value::qmc[i].x = qmc[i]->getX();
        value::qmc[i].y = qmc[i]->getY();
        value::qmc[i].z = qmc[i]->getZ();
        }
    } else if (index <= number_of_qmc) {
        qmc[index - 1]->read();
        value::qmc_bearing[index-1] = qmc[index-1]->getAzimuth();
        value::qmc[index-1].x = qmc[index-1]->getX();
        value::qmc[index-1].y = qmc[index-1]->getY();
        value::qmc[index-1].z = qmc[index-1]->getZ();
    }
}

QMC5883LCompass* qmc[number_of_qmc];