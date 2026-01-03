// Compiled successfully 2025-01-02

#ifndef SERIAL_h
#define SERIAL_h

#include <Arduino.h>
#include "dependencies/definitions.h"

class RobotSerial {
  public:
	RobotSerial(uint16_t baud_rate_def) : baud_rate(baud_rate_def) {
		input_buffer[0] = '\0';	// Initialize input string to empty
	}
	void begin(){
		Serial.begin(baud_rate);	// Start serial communication
	}
	char* read(){
		if (is_input()){
			read_input();		
		}
		return input_buffer;
	}
	void read_into(char* buffer, uint16_t length = STRING_LIMIT){
		if (is_input()){
			read_input();
			strncpy(buffer, input_buffer, length);
		}
	}
	char* get(){
		return input_buffer;
	}
	char* get_into(char* buffer, uint16_t length = STRING_LIMIT){
		strncpy(buffer, input_buffer, length);
		return buffer;
	}
	void write(const char* output){
		Serial.print(output);
	}
	void write_line(const char* output){
		Serial.println(output);
	}
	bool is_command(){
		if(is_command(input_buffer)){
			return true;
		}
		return false;
	}
	bool is_command(const char* input_string){
		if((strlen(input_string) > 1) && (input_string[0] == Code::Delimiter::start && input_string[strlen(input_string)-1] == Code::Delimiter::end)){
			return true;
		}
		return false;
	}
  private:
  	uint16_t baud_rate;
	static constexpr uint8_t serial_delay = 1;
	char input_buffer[STRING_LIMIT];
	uint8_t loop_counter = 0;     
	bool is_input(){
		if(Serial.available() > 0) {
			loop_counter++;
			return true;
		}
		return false;
	}
	void read_input(){
		delay(serial_delay);
		uint16_t index = 0;
		while(Serial.available()){
			input_buffer[index] = Serial.read();
			if(index == STRING_LIMIT - 1){
				break;
			}
			index++;
		}
		input_buffer[index] = '\0'; // Null-terminate the string
	}
};


#endif
