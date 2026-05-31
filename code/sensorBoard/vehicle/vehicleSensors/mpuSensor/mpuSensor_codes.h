#ifndef MPU_SENSOR_CODES_H
#define MPU_SENSOR_CODES_H

namespace mpu_sensor {

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

// Retrieve the string associated with an error code
void get_error_str(ERROR error, char* buffer, size_t buffer_size = 16){
    uint8_t error_code = static_cast<uint8_t>(error);
    if (buffer_size < 16) return;
    memset(buffer, 0, buffer_size);
    switch(error_code){
        case 0:
            strncpy(buffer, "NO_ERROR", buffer_size);
            break;
        case 1:
            strncpy(buffer, "NOT_FOUND", buffer_size);
            break;
        case 2:
            strncpy(buffer, "NOT_VALID", buffer_size);
            break;
        case 15:
            strncpy(buffer, "UNKNOWN", buffer_size);
            break;
        default:
            return; 
    }
}

}

#endif