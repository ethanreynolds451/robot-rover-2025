// Include this to access strings associated with the IR sensor

#ifndef IR_SENSOR_CODES_H
#define IR_SENSOR_CODES_H

#include "irSensor_t.h"

namespace ir_sensor {

// Retrieve the string associated with a state code
void get_state_str(STATE state, char* buffer, size_t buffer_size = 16){
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(state){
        case STATE::UNINITIALIZED: snprintf(buffer, buffer_size, "UNINITIALIZED"); break;
        case STATE::DISCONNECTED:  snprintf(buffer, buffer_size, "DISCONNECTED"); break
        case STATE::IDENTIFIED:    snprintf(buffer, buffer_size, "IDENTIFIED"); break;
        case STATE::CONFIGURED:    snprintf(buffer, buffer_size, "CONFIGURED"); break
        case STATE::READY:         snprintf(buffer, buffer_size, "READY"); break;
        case STATE::ACTIVE:        snprintf(buffer, buffer_size, "ACTIVE"); break;
        case STATE::FAULT:         snprintf(buffer, buffer_size, "FAULT"); break;
        default:                   snprintf(buffer, buffer_size, "UNDEFINED_STATE"); break;
    }
}

// No errors for IR sensor

// Retrieve the string associated with an LED code
void get_led_str(LED led_state, char* buffer, size_t buffer_size = 16){
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(led_state){  
        case LED::LED_OFF: snprintf(buffer, buffer_size, "LED_OFF"); break;
        case LED::LED_ON:  snprintf(buffer, buffer_size, "LED_ON"); break;
        default:           snprintf(buffer, buffer_size, "UNDEFINED_LED"); break;
    }
}

}

#endif