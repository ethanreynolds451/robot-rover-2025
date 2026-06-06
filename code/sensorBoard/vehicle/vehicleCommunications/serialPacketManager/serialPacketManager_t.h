#ifndef SERIAL_PACKET_MANAGER__T_H
#define SERIAL_PACKET_MANAGER__T_H

namespace serial_packet_manager {

enum class PACKET_STATUS {
    CLEAR,
    PARTIAL, 
    FULL, 
    COMPLETE
};

enum class BUFFER_MODE {      
    OVERWRITE_LATEST,
    OVERWRITE_OLDEST,
    DISCARD_NEW
};

// Must match on both sender and reciever devices
enum class VALIDATION_MODE {
    NONE,        
    CONFIRM,    // Confirms recipt of each valid data packet but does not request resends
    ARQ         // Requests resend of missing or corrupted serial packets
};

enum class TRANSPORT_MODE {
    AUTOMATIC,  // Use update() to automatically manage sending and receiving data
    MANUAL      // Manually call send() and read() to manage data transmission and reception
};

struct MODE {
    BUFFER_MODE buffer_mode;
    VALIDATION_MODE validation_mode;
    TRANSPORT_MODE transport_mode;
};

struct CONFIG {
    unsigned long baudrate = 115200;
    uint8_t port = 0;  
    MODE input_mode = {BUFFER_MODE::OVERWRITE_OLDEST, VALIDATION_MODE::NONE, TRANSPORT_MODE::AUTOMATIC}; 
    MODE output_mode = {BUFFER_MODE::OVERWRITE_OLDEST, VALIDATION_MODE::NONE, TRANSPORT_MODE::AUTOMATIC};
};

struct HEADER {
    uint16_t packet_id;     // 4 bytes (hex)
    uint8_t packet_index;   // 2 bytes (hex)
    uint8_t packet_count;   // 2 bytes (hex)
};

struct SERIAL_PACKET {
    unsigned long timestamp;    // internal tracing, not part of the string packet
    bool is_new = false;        // internal tracking, not part of the string packet
    PACKET_STATUS status;       // 1 byte (not part of the string packet)
    HEADER header;              // 8 bytes
    char data[50];              // 50 bytes (variable length data)
    uint8_t checksum;           // 2 bytes (hex)
}; // Reserve 2 bytes for delimiters and 2 bytes for null + newline when string formated

}

#endif