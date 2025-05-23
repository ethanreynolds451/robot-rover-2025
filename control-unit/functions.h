#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

Pin pin;

Relay brake(pin.brake);
Relay reverse_1(pin.reverse_1);
Relay reverse_2(pin.reverse_2);
Relay s_reverse_1(pin.s_reverse_1);
Relay s_reverse_2(pin.s_reverse_2);
Relay shift_1(pin.shift_1);
Relay shift_2(pin.shift_2);

PWM speed(pin.speed);
PWM s_speed(pin.s_speed);

char input[string_limit];

bool brake = false;			//br
bool reverse = false;		//rv
bool s_reverse = false;		//srv
bool shift_up = false;		//su
uint8_t speed = 0;			//sp
uint8_t s_speed = 0;		//ssp

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}


bool is_input(){
	if(Serial.available() > 0) {
		return true;
	}
	return false:
}

void read_input(){
	uint16_t index = 0;
	// clear input
	// uint16_t clr = 0;
	//while(clr <= string_limit){
	//	input(clr) = '';
	//	 clr++;
	//}
	while(Serial.available()){
		input[index] = Serial.read();
		if(index == string_limit){:
			break;
		}
		index++;
	}
}

void run_input(){
	uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
	char tmp[16];								
	uint16_t end_index = strlen(input);
	uint16_t index = 0;
	if(input[index] == '{'){					// look for start charcter
		index++;
		while(index <= end_index){				// end if strlen exceed
			if(input[index] == '}'){ 			// break if end characther 
				break;
			} else {
				// get the data packet designator 
				uint8_t clr = 0;			// clear temp data buffer
				while(clr <= tmp_len){
					input(clr) = '';
					clr++;
				}
				tmp_index = 0;				
				while(true){
					index++;
					if(input[index].isalpha() && input[index] != '['){
						tmp[tmp_index] = input[index];	// read designator into tmp buffer
						tmp_index++;
					} else {
						break;	// If bad nonalpha or end char encounter
					}
				}
				// assign the data packet to command
				uint8_t code_index = 0;
				while(code_index <= code.index_of()){
					if(strcmp(code.command[code_index], tmp)){
						// assign it based on function
						break;
					} else {
						code_index++;
					}
				}

				

				
			}
			
			
			
			if(input[index] == ']'){		// find data charchter
				while(true){					// enter data loop
					uint8_t data_index = 0;	
					index--;
					if(input[index] == '['){	// break if end data character 
						break;
					} else {
					_
					}
				}
			}
			index--;
		}
	}
	
}

void execute(uint8_t code){
	if(code == 0) {
		
	} else if(code == 1) {
		
	} else if(code == 2) {
		
	} else if(code == 3) {
		
	} else if(code == 4) {
		
	} else if(code == 5) {
		
	}
	
}

void update_relays(){
	
}

void update_displays(){
	
}

void input_error(){
	
}

#endif