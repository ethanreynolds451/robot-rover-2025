/*
Serial packet manager for vehicle communications

This module splits large data transmissions into pakets that fit within the Arduino serial buffer
It managers data integrity and provides a simple interface for sending and receiving data

Packet indexing behavior: 
- IDs roll over once the maximum value is reached, so IDs may not be unique if the packet manager is operaitng for a long time
- If long-term unique idenficaiton is required (eg. for logging), using timestamps is recommended
- Packet indexing MUST skip 0xFFFF because this is used to indicate an empty slot
*/

#ifndef SERIAL_PACKET_MANAGER_H
#define SERIAL_PACKET_MANAGER_H

#include "serialPacketManager_t.h"

// Complex implementations will be in the cpp

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
    ~SerialPacketManager(){
        reset();  // Stop serial communication and clear buffers on destruction
    };
    

    //********** Activity Management ********** /

    void begin();     // Initializes the serial communication with the configured baudrate and port, must call after setting parameters for them to take effect
    void start();     // Start the packet manager, allowing it to send and receive data based on the configured transport mode
    void stop();      // Stops the packet manager, halting all sending and receiving activity but does not reset buffers or state
    void reset();     // Resets the packet manager, clearing buffers and resetting state but does not change configuration
    void update();    // Automatically manages transmission and reception (when set to AUTOMATIC transport mode)
    void send();      // Manually trigger sending of data in the outbound buffer (not allowed in AUTOMATIC transport mode)
    void read();      // Manually trigger reading of data into the inbound buffer (not allowed in AUTOMATIC transport mode)


    // ********** Configuration ********** /

    // Configuration setters
    void set_port(uint8_t port) { this->config.port = port; };
    void set_baudrate(unsigned long baudrate) { this->config.baudrate = baudrate; };
    void set_input_mode(const MODE& mode) { this->config.input_mode = mode; };
    void set_output_mode(const MODE& mode) { this->config.output_mode = mode; };
    void set_config(const CONFIG& config) { this->config = config; };

    // Configuration getters
    uint8_t get_port() const { return this->config.port; };
    unsigned long get_baudrate() const { return this->config.baudrate; };
    const MODE& get_input_mode() const { return this->config.input_mode; };
    const MODE& get_output_mode() const { return this->config.output_mode; };
    const CONFIG& get_config() const { return this->config; };
    STATE get_state() const { return this->state; };


    // ********** Outbound Data Management ********** //

    // Data adding functions (returns the packet ID or 0xFFFF for error)
    // Data will be coppied to the outbound buffer and managed internally
    // Expects as null-terminates string, but max length can be provided for safety (defaults to max total possible length to prevent overflow)
    // Must encode all data types as a string before adding
    packetid_t add(const char* data, size_t max_length = PACKET_DATA_SIZE*PACKET_MANAGER_OUTBOUND_BUFFER_SIZE);               // Data that is part of a larger transmisison, will not mark as ready to send until add_and_send is called
    packetid_t add_and_send(const char* data, size_t max_length = PACKET_DATA_SIZE*PACKET_MANAGER_OUTBOUND_BUFFER_SIZE);      // Data constituting a complete transmission, marks data as ready to send
    
    // For manual retrieval of data (Warning: relies on internal management and only valid until next mutating call)
    const char* const* view_outbound_data() const { return this->outgoing_data; } 
    DATA_PACKET outbound_data_packet_bounds(packetid_t packet_id) const;  // Get the bounds for the data packet's location in the outbound data buffer
    
    // Copy the data into a provided buffer, returns bytes written
    size_t get_outbound_data_packet(char* buffer, size_t buffer_size, packetid_t packet_id) const;

    // Manage the outbound data buffer
    void clear_outbound_data(); 
    void clear_outbound_data_packet(packetid_t packet_id);  


    // ********** Inbound Data Management ********** //

    // For manual retrieval of data (Warning: relies on internal management and only valid until next mutating call)
    const char* const* view_inbound_data() const { return this->incoming_data; } 
    DATA_PACKET inbound_data_packet_bounds(packetid_t packet_id) const;   // Inclusive start index in inbound data buffer
    
    // Copy the data into a provided buffer, returns bytes written
    size_t get_inbound_data_packet(char* buffer, size_t buffer_size, packetid_t packet_id) const;   // Does not mark it as read
    size_t read_inbound_data_packet(char* buffer, size_t buffer_size, packetid_t packet_id);        // Marks it as read so it can be overwritten

    // Clear data
    void clear_inbound_data_packet(packetid_t packet_id); 
    void clear_inbound_data(); // Clear all inbound data packets, resetting the buffer and management system


    // ********** Data Packet ID Retrieval ********** //

    // Get ID of latest incomplete data packet (returns 0xFFFF if none available)
    packetid_t get_working_inbound_packet_id(); 
    packetid_t get_working_outbound_packet_id();

    // Get latest and oldest complete data packet IDs (returns 0xFFFF if none available)
    packetid_t get_latest_inbound_packet_id();
    packetid_t get_latest_outbound_packet_id();
    packetid_t get_oldest_inbound_packet_id();
    packetid_t get_oldest_outbound_packet_id();

    // Return an ordered array of all active data packet IDs
    // Allocated lenght is based on number of packets
    // Empty slots are filled with 0xFFFF
    const packetid_t* get_inbound_packet_ids();
    const packetid_t* get_outbound_packet_ids();

    // ********** Serial Packet Accessors ********** //

    // Should not be used for normal operation but may be required for debugging or advanced use

    // Access a specific serial packet by its header
    const SERIAL_PACKET& get_inbound_packet(const HEADER& header);
    const SERIAL_PACKET& get_outbound_packet(const HEADER& header);

    // Buffer management
    const char* view_inbound_serial_buffer() const { return this->incoming_packet; }
    const char* view_outbound_serial_buffer() const { return this->outgoing_packet; }
    void clear_inbound_serial_buffer();
    void clear_outbound_serial_buffer();

  private: 
    HardwareSerial* serial = nullptr;
    CONFIG config{};
    STATE state = STATE::UNINITIALIZED;
    SERIAL_PACKET inbound_packets[PACKET_MANAGER_INBOUND_BUFFER_SIZE];
    SERIAL_PACKET outbound_packets[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE];
    // Buffers to hold packets converted to strings or recieved as strings
    // Act as a "virtual serial buffer" 
    char incoming_packet[ARDUINO_SERIAL_BUFFER_SIZE]; 
    char outgoing_packet[ARDUINO_SERIAL_BUFFER_SIZE];
    // Hold ordered pointers to the data fields in the packets, initialize each element to nullptr
    const char* incoming_data[PACKET_MANAGER_INBOUND_BUFFER_SIZE] = {nullptr};  
    const char* outgoing_data[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE] = {nullptr};
    // Hold ordered pointers to the packet IDs for tracking and management
    packetid_t inbound_packet_ids[PACKET_MANAGER_INBOUND_BUFFER_SIZE] = {INVALID_PACKET_ID};
    packetid_t outbound_packet_ids[PACKET_MANAGER_OUTBOUND_BUFFER_SIZE] = {INVALID_PACKET_ID};
}; 

}

#endif