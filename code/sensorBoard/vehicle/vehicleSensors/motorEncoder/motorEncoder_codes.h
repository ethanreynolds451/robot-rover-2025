#ifndef MOTOR_ENCODER_CODES_H
#define MOTOR_ENCODER_CODES_H

#include "motorEncoder_t.h"

namespace motor_encoder {

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
        case 15:
            strncpy(buffer, "FAULT", buffer_size);
            break;
        default:
            return;
    }
}

// No errors for motor encoder

}

#endif