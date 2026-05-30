// Include this to access strings associated with the IR sensor

#ifndef IR_SENSOR_CODES_H
#define IR_SENSOR_CODES_H

#include "irSensor_t.h"

namespace ir_sensor {

// Retrieve the string associated with a state code
void get_state_str(STATE state, char* buffer, size_t buffer_size = 16){
    uint8_t state_code = static_cast<uint8_t>(state);
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(state_code){
        case 0:
            strncpy(buffer, "UNINITIALIZED", buffer_size);
            break;
        case 1:
            strncpy(buffer, "DISCONNECTED", buffer_size);
            break;
        case 2:
            strncpy(buffer, "IDENTIFIED", buffer_size);
            break;
        case 3:
            strncpy(buffer, "CONFIGURED", buffer_size);
            break;
        case 4:
            strncpy(buffer, "READY", buffer_size);
            break;
        case 5:
            strncpy(buffer, "ACTIVE", buffer_size);
            break;
        case 255:
            strncpy(buffer, "FAULT", buffer_size);
            break;
        default:
            return; 
    }
}

// No errors for IR sensor

// Retrieve the string associated with an LED code
void get_led_str(uint8_t led_code, char* buffer, size_t buffer_size = 16){
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(led_code){
        case 0:
            strncpy(buffer, "LED_OFF", buffer_size);
            break;
        case 1:
            strncpy(buffer, "LED_ON", buffer_size);
            break;
        default:
            return;
    }
}

}

#endif