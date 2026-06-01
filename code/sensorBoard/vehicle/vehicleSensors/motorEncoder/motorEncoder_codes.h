#ifndef MOTOR_ENCODER_CODES_H
#define MOTOR_ENCODER_CODES_H

#include "motorEncoder_t.h"

namespace motor_encoder {

// Retrieve the string associated with a state code
void get_state_str(STATE state, char* buffer, size_t buffer_size = 16){
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(state){
        case STATE::UNINITIALIZED: snprintf(buffer, buffer_size, "UNINITIALIZED"); break;
        case STATE::DISCONNECTED:  snprintf(buffer, buffer_size, "DISCONNECTED"); break;
        case STATE::IDENTIFIED:    snprintf(buffer, buffer_size, "IDENTIFIED"); break;
        case STATE::CONFIGURED:    snprintf(buffer, buffer_size, "CONFIGURED"); break;
        case STATE::READY:         snprintf(buffer, buffer_size, "READY"); break;
        case STATE::ACTIVE:        snprintf(buffer, buffer_size, "ACTIVE"); break;
        case STATE::FAULT:         snprintf(buffer, buffer_size, "FAULT"); break;
        default:                   snprintf(buffer, buffer_size, "UNDEFINED_STATE"); break;
    }
}

// No errors for motor encoder

}

#endif