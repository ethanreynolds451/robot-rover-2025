#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H

#include "../../libraries/arduino/Arduino.h"
#include "sampleTestConfig.h"

namespace sampleTest {

    void initialize(){
        Serial.begin(params::baud_rate);
    }

    void run(){
        while(true){
            Serial.println("Hello World");
            delay(1000);
        }
    }

}

#endif