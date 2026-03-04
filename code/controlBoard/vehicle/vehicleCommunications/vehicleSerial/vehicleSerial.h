// Compiled successfully 2025-01-02

/*	This version splits data into 64-bype packets to avoid buffer overflow 
	and uses an update function with timer to manage delay
	for non-blocking approach
*/ 

#ifndef VEHICLESERIAL_h
#define VEHICLESERIAL_h

#include "timer/timer.h"

class RobotSerial {
  public:
	RobotSerial(uint32_t baud_rate) 
		: baud_rate(baud_rate), 
	    read_timer(read_delay(baud_rate)),
      	write_timer(write_delay(baud_rate))
	{
		// These buffers are handled using packets, not as full strings
		// Initialize all characters in buffers to nuill character
		for(uint16_t i = 0; i < INPUT_LENGTH; i++){
			this->input_buffer[i] = '\0';
		}
		for(uint16_t i = 0; i < OUTPUT_LENGTH; i++){
			this->output_buffer[i] = '\0';
		}
	}

	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
		while (!Serial) { }  // only on USB-based boards, wait till serial is ready
	}

	// Non-blocking loop function 
	void update(){
		// If there is outgoing data and the send delay has passed, send it
		if (this->write_timer.passed()){
			if(total_space_filled(this->output_buffer, OUTPUT_PACKETS) > 0){
				this->send_next_packet();
			}
		}
		// If there is incoming data and the read delay has passed, read it into buffer
		if(this->read_timer.passed()){
			// Already checks if there is data available
			this->read_next_packet();
		}
	}

	size_t available(){
		return total_space_filled(this->input_buffer, INPUT_PACKETS);
	}


	// *** Buffer manipulation functions ***


	// ** Output (sending) functions **

	// Add data to the output buffer, return true if successful, false if not enough space
	bool add(const char* output){
		return this->add_data(output);
	}

	bool add_packet(const char* output, uint8_t packet_number){
		return this->set_packet_in(this->output_buffer, output, packet_number);
	}

	// Send the next packet, delete once sent and re-index the remaining packets
	// Will only send if the write delay has passed, otherwise returns false
	bool send(){
		return this->send_next_packet();
	}

	bool send(uint8_t packet_number){
		this->send_packet(packet_number);
		return true; // This function does not manage timing, so it always succeeds
	}

	// Not implemented yet
	bool send_with_validation(){
		return this->send_next_packet_with_validation();
	}

	// Clear the entire output buffer
	void clear_output(){
		clear_data(this->output_buffer, OUTPUT_LENGTH);
	}


	// ** Input (receiving) functions **

	bool read(){
		if(is_input()){
			return this->read_next_packet();
		}
		return false;
	}

	bool read(uint8_t packet_number){
		if(is_input()){
			return this->read_packet(packet_number);
		}
		return false;
	}

	// Directly return the entire input buffer
	void get_buffer(char* return_buffer, uint16_t length = INPUT_LENGTH){
		char* data = this->input_buffer;		// Declare a pointer to the input buffer
		strncpy(return_buffer, data, length);
	}

	// Sort the packets and return data in order, clear and re-index to zero
	char* get(){
		if(total_space_filled(this->input_buffer, INPUT_PACKETS) == 0){
			//Serial.println("No data available to return"); // Debugging statement to verify no data is available
			return nullptr; // No data to return
		} else {
			return this->get_input();
		}
	}

	// Get an input packet by index
	char* get_packet(uint8_t packet_number){
		return this->get_packet_in(this->input_buffer, packet_number);
	};

	// Get the next input packet in order, delete once read and re-index the remaining packets
	char* get_next_packet(){
		return this->retrieve_next_packet(); 
	};

	// Clear the entire input buffer
	void clear_input(){
		clear_data(this->input_buffer, INPUT_LENGTH);
	}

	// Get functions into a provided buffer, will only copy up to the specified length to avoid overflow

	// For ordered packets
	void get_into(char* return_buffer, uint16_t length = INPUT_LENGTH){
		char* ordered_data = this->get();
		strncpy(return_buffer, ordered_data, length);
	}




	void get_packet_into(char* return_buffer, uint8_t packet_number, uint16_t length = INPUT_LENGTH){
		char* data = this->get_packet(packet_number);
		strncpy(return_buffer, data, length);
	}

	void get_next_packet_into(char* return_buffer, uint16_t length = INPUT_LENGTH){
		char* data = this->get_next_packet();
		strncpy(return_buffer, data, length);
	}

	// *** Direct serial functions (blocking) ***

	// Pass-through read and write functions
	char* serial_read(){
		if (is_input()){
			read_serial_input();		// This is a blocking call
		}
		return this->input_buffer;
	}
	void serial_read_into(char* output_buffer, uint16_t length = PACKET_LENGTH){
		if (is_input()){
			read_serial_input();
			strncpy(output_buffer, this->input_buffer, length);
		}
	}
	void serial_write(const char* output){
		Serial.print(output);
	}
	void serial_writeln(const char* output){
		Serial.println(output);
	}



  private:	
	// Declaration parameters
  	uint32_t baud_rate;
	
	// Calculate delays based on baud rate and length of packet, add 10% buffer for safety
	// Used for initialization of timers
	uint8_t read_delay(uint32_t baud){
		return (uint8_t)round(((float)OUTPUT_LENGTH*10.*10000./(float)baud)*1.1);
	}
	uint8_t write_delay(uint32_t baud){
		return (uint8_t)round(((float)INPUT_LENGTH*10.*10000./(float)baud)*1.1);
	}

	// Hardcoded parameters
	static constexpr size_t PACKET_LENGTH = 64;			// Max packet length from arduino serial buffer
	// Number of packets, hardcode to avoid dynamic allocation
	static constexpr uint8_t INPUT_PACKETS = 1; 		// Read only one command packet at a time, packets always less than 64 bytes
	static constexpr uint8_t OUTPUT_PACKETS = 8;		// Allow ample room for output buffering

	// Derived parameters (calculated at compile time)
	static constexpr size_t INPUT_LENGTH = PACKET_LENGTH * INPUT_PACKETS;  				// Only needs to be as long as serial buffer
	static constexpr size_t OUTPUT_LENGTH = PACKET_LENGTH * OUTPUT_PACKETS; 	// Max input string length
	
	// Buffers
	char input_buffer[INPUT_LENGTH];
	char output_buffer[OUTPUT_LENGTH];

	// Timers (initialized in constuctor)
	Timer read_timer;
	Timer write_timer; 

	// *** Buffer management variables and functions ***

	// Packet tracking, zero index is no data
	uint8_t input_order[INPUT_PACKETS] = {0};
	uint8_t output_order[OUTPUT_PACKETS] = {0};


	// ** Intermediate functions to manage data in buffer **

	// ** OUTPUT management **

	// Add data to output buffer, returns true if successful
	bool add_data(const char* data){
		// Must be a null terminated string
		if(data == nullptr || strlen(data) == 0){
			return false; // No data to add
		}

		// Make sure there is enough space in the buffer
		if(total_space_remaining(this->output_buffer, OUTPUT_PACKETS, OUTPUT_LENGTH) < strlen(data)){
			return false; // Not enough space to add data
		}

		// Allocate data to the packets in the output buffer
		uint8_t current_packet = 0;
		uint8_t highest_index = 0;
		const char* remaining_data = data;

		// Try to fill the latest partially filled packet if there is one
		if(total_space_filled(this->output_buffer, OUTPUT_PACKETS) > 0){
			for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
				// Find highest index packet
				if(output_order[i] > current_packet){
					current_packet = i;
					highest_index = output_order[i];
				}
			}
		
			// If there is space in this packet, fill it
			if(space_remaining(this->output_buffer, current_packet) > 0){
				remaining_data += fill_packet(this->output_buffer, remaining_data, current_packet);
				// If all data has been allocated, return true
				if(strlen(remaining_data) == 0){
					return true;
				} 
			}
		}
		// This does not do any re-indexing because this packet will always be indexed already

		// Move on to empty packets
		while(strlen(remaining_data) > 0){
			// Will check if there's data remaining before each loop cycle
			// Find an empty packet
			current_packet = 0;
			for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
				if(output_order[i] == 0){
					current_packet = i;
					break;
				}
			}
			
			// Fill the packet
			remaining_data += fill_packet(this->output_buffer, remaining_data, current_packet);

			// Set the index of this packet to be one higher than the current highest index
			highest_index++;
			output_order[current_packet] = highest_index;	
		}
		return true;
	}


	// Send a specific packet from the buffer
	void send_packet(uint8_t packet_number){
		// Create buffer to hold packet data
		char buffer[PACKET_LENGTH];
		// Copy in the data from the packet to send
		for(uint8_t i = 0; i < PACKET_LENGTH; i++){
			buffer[i] = this->output_buffer[packet_number * PACKET_LENGTH + i];
		}
		// Write the packet over serial
		Serial.print(this->output_buffer);
		// Reciever will have to strip null characters
	}
	
	// Send the next packet, clear and re-index
	bool send_next_packet(){
		// Find packet with index 1
		uint8_t current_packet = 0;
		for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
			if(output_order[i] == 1){
				current_packet = i;
				break;
			}
			// No packet with index 1 found, buffer is empty
			return false;
		}

		// Send the packet (automatically selects output buffer)
		send_packet(current_packet);

		// Clear the packet
		clear_packet(this->output_buffer, current_packet);

		// Re-index the remaining packets
		for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
			if(output_order[i] > 1){
				output_order[i]--;
			} else if(output_order[i] == 1){
				output_order[i] = 0; // Clear the sent packet index
			}
		}
		return true; 
	}

	// Don't clear or re-index until a validation response is received
	bool send_next_packet_with_validation(){}
	// This version is not used in implementation but could be useful in future

	// ** INPUT management **

	// Retrieve a specific packet from input
	char* retrieve_packet(uint8_t packet_number){
		char buffer[PACKET_LENGTH];
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			buffer[i] = buffer[packet_number * PACKET_LENGTH + i];
		}
		return buffer;
	}

	// Return the contents of the next input packet in order, clear and re-index
	char* retrieve_next_packet(){
		char buffer[PACKET_LENGTH];
		uint8_t highest_index = 0;
		uint8_t current_packet = 0;

		for(uint8_t i = 0; i < INPUT_PACKETS; i++){
			// Find highest index packet
			if(output_order[i] > current_packet){
				current_packet = i;
				highest_index = input_order[i];
			}
		}

		// If the highest packet is 1 or greater, return it
		if(highest_index > 0){
			// Copy the packet to a buffer
			strncpy(buffer, get_packet_in(this->input_buffer, current_packet), PACKET_LENGTH);

			// Clear the packet
			clear_packet(this->input_buffer, current_packet);

			// Re-index the remaining packets
			for(uint8_t i = 0; i < INPUT_PACKETS; i++){
				if(input_order[i] > 1){
					input_order[i]--;
				} else if(input_order[i] == 1){
					input_order[i] = 0; // Clear the sent packet index
				}
			}

			return buffer;
		}
	}

	// Written by AI, need to check
	char* get_input() {
		char buffer[INPUT_LENGTH];
		uint8_t current_packet = 0;
		uint8_t highest_index = 0;

		for(uint8_t i = 0; i < INPUT_PACKETS; i++){
			// Find highest index packet
			if(input_order[i] > current_packet){
				current_packet = i;
				highest_index = input_order[i];
			}
		}

		// If there is data in the buffer, return it in order
		if(highest_index > 0){
			size_t buffer_index = 0;
			for(uint8_t index = 1; index <= highest_index; index++){
				for(uint8_t i = 0; i < INPUT_PACKETS; i++){
					if(input_order[i] == index){
						strncpy(buffer + buffer_index, get_packet_in(this->input_buffer, i), PACKET_LENGTH);
						buffer_index += space_filled(this->input_buffer, i);
						break;
					}
				}
			}
			return buffer;
		} else {
			return nullptr; // No data to return
		}
	}
	
	// Read data from serial input buffer into specified packet
	// Return true of successful, false if no data available 
	// Written by AI, test and verify
	bool read_packet(uint8_t packet_number){
		clear_packet(this->input_buffer, packet_number); // Clear the packet before writing new data
		uint16_t index = 0;
		if(is_input()){
			while(Serial.available()){	
				int c = Serial.read();		// Returns int, -1 if no data available
				if (c < 0) break; // Safety to ensure invalid character isn't read
				this->input_buffer[packet_number * PACKET_LENGTH + index] = (char)c;	// Need to cast to char
				if(index == PACKET_LENGTH - 1){
					break;
				}
				index++;
			}
			this->input_buffer[packet_number * PACKET_LENGTH + index] = '\0'; // Null-terminate the string
			return true;
		}
		return false;
	}


	// Note: this should be re-written to share lower level functions with the add_data function but I didn't feel like it

	// Uses same implementation as the add function to fill the highest packet then move on to empty packets, but with the read buffer instead of the output buffer
	// Will only read if there is data available, otherwise returns false
	// If there is an overflow, the lowest packet will be cleared and data will be read into it, continuing until all data is read
	// AI wrote this, need to test
	bool read_next_packet() {
		uint8_t highest_packet = 0;
		uint16_t index = 0;

		// Check for available data
		if (is_input()) {
			//Serial.println("Data available, reading into buffer..."); // Debugging statement
			// Read data into the highest packet first
			while (Serial.available()) {
				int c = Serial.read();
				if (c < 0) break; // Safety check

				// If we have reached the end of the highest packet, move to the next
				if (index >= PACKET_LENGTH) {
					highest_packet++;
					index = 0;
				}

				// If we exceed the number of input packets, clear the lowest one
				if (highest_packet >= INPUT_PACKETS) {
					clear_packet(this->input_buffer, 0); // Clear the lowest packet
					highest_packet = 0; // Reset to start filling from the lowest packet
				}

				// Store the character in the appropriate packet
				this->input_buffer[highest_packet * PACKET_LENGTH + index] = (char)c;
				index++;
			}

			// Null-terminate the last packet
			this->input_buffer[highest_packet * PACKET_LENGTH + index] = '\0';
			return true;
		}
		return false;
	}


	// ** Core functions to interact with packets in buffer **
	// Packet numbers are zero indexed

	// Return the contents of a specified packet
	char* get_packet_in(char* buffer, uint8_t packet_number){
		char packet_data[PACKET_LENGTH];
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			packet_data[i] = buffer[packet_number * PACKET_LENGTH + i];
		}
		return packet_data;
	}
	
	// Write new data to specific packet
	bool set_packet_in(char* buffer, const char* new_data, uint8_t packet_number){
		if (packet_number >= OUTPUT_PACKETS){
			return false; // Invalid packet number
		}
		if (strlen(new_data) > PACKET_LENGTH){
			return false; // Data too long for packet
		}
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			buffer[packet_number * PACKET_LENGTH + i] = new_data[i];
		}
		return true;
	}

	// The rest of these can be applied to any buffer with same structure

	// Fill packet with new data, returns how many bytes were written
	// ChatGPT fixed this, need to verify
	uint8_t fill_packet(char* buffer, const char* new_data, uint8_t packet_number){
		size_t start_index = space_filled(buffer, packet_number)
							+ packet_number * PACKET_LENGTH;

		size_t packet_end = (packet_number + 1) * PACKET_LENGTH;
		size_t packet_space = packet_end - start_index;

		size_t data_length = strlen(new_data);

		size_t bytes_to_copy = data_length < packet_space
							? data_length
							: packet_space;

		for (size_t i = 0; i < bytes_to_copy; i++) {
			buffer[start_index + i] = new_data[i];
		}

		return bytes_to_copy;
	}

	// Return index of first empty packet
	size_t space_filled(char* buffer, uint8_t packet){
		uint8_t index = 0;
		// Can't use strlen for this because contiguous packets may also be filled
		for(uint8_t i = 0; i < PACKET_LENGTH; i++){
			if(buffer[packet * PACKET_LENGTH + i] != '\0'){
				index++;
			}
		}
		return index;
	}

	size_t space_remaining(char* buffer, uint8_t packet){
		return PACKET_LENGTH - space_filled(buffer, packet);
	}

	size_t total_space_filled(char* buffer, uint8_t number_of_packets){
		size_t total = 0;
		for(uint8_t i = 0; i < number_of_packets; i++){
			total += space_filled(buffer, i);
		}
		return total;
	}

	size_t total_space_remaining(char* buffer, uint8_t number_of_packets, uint8_t total_length){
		return total_length - total_space_filled(buffer, number_of_packets);
	}

	// Write null characters to specific packet in buffer
	void clear_packet(char* buffer, uint8_t packet_number){
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			buffer[packet_number * PACKET_LENGTH + i] = '\0';
		}
	}

	// Write null characters to entire buffer
	void clear_data(char* buffer, size_t length) {
		for (size_t i = 0; i < length; i++) {
			buffer[i] = '\0';
		}
	}


	// *** Internal serial interface functions ***

	bool is_input(){
		if(Serial.available() > 0) {
			return true;
		}
		return false;
	}

	// The old blocking read function
	void read_serial_input(){
		delay(read_delay(baud_rate));
		uint16_t index = 0;
		while(Serial.available()){	
			int c = Serial.read();		// Returns int, -1 if no data available
			if (c < 0) break; // Safety to ensure invalid character isn't read
			this->input_buffer[index] = (char)c;	// Need to cast to char
			if(index == INPUT_LENGTH - 1){
				break;
			}
			index++;
		}
		this->input_buffer[index] = '\0'; // Null-terminate the string
	}
};


#endif