#ifndef SERIAL_h
#define SERIAL_h

#include "dependencies/libraries.h"

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
	void reset_loop(){
		loop_counter = 0;
	}
	bool delay_passed(){
		if(serial_loop_counter >= serial_delay){
			serial_loop_counter = 0;
			return true;
		}
	}
  private:
	char input[string_limit];
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
			if(index == string_limit){
				break;
			}
			index++;
		}
	}
};


#endif