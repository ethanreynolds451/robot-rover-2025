#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

bool is_input(){
	if(Serial.available() > 0) {
		return true;
	}
	return false;
}

void read_input(){
	uint16_t index = 0;
	while(Serial.available()){
		input[index] = Serial.read();
		if(index == string_limit){
			break;
		}
		index++;
	}
}

void run_input(){
	uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
	char tmp_code[16];
  char tmp_data[16];
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
          tmp_code[clr] = ' ';                    
          tmp_data[clr] = ' ';
					clr++;
				}
				uint8_t tmp_index = 0;				// go to start of data buffer
				while(true){				// until data encountered
					index++;
					if(isalpha(input[index]) && input[index] != '['){
						tmp_code[tmp_index] = input[index];	// read designator into tmp buffer
						tmp_index++;
					} else {
						break;	// If bad nonalpha or end char encounter
					}
				}
    			// get data
				if(input[index] == '['){		// find data charchter
					while(true){					// enter data loop
						uint8_t data_index = 0;
						index++;
						if(input[index] == ']'){	// break if end data character
							break;
						} else {
	                        tmp_data[data_index] = input[index];
	                        data_index++;
						}
					}
				}
    			// run command with data
				uint8_t code_index = 0;
				while(code_index <= command.number_of){
					if(strcmp(command.commands[code_index].code, tmp_code)){
						command.execute(code_index, tmp_data);
						break;
					} else {
       					code_index++;
     				}
				}
			}
		}
	}
}

void update(){
	brake_relay.set(!control.brake);
	reverse_1_relay.set(control.reverse);
	reverse_2_relay.set(control.reverse);
	s_reverse_1_relay.set(control.s_reverse);
	s_reverse_2_relay.set(control.s_reverse);
	shift_1_relay.set(control.shift_up);
	shift_2_relay.set(control.shift_up);
	speed_.set(control.speed_);
	s_speed.set(control.s_speed);
}

void reset_vehicle(){
  control.set_defaults();
  control.set_brake(true);
  update();
}

void input_error(){
	reset_vehicle();
  Serial.println("Input timeout, vehicle reset");
}


#endif
