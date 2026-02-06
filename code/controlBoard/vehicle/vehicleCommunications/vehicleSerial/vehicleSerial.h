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
		this->input_buffer[0] = '\0';	// Initialize input string to empty
		this->output_buffer[0] = '\0'; // Initialize output string to empty	
	}

	uint8_t read_delay(uint32_t baud){
		return (uint8_t)round(((float)OUTPUT_LENGTH*10.*10000./(float)baud)*1.1);
	}
	uint8_t write_delay(uint32_t baud){
		return (uint8_t)round(((float)INPUT_LENGTH*10.*10000./(float)baud)*1.1);
	}

	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
		while (!Serial) { }  // only on USB-based boards, wait till serial is ready
	}

	void update(){
		// If there is outgoing data and the send delay has passed, send it
		if (this->write_timer.passed()){
			if(total_space_filled(this->output_buffer) > 0){
				this->send_next_packet();
			}
		}
		// If there is incoming data and the read delay has passed, read it into buffer
	}

	// *** Buffer manipulation functions ***

	// Directly return the input buffer
	char* get(){
		return this->input_buffer;
	}

	// Copy input buffer into provided buffer for number of bytes
	// Default to length of the input buffer
	void get_into(char* return_buffer, uint16_t length = INPUT_LENGTH){
		strncpy(return_buffer, this->input_buffer, length);
	}

	// *** Direct serial functions ***

	// Pass-through read and write functions
	char* read(){
		if (is_input()){
			read_input();		// This is a blocking call
		}
		return this->input_buffer;
	}
	void read_into(char* output_buffer, uint16_t length = PACKET_LENGTH){
		if (is_input()){
			read_input();
			strncpy(output_buffer, this->input_buffer, length);
		}
	}
	void write(const char* output){
		Serial.print(output);
	}
	void writeln(const char* output){
		Serial.println(output);
	}


	// Temp for test will modify later
	void add(const char* output){
		this->add_data(output);
	}

	void send(){
		this->send_next_packet();
	}

	void clear(){
		this->clear_output();
	}


  private:	
	// Declaration parameters
  	uint32_t baud_rate;

	// Just for now for backwards compatability before its replaced
	uint8_t old_read_delay = 100; 

	// Hardcoded parameters
	static constexpr size_t PACKET_LENGTH = 64;			// Max packet length from arduino serial buffer
	// Number of packets, hardcode to avoid dynamic allocation
	static constexpr uint8_t INPUT_PACKETS = 1; 		// Read only one command packet at a time, packets always less than 64 bytes
	static constexpr uint8_t OUTPUT_PACKETS = 8;		// Allow room for output buffering

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

	// Add data to output buffer, returns true if successful
	bool add_data(const char* data){
		// Must be a null terminated string
		if(data == nullptr || strlen(data) == 0){
			return false; // No data to add
		}

		// Make sure there is enough space in the buffer
		if(total_space_remaining(this->output_buffer) < strlen(data)){
			return false; // Not enough space to add data
		}

		// Allocate data to the packets in the output buffer
		uint8_t current_packet = 0;
		uint8_t highest_index = 0;
		const char* remaining_data = data;

		// Try to fill the latest partially filled packet if there is one
		if(total_space_filled(this->output_buffer) > 0){
			Serial.println("Filling partial packet");
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
				Serial.print("Filling packet ");
				Serial.println(current_packet);
				// If all data has been allocated, return true
				if(strlen(remaining_data) == 0){
					return true;
				} else {
					Serial.print("Bytes remaining after filling partial packet: ");
					Serial.println(strlen(remaining_data)); 
					Serial.print("Data remaining after filling partial packet: ");
					Serial.println(remaining_data);
				}
			}
		}
		// This does not do any re-indexing because this packet will always be indexed already


		// Move on to empty packets
		while(true){
			Serial.println("Filling new packet");
			uint8_t timeout = 0;
			// Find an empty packet
			current_packet = 0;
			for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
				if(output_order[i] == 0){
					current_packet = i;
					break;
				}
			}
			// Fill the packet
			Serial.print("Adding data to packet ");
			Serial.println(current_packet);

			remaining_data += fill_packet(this->output_buffer, remaining_data, current_packet);
			
			Serial.print("Bytes remaining: ");
			Serial.println(remaining_data);

			// Set the index 
			highest_index++;
			output_order[current_packet] = highest_index;

			// Return once all the data has been allocated
			if(strlen(remaining_data) == 0){
				return true;
			}		

			// Make sure it doesn't infinite loop if something goes wrong
			timeout++;
			if(timeout > OUTPUT_PACKETS){
				// Should never reach here because of initial space check
				return false; 
			}
			// Might want to add reversion so it doesn't leave garbage in case of failure part way through
		}
	}

	void clear_input(){
		clear_data(this->input_buffer);
	}

	void clear_output(){
		clear_data(this->output_buffer);
	}

	// Read data from the imput buffer in order and return it
	char* read_data(){

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
	void send_next_packet_with_validation(){}
	// This version is not used in implementation but could be useful in future


	// ** Core functions to interact with packets in buffer **
	// Packet numbers are zero indexed

	char* read_packet(uint8_t packet_number){
		char buffer[PACKET_LENGTH];
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			buffer[i] = this->input_buffer[packet_number * PACKET_LENGTH + i];
		}
		return buffer;
	}
	
	// Write new data to specific packet in buffer
	void write_packet(const char* new_data, uint8_t packet_number){
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			this->output_buffer[packet_number * PACKET_LENGTH + i] = new_data[i];
		}
	}

	// Fill packet with new data, returns how many bytes were written
	uint8_t fill_packet(char* buffer, const char* new_data, uint8_t packet_number){
		// First index in the packet that doesn't have data
		size_t start_index = space_filled(buffer, packet_number) + packet_number * PACKET_LENGTH;
		// End of the packet
		size_t end_index = (packet_number + 1) * PACKET_LENGTH - 1;
		// Index to increment through input data
		size_t data_index = 0;
		// Total length of input data
		size_t data_length = strlen(new_data);
		// End index in packet
		size_t end = data_length <= end_index ? data_length : end_index;
		for(int i = start_index; i <= end; i++){
			buffer[i] = new_data[data_index];
			data_index++;
		}

		// return the number of bytes written
		return data_index;
		Serial.println(data_index); 
	}

	// Return index of first empty packet
	size_t space_filled(char* buffer, uint8_t packet){
		uint8_t index = 0;
		// Can't use strlen for this because contiguous packets may also be filled
		for(int i = 0; i < PACKET_LENGTH; i++){
			if(buffer[packet * PACKET_LENGTH + i] != '\0'){
				index++;
			}
		}
		return index;
	}

	size_t space_remaining(char* buffer, uint8_t packet){
		return PACKET_LENGTH - space_filled(buffer, packet);
	}

	size_t total_space_filled(char* buffer){
		size_t total = 0;
		for(uint8_t i = 0; i < OUTPUT_PACKETS; i++){
			total += space_filled(buffer, i);
		}
		return total;
	}

	size_t total_space_remaining(char* buffer){
		return OUTPUT_LENGTH - total_space_filled(buffer);
	}

	// Write null characters to specific packet in buffer
	void clear_packet(char* buffer, uint8_t packet_number){
		for(uint16_t i = 0; i < PACKET_LENGTH; i++){
			buffer[packet_number * PACKET_LENGTH + i] = '\0';
		}
	}

	// Write null characters to entire buffer
	void clear_data(char* buffer){
		size_t length = sizeof(buffer)/sizeof(buffer[0]);
		for(uint16_t i = 0; i < length; i++){
			buffer[i] = '\0';
		}
	}

	char* get_input(){

	}


	// *** Internal serial interface functions ***

	bool is_input(){
		if(Serial.available() > 0) {
			return true;
		}
		return false;
	}

	// The old blocking read function
	void read_input(){
		delay(old_read_delay);
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
