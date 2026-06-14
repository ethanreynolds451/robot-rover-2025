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
    SerialPacketManager(unsigned long baudrate = 115200, uint8_t serial_port = 0);
    ~SerialPacketManager();
    
    //********** Activity Management ********** /

    void begin();       // Brings to active state
    void initialize();  // Initializes the serial communication with the configured baudrate and port, must call after setting parameters for them to take effect
    void start();       // Start the packet manager, allowing it to send and receive data based on the configured transport mode
    void stop();        // Stops the packet manager, halting all sending and receiving activity but does not reset buffers or state
    
    void reset();       // Resets the packet manager, clearing buffers and resetting state but does not change configuration
    void update();      // Automatically manages transmission and reception (when set to AUTOMATIC transport mode)
    void send();        // Manually trigger sending of data in the outbound buffer (not allowed in AUTOMATIC transport mode)
    void read();        // Manually trigger reading of data into the inbound buffer (not allowed in AUTOMATIC transport mode)


    // ********** Configuration ********** //

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
    const char* const* view_outbound_data() const { return this->output.data; } 
    DATA_PACKET outbound_data_packet_bounds(packetid_t packet_id) const;  // Get the bounds for the data packet's location in the outbound data buffer
    
    // Copy the data into a provided buffer, returns bytes written
    size_t get_outbound_data_packet(char* buffer, size_t buffer_size, packetid_t packet_id) const;

    // Manage the outbound data buffer
    void clear_outbound_data(); 
    void clear_outbound_data_packet(packetid_t packet_id);  


    // ********** Inbound Data Management ********** //

    // For manual retrieval of data (Warning: relies on internal management and only valid until next mutating call)
    const char* const* view_inbound_data() const { return this->input.data; } 
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
    const packetid_t* get_inbound_packet_ids() { return this->input.ids; };
    const packetid_t* get_outbound_packet_ids() { return this->output.ids; };

    // ********** Serial Packet Accessors ********** //

    // Should not be used for normal operation but may be required for debugging or advanced use

    // Access a specific serial packet by its header
    const SERIAL_PACKET& get_inbound_packet(const HEADER& header) { return find_packet(this->input.packets, this->input.buffer_size, header); };
    const SERIAL_PACKET& get_outbound_packet(const HEADER& header) {return find_packet(this->output.packets, this->output.buffer_size, header);};

    // Buffer management
    const char* view_inbound_serial_buffer() const { return this->input.serial_buffer; };
    const char* view_outbound_serial_buffer() const { return this->output.serial_buffer; };
    void clear_inbound_serial_buffer() { memset(this->input.serial_buffer, 0, ARDUINO_SERIAL_BUFFER_SIZE); };
    void clear_outbound_serial_buffer() { memset(this->output.serial_buffer, 0, ARDUINO_SERIAL_BUFFER_SIZE); };

  private: 
    // *** Internal Data *** ///
    HardwareSerial* serial = nullptr;
    CONFIG config{};
    STATE state = STATE::UNINITIALIZED;
    // Use input and output structs to package all relevant data for easier management
    INPUT input{};
    OUTPUT output{};

    // *** Internal Functions *** ///

    // Return a reference to the packet with matching header or nullptr if not found
    const SERIAL_PACKET& find_packet(const SERIAL_PACKET* packets, packetindex_t num_packets, const HEADER& header);

    void update_incoming_data();   
    void update_outgoing_data();
  }; 

}

#endif