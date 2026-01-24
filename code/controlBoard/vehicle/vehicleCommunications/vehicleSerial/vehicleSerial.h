// Compiled successfully 2025-01-02

#ifndef VEHICLESERIAL_h
#define VEHICLESERIAL_h

#include <Arduino.h>

class RobotSerial {
  public:
	RobotSerial(uint16_t baud_rate) : baud_rate(baud_rate) {
		this->input_buffer[0] = '\0';	// Initialize input string to empty
	}
	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
	}
	char* read(){
		if (is_input()){
			read_input();		
		}
		return this->input_buffer;
	}
	void read_into(char* output_buffer, uint16_t length = STRING_LIMIT){
		if (is_input()){
			read_input();
			strncpy(output_buffer, this->input_buffer, length);
		}
	}
	char* get(){
		return this->input_buffer;
	}
	void get_into(char* output_buffer, uint16_t length = STRING_LIMIT){
		strncpy(output_buffer, this->input_buffer, length);
	}
	void write(const char* output){
		Serial.print(output);
	}
	void add(const char* output){
		strcat(this->output_buffer, output);
	}
	void send(){
		Serial.print(this->output_buffer);
		this->output_buffer[0] = '\0'; // Clear output buffer after sending
	}
	void write_line(const char* output){
		Serial.println(output);
	}
	bool is_command(){
		return is_command(this->input_buffer);
	}
	bool is_command(const char* input_string){
		if (!input_string) return false;		// Check for null pointer
		namespace D = Code::Delimiter;			// Local namespace alias
		const size_t start_length = strlen(D::start);
		const size_t end_length = strlen(D::end);
		const size_t input_length = strlen(input_string);
		return ((input_length >= start_length + end_length) && 
				(strncmp(input_string, D::start, start_length) == 0) &&
				(strncmp(input_string + input_length - end_length, D::end, end_length) == 0)
				);
	}
  private:
  	static constexpr uint8_t serial_delay = 1;
  	uint16_t baud_rate;
	char input_buffer[STRING_LIMIT];
	char output_buffer[STRING_LIMIT];
	uint8_t loop_counter = 0;     
	bool is_input(){
		if(Serial.available() > 0) {
			this->loop_counter++;
			return true;
		}
		return false;
	}
	void read_input(){
		delay(RobotSerial::serial_delay);
		uint16_t index = 0;
		while(Serial.available()){
			this->input_buffer[index] = Serial.read();
			if(index == STRING_LIMIT - 1){
				break;
			}
			index++;
		}
		this->input_buffer[index] = '\0'; // Null-terminate the string
	}
};


#endif
