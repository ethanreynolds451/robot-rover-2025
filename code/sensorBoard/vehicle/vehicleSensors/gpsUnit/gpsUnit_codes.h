// Include this to access strings associated with the GPS unit

#ifndef GPS_UNIT_CODES_H
#define GPS_UNIT_CODES_H

#include "gpsUnit_t.h"

namespace gps_unit {

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

void get_error_str(ERROR error, char* buffer, size_t buffer_size = 16){
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(error){
        case ERROR::NO_ERROR:  snprintf(buffer, buffer_size, "NO_ERROR"); break;
        case ERROR::NOT_FOUND: snprintf(buffer, buffer_size, "NOT_FOUND"); break;
        case ERROR::NOT_VALID: snprintf(buffer, buffer_size, "NOT_VALID"); break;
        case ERROR::BUS_FAULT: snprintf(buffer, buffer_size, "BUS_FAULT"); break;
        case ERROR::UNKNOWN:   snprintf(buffer, buffer_size, "UNKNOWN_ERROR"); break;
        default:               snprintf(buffer, buffer_size, "UNDEFINED_ERROR"); break;    
    }
}

}

#endif