#ifndef SERIAL_h
#define SERIAL_h

#include <Arduino.h>
#include "dependencies/definitions.h"

class SerialControl {
  public:
	SerialControl(baud_rate) : baud_rate(baud_rate) {}
	void begin(){
		Serial.begin(baud_rate);
	}
	char* read(){
		if (is_input()){
			read_input();
			return input;
		}
	}
	void read_into(char* buffer, uint16_t length){
		if (is_input()){
			read_input();
			strncpy(buffer, input, length);
		}
	}
	char* get(){
		return input;
	}
	char* get_into(char* buffer, uint16_t length){
		strncpy(buffer, input, length);
		return buffer;
	}
	void write(const char* output){
		Serial.print(output);
	}
	bool is_command(){
		if(is_command(input)){
			return true;
		}
		return false;
	}
	bool is_command(const char* input_string){
		if(input_string[0] == '{' && input_string[strlen(input_string)-1] == '}'){
			return true;
		}
		return false;
	}
  private:
  	static const uint8_t serial_delay = 1;
	char input[STRING_LIMIT];
	uint8_t loop_counter = 0;     
	bool is_input(){
		if(Serial.available() > 0) {
			serial_loop_counter++;
			return true;
		}
		return false;
	}
	void read_input(){
		delay(serial_delay);
		uint16_t index = 0;
		while(Serial.available()){
			input[index] = Serial.read();
			if(index == STRING_LIMIT){
				break;
			}
			index++;
		}
		input[index] = '\0'; // Null-terminate the string
	}
};


#endif