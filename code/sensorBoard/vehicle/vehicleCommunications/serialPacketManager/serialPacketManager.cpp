#include "serialPacketManager.h"


namespace serial_packet_manager {

using SPM = SerialPacketManager;


// *** Constructor and Destructor *** //

SPM::SerialPacketManager(unsigned long baudrate, uint8_t serial_port) {
    this->config.baudrate = baudrate;
    this->config.port = serial_port;
    // Allow the packet manager to be used on any hardware serial port present
    if (config.port == 0){
        serial = &Serial;   // Use hardware serial 0
    } 
#if defined(HAVE_HWSERIAL1) || defined(PIN_SERIAL1_RX) || defined(SERIAL1_PRESENT)            
    else if (config.port == 1){
        serial = &Serial1;  // Use hardware serial 1
    } 
#endif 
#if defined(HAVE_HWSERIAL2) || defined(PIN_SERIAL2_RX) || defined(SERIAL2_PRESENT)            
    else if (config.port == 2){
        serial = &Serial2;  // Use hardware serial 2
    } 
#endif
#if defined(HAVE_HWSERIAL3) || defined(PIN_SERIAL3_RX) || defined(SERIAL3_PRESENT)            
    else if (config.port == 3){
        serial = &Serial3;  // Use hardware serial 3
    } 
#endif   
    else {
        // Fallback to ensure it is defined even if an invalid port is specified
        serial = &Serial;
    }      
}

SPM::~SerialPacketManager() { reset(); }


//********** Activity Management ********** //

SPM::begin(){
    initialize(); 
    start();
}

SPM::initialize(){
    if(this->state != STATE::UNINITIALIZED){
        reset(); 
    }
    this->serial->begin(this->config.baudrate);
    this->state = STATE::INITIALIZED;
}

SPM::start(){
    if((this->state == STATE::INITIALIZED) || (this->state == STATE::STOPPED)){
        this->state = STATE::ACTIVE;
    }
}

SPM::stop(){
    if(this->state == STATE::ACTIVE){
        this->state = STATE::STOPPED;
    }
}

SPM::reset(){
    this->state = STATE::UNINITIALIZED;
    clear_inbound_data();
    clear_outbound_data();
    clear_inbound_serial_buffer();
    clear_outbound_serial_buffer();
}

SPM::update(){
    if(this->state == STATE::ACTIVE){
        if(this->config.output_mode.transport_mode == TRANSPORT_MODE::AUTOMATIC){
            send();
        }
        if(this->config.input_mode.transport_mode == TRANSPORT_MODE::AUTOMATIC){
            read();
        }
    }
}

SPM::send(){
    if((this->state == STATE::ACTIVE) && (this->config.output_mode.transport_mode == TRANSPORT_MODE::MANUAL)){
        // add implementation for sending data in the outbound buffer
    }
}

SPM::read(){
    if((this->state == STATE::ACTIVE) && (this->config.input_mode.transport_mode == TRANSPORT_MODE::MANUAL)){
        // add implementation for reading data into the inbound buffer
    }
}

// ********** Outbound Data Management ********** //

// ********** Inbound Data Management ********** //

// ********** Data Packet ID Retrieval ********** //

SPM::packetid_t get_working_inbound_packet_id(); 
SPM::packetid_t get_working_outbound_packet_id();
SPM::packetid_t get_latest_inbound_packet_id();
SPM::packetid_t get_latest_outbound_packet_id();
SPM::packetid_t get_oldest_inbound_packet_id();
SPM::packetid_t get_oldest_outbound_packet_id();


// *** Internal Functions *** //

// Return a pointer to the packet with the matching header, or nullptr if not found
SPM::find_packet(const SERIAL_PACKET* packets, packetindex_t num_packets, const HEADER& header){
    for(SERIAL_PACKET* packet = packets; packet < packets + num_packets; packet++){
        if(packet->header.packet_id == header.packet_id && 
           packet->header.packet_index == header.packet_index && 
           packet->header.packet_count == header.packet_count){
            return packet;
        }
    }
    return nullptr;
}

// Return the packet ID of the 
SPM::get_complete_packet_id(const SERIAL_PACKET* packets, packetindex_t num_packets, unsigned long timestamp) {
    
}

SPM::get_working_packet_id()
