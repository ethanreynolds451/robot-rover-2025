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
		: baud_rate(baud_rate), 				// Store the baud rate input
	    read_timer(read_delay(baud_rate)),		// Use baud rate to calculate appropriate read delay, initialize timer
      	write_timer(write_delay(baud_rate))		// Use baud rate to calculate appropriate write delay, initialize timer
	{
		// These buffers are handled using packets, not as full strings
		// Initialize all characters in buffers to null character
		for(uint16_t i = 0; i < INPUT_LENGTH; i++){
			// Write null character to each position in the memory buffer
			this->input_buffer[i] = '\0';
		}
		for(uint16_t i = 0; i < OUTPUT_LENGTH; i++){
			// Write null character to each position in the memory buffer
			this->output_buffer[i] = '\0';
		}
	}

	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
		while (!Serial) { }  // only on USB-based boards, wait till serial is ready
	}

	// Update function called in main program loop, manages timing of reads and writes
	void update(){
		// If there is outgoing data and the send delay has passed, send it
		if (this->write_timer.passed()){
			// Sends next packet in output buffer over serial if there is data to send
			this->send_next_packet();
		}
		// If there is incoming data and the read delay has passed, read it into buffer
		if(this->read_timer.passed()){
			// Reads from serial buffer into input buffer if data available
			this->read_next_packet();
		}
	}

	// Return the number of bytes available to retrieve from the input buffer
	size_t available(){
		return total_space_filled(this->input_buffer, INPUT_PACKETS);
	}

	// Return the amount of space left in the output buffer to read new data
	size_t free(){
		return total_space_remaining(this->output_buffer, OUTPUT_PACKETS, OUTPUT_LENGTH);
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

	// Data retrieving functions

	// Directly return the entire input buffer
	bool get_buffer(char* return_buffer, uint16_t length = INPUT_LENGTH){
		char* data = this->input_buffer;		// Declare a pointer to the input buffer
		if(strlen(data) == 0){
			return false; // No data to		 return
		}
		strncpy(return_buffer, data, length);	// Copy the data to the return buffer up to specified length
		return true; 							// Data successfully copied to return buffer
	}

	// Sort the packets and return data in order, clear and re-index to zero
	bool get(char* return_buffer, uint16_t length = INPUT_LENGTH){
		if(total_space_filled(this->input_buffer, INPUT_PACKETS) == 0){
			return false; 						// No data to return
		}
		// Copy all packets in order to return buffer
		uint16_t buffer_index = 0;
		uint8_t highest_index = 0;
		uint8_t highest_packet = 0;
		
		// Find highest index
		for(uint8_t i = 0; i < INPUT_PACKETS; i++){
			if(input_order[i] > highest_index){
				highest_packet = i;
				highest_index = input_order[i];
			}
		}
		
		// Copy packets in order
		for(uint8_t index = 1; index <= highest_index && buffer_index < length; index++){
			for(uint8_t i = 0; i < INPUT_PACKETS; i++){
				if(input_order[i] == index){
					size_t to_copy = space_filled(this->input_buffer, i);
					if(buffer_index + to_copy > length) to_copy = length - buffer_index;
					
					for(size_t j = 0; j < to_copy; j++){
						return_buffer[buffer_index++] = this->input_buffer[i * PACKET_LENGTH + j];
					}
					break;
				}
			}
		}
		return_buffer[buffer_index] = '\0';
		return true;
	}

	// Get an input packet by index
	bool get_packet(char* return_buffer, uint8_t packet_number, uint16_t length = PACKET_LENGTH){
		if(space_filled(this->input_buffer, packet_number) == 0){
			return false; 						// No data in this packet to return
		}
		this->get_packet_in(return_buffer, this->input_buffer, packet_number);
		return true;
	};

	// Get the next input packet in order, delete once read and re-index the remaining packets
	bool get_next_packet(char* return_buffer, uint8_t packet_number, uint16_t length = PACKET_LENGTH){
		if(space_filled(this->input_buffer, packet_number) == 0){
			return false; 						// No data in this packet to return
		}
		this->retrieve_next_packet(return_buffer);
		return true;
	};

	// Clear the entire input buffer
	void clear_input(){
		clear_data(this->input_buffer, INPUT_LENGTH);
	}

	// *** Direct serial functions (blocking) ***

	// Pass-through read and write functions
	void serial_read(char* output_buffer, uint16_t length = PACKET_LENGTH){
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
		// Make sure there is data in the buffer before trying to send
		if(total_space_filled(this->output_buffer, OUTPUT_PACKETS) > 0){
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
	}

	// Don't clear or re-index until a validation response is received
	bool send_next_packet_with_validation(){}
	// This version is not used in implementation but could be useful in future

	// ** INPUT management **

	// Retrieve a specific packet from given buffer
	bool retrieve_packet(char* return_buffer, char* buffer, uint8_t packet_number, size_t length = PACKET_LENGTH){
		size_t filled = space_filled(buffer, packet_number);
		if(filled == 0 || length < filled){
			return false; 							// No data in this packet or not enough space to hold it
		}
		for(size_t i = 0; i < filled; i++){
			return_buffer[i] = buffer[packet_number * PACKET_LENGTH + i];
		}
		return_buffer[filled] = '\0'; // Null-terminate
		return true;
	}

	// Return the contents of the next packet in order, clear and re-index
	bool retrieve_next_packet(char* return_buffer, size_t buffer_length){
		uint8_t highest_index = 0;
		uint8_t current_packet = 0;

		// Find packet with index 1 (next to send)
		for(uint8_t i = 0; i < INPUT_PACKETS; i++){
			if(input_order[i] == 1){
				current_packet = i;
				highest_index = 1;
				break;
			}
		}

		// If found packet with index 1, return it
		if(highest_index > 0){
			// Copy the packet to return buffer
			size_t bytes_filled = space_filled(this->input_buffer, current_packet);
			if(bytes_filled == 0 || buffer_length < bytes_filled) return false;
			
			for(size_t i = 0; i < bytes_filled; i++){
				return_buffer[i] = this->input_buffer[current_packet * PACKET_LENGTH + i];
			}
			return_buffer[bytes_filled] = '\0';

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

			return true;
		}
		return false;
	}

	// Get all input data ordered by packet index
	// NOTE: This function is removed to avoid use-after-free bugs with local buffers
	// Use get_next_packet() or get_buffer() instead for safer access
	
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

	// Read available data into highest packet, respecting packet boundaries
	// Will only read if there is data available, otherwise returns false
	// If buffer overflows, oldest data may be lost
	bool read_next_packet() {
		// Check for available data
		if (!is_input()) {
			return false;
		}
		
		// Find the highest indexed packet
		uint8_t highest_packet = 0;
		uint8_t highest_index = 0;
		for(uint8_t i = 0; i < INPUT_PACKETS; i++){
			if(input_order[i] > highest_index){
				highest_packet = i;
				highest_index = input_order[i];
			}
		}
		
		// If no packet is indexed yet, use packet 0 with index 1
		if(highest_index == 0){
			highest_packet = 0;
			input_order[0] = 1;
			highest_index = 1;
		}
		
		// Read data into the highest packet
		uint16_t index = space_filled(this->input_buffer, highest_packet);
		while (Serial.available() && index < PACKET_LENGTH) {
			int c = Serial.read();
			if (c < 0) break; // Safety check
			
			this->input_buffer[highest_packet * PACKET_LENGTH + index] = (char)c;
			index++;
		}
		
		// Null-terminate the packet
		if(index < PACKET_LENGTH) {
			this->input_buffer[highest_packet * PACKET_LENGTH + index] = '\0';
		}
		return true;
	}


	// ** Core functions to interact with packets in buffer **
	// Packet numbers are zero indexed

	// Copy contents of a specified packet into provided buffer
	// Returns number of bytes copied
	uint16_t get_packet_in(char* buffer, uint8_t packet_number, char* dest_buffer, size_t dest_length){
		size_t filled = space_filled(buffer, packet_number);
		if(filled == 0 || dest_length < filled) return 0;
		
		for(size_t i = 0; i < filled; i++){
			dest_buffer[i] = buffer[packet_number * PACKET_LENGTH + i];
		}
		return filled;
	}
	
	// Write new data to specific packet
	bool set_packet_in(char* buffer, const char* new_data, uint8_t packet_number){
		if (packet_number >= OUTPUT_PACKETS){
			return false; // Invalid packet number
		}
		size_t data_len = strlen(new_data);
		if (data_len > PACKET_LENGTH - 1){
			return false; // Data too long for packet (need space for null terminator)
		}
		for(size_t i = 0; i < data_len; i++){
			buffer[packet_number * PACKET_LENGTH + i] = new_data[i];
		}
		buffer[packet_number * PACKET_LENGTH + data_len] = '\0'; // Null-terminate
		return true;
	}

	// The rest of these can be applied to any buffer with same structure

	// Fill packet with new data, returns how many bytes were written
	uint16_t fill_packet(char* buffer, const char* new_data, uint8_t packet_number){
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