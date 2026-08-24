#ifndef TOF_SENSOR_CODES_H
#define TOF_SENSOR_CODES_H

namespace tof_sensor {

void get_state_str(const STATE& state, char* buffer, size_t buffer_size) {
    if (buffer_size < 16) return; 
    memset(buffer, 0, buffer_size);
    switch (state) {
        case STATE::UNINITIALIZED:
            strncpy(buffer, "UNINITIALIZED", buffer_size);
            break;
        case STATE::DISCONNECTED:
            strncpy(buffer, "DISCONNECTED", buffer_size);
            break;
        case STATE::IDENTIFIED:
            strncpy(buffer, "IDENTIFIED", buffer_size);
            break;
        case STATE::CONFIGURED:
            strncpy(buffer, "CONFIGURED", buffer_size);
            break;
        case STATE::READY:
            strncpy(buffer, "READY", buffer_size);
            break;
        case STATE::ACTIVE:
            strncpy(buffer, "ACTIVE", buffer_size);
            break;
        case STATE::FAULT:
            strncpy(buffer, "FAULT", buffer_size);
            break;
        default:
            strncpy(buffer, "UNKNOWN_STATE", buffer_size);
    }
}

void get_error_str(const ERROR& error, char* buffer, size_t buffer_size) {
    if (buffer_size < 16) return; 
    memset(buffer, 0, buffer_size);
    switch (error) {
        case ERROR::NO_ERROR:
            strncpy(buffer, "NO_ERROR", buffer_size);
            break;
        case ERROR::NOT_FOUND:
            strncpy(buffer, "NOT_FOUND", buffer_size);
            break;
        case ERROR::NOT_VALID:
            strncpy(buffer, "NOT_VALID", buffer_size);
            break;
        case ERROR::UNKNOWN:
            strncpy(buffer, "UNKNOWN_ERROR", buffer_size);
            break;
        default:
            strncpy(buffer, "INVALID_ERROR", buffer_size);
    }
}

}

#endif