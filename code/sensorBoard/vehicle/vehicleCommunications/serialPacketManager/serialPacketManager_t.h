#ifndef SERIAL_PACKET_MANAGER__T_H
#define SERIAL_PACKET_MANAGER__T_H

namespace serial_packet_manager {

using packetid_t = uint16_t;
using packetindex_t = uint8_t;

constexpr packetid_t INVALID_PACKET_ID = UINT16_MAX; 

constexpr size_t ARDUINO_SERIAL_BUFFER_SIZE = 64; 
constexpr size_t PACKET_DATA_SIZE = 50; 

// Prevent multiplication overflow
static_assert(ARDUINO_SERIAL_BUFFER_SIZE == 0 || 
                PACKET_DATA_SIZE == 0 ||
                (ARDUINO_SERIAL_BUFFER_SIZE < (SIZE_MAX/PACKET_DATA_SIZE)), 
                "ARDUINO_SERIAL_BUFFER_SIZE and PACKET_DATA_SIZE must be greater than 0 and their product must not exceed SIZE_MAX to prevent overflow");

enum class PACKET_STATUS {
    CLEAR,
    PARTIAL, 
    FULL, 
    COMPLETE, 
    INVALID
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

enum class STATE {
    UNINITIALIZED,
    INITIALIZED,
    ACTIVE,
    STOPPED
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
    // Must update if packetid_t type changes
    packetid_t packet_id;           // 4 bytes (hex encoded)size
    packetindex_t packet_index;     // 2 bytes (hex encoded)
    packetindex_t packet_count;     // 2 bytes (hex encoded)
};

struct SERIAL_PACKET {
    // Internal metadata
    unsigned long timestamp;     
    bool is_new = false;           
    PACKET_STATUS status;          
    // String formated packet structure
    HEADER header;                  // 8 bytes
    char data[PACKET_DATA_SIZE];    // 50 bytes (variable length data)
    uint8_t checksum;               // 2 bytes (hex)
}; // Reserve 2 bytes for delimiters and 2 bytes for null + newline when string formated


struct INPUT {
    packetid_t buffer_size = PACKET_MANAGER_INBOUND_BUFFER_SIZE;
    char serial_buffer[ARDUINO_SERIAL_BUFFER_SIZE];
    SERIAL_PACKET packets[PACKET_MANAGER_INBOUND_BUFFER_SIZE];
    const char* data[PACKET_MANAGER_INBOUND_BUFFER_SIZE] = {nullptr};  
    packetid_t ids[PACKET_MANAGER_INBOUND_BUFFER_SIZE] = {INVALID_PACKET_ID};
}; 

struct OUTPUT {
    packetid_t buffer_size = PACKET_MANAGER_OUTBOUND_BUFFER_SIZE;
    char serial_buffer[ARDUINO_SERIAL_BUFFER_SIZE];
    SERIAL_PACKET packets[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE];
    const char* data[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE] = {nullptr};
    packetid_t ids[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE] = {INVALID_PACKET_ID};
};

struct DATA_PACKET {
    packetindex_t packet_start;     // Inclusive start index in the serial packet buffer for this data packet
    packetindex_t packet_end;       // Exclusive end index in the serial packet buffer for this data packet
    packetindex_t packet_count;     // Number of serial packets in this data packet, should be equal to packet_end - packet_start   
};

}

#endif