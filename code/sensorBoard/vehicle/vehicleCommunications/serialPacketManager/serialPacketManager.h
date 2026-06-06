/*
Serial packet manager for vehicle communications

This module splits large data transmissions into pakets that fit within the Arduino serial buffer
It managers data integrity and provides a simple interface for sending and receiving data

*/


#ifndef SERIAL_PACKET_MANAGER_H
#define SERIAL_PACKET_MANAGER_H

#include "serialPacketManager_t.h"

// Implementations will be in the cpp

namespace serial_packet_manager {

class SerialPacketManager {
  public: 
    SerialPacketManager(unsigned long baudrate = 115200, uint8_t serial_port = 0)
      {
        this->config.baudrate = baudrate;
        this->config.port = serial_port;
        // Allow the packet manager to be used on any hardware serial port present
            if (config.port == 0){
                serial = &Serial;   // Use hardware serial 0
            } 
#if defined(HAVE_HWSERIAL1) || defined(PIN_SERIAL1_RX) || defined(SERIAL1_PRESENT)            else if (config.port == 1){
                serial = &Serial1;  // Use hardware serial 1
            } 
#endif 
#if defined(HAVE_HWSERIAL2) || defined(PIN_SERIAL2_RX) || defined(SERIAL2_PRESENT)            else if (config.port == 2){
                serial = &Serial2;  // Use hardware serial 2
            } 
#endif
#if defined(HAVE_HWSERIAL3) || defined(PIN_SERIAL3_RX) || defined(SERIAL3_PRESENT)            else if (config.port == 3){
                serial = &Serial3;  // Use hardware serial 3
            } 
#endif   
            else {
                // Fallback to ensure it is defined even if an invalid port is specified
                serial = &Serial;
            }      
  }
    ~SerialPacketManager();
    
    // Activity management functions
    void begin();
    void start(); 
    void stop();
    void reset();
    void update();    // Automatically manages transmission and reception (when set to AUTOMATIC transport mode)
    void send();      // Manually trigger sending of data in the outbound buffer (not allowed in AUTOMATIC transport mode)
    void read();      // Manually trigger reading of data into the inbound buffer (not allowed in AUTOMATIC transport mode)

    // Configuration functions
    void set_port(uint8_t port);
    void set_baudrate(unsigned long baudrate);
    void set_input_mode(MODE mode);
    void set_output_mode(MODE mode);
    void set_config(CONFIG config);

    // Parameter getters
    uint8_t get_port() const { return this->config.port; };
    unsigned long get_baudrate() const { return this->config.baudrate; };
    const MODE& get_input_mode() const { return this->config.input_mode; };
    const MODE& get_output_mode() const { return this->config.output_mode; };
    const CONFIG& get_config() const { return this->config; };

    // Data adding functions (returns the packet ID or -1 for error)
    int16_t add(char* data);               // Data that is part of a larger transmisison, will not mark as ready to send until add_and_send is called
    int16_t add_and_send(char* data);      // Data constituting a complete transmission, marks data as ready to send
      // If partial data exists, add_and_send will complete the previous transmissoin and mark it as ready to send

    // Return the ID of the latest incomplete packet
    int16_t get_working_inbound_packet_id(); 
    int16_t get_working_outbound_packet_id();

    // Data accessors
    char*** view_latest_inbound_data();
    char*** view_latest_outbound_data();
    char*** get_latest_inbound_data();
    char*** get_latest_outbound_data();
    
    char*** view_oldest_inbound_data();
    char*** view_oldest_outbound_data();
    char*** get_oldest_inbound_data();
    char*** get_oldest_outbound_data();

    char*** view_all_inbound_data();
    char*** view_all_outbound_data();
    char*** get_all_inbound_data();
    char*** get_all_outbound_data();

    // Individual packet accessors
    SERIAL_PACKET& get_inbound_packet();
    SERIAL_PACKET& get_outbound_packet();

    // Buffer management
    char* view_inbound_buffer();
    char* view_outbound_buffer();
    char* clear_inbound_buffer();
    char* clear_outbound_buffer();

    void clear_inbound_data(); 
    void clear_outbound_data(); 

  private: 
    HardwareSerial* serial = nullptr;
    CONFIG config{};
    SERIAL_PACKET inbound_packets[PACKET_MANAGER_INBOUND_BUFFER_SIZE];
    SERIAL_PACKET outbound_packets[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE];
    // Buffers to hold packets converted to strings or recieved as strings
    char incoming_packet[64]; 
    char outgoing_packet[64];
    // Hold ordered pointers to the data fields in the packets
    char** [] incoming_data = {nullptr};  
    char** [] outgoing_data = {nullptr};
}; 

}

#endif