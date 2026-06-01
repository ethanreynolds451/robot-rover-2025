#ifndef QMC_SENSOR_CODES_H
#define QMC_SENSOR_CODES_H

namespace qmc_sensor {

// Get the string representation of a state
void get_state_str(const STATE& state, char* buffer, size_t buffer_size = 16) {
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size); 
    switch (state) {
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

// Get the string representation of an error
void get_error_str(const ERROR& error, char* buffer, size_t buffer_size = 16) {
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch (error) {
        case ERROR::NO_ERROR:  snprintf(buffer, buffer_size, "NO_ERROR"); break;
        case ERROR::NOT_FOUND: snprintf(buffer, buffer_size, "NOT_FOUND"); break;
        case ERROR::NOT_VALID: snprintf(buffer, buffer_size, "NOT_VALID"); break;
        case ERROR::UNKNOWN:   snprintf(buffer, buffer_size, "UNKNOWN_ERROR"); break;
        default:               snprintf(buffer, buffer_size, "UNDEFINED_ERROR"); break;
    }
}

}

#endif