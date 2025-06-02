#include "definitions.h"

#ifndef FUNCTIONS_h
#define FUNCTIONS_h

void setup_function(){
    Serial.begin(baud_rate);
    // Set pinmodes
    pinMode(pin.brake, OUTPUT);
    pinMode(pin.reverse_1, OUTPUT);
    pinMode(pin.reverse_2, OUTPUT);
    pinMode(pin.s_reverse_1, OUTPUT);
    pinMode(pin.s_reverse_2, OUTPUT);
    pinMode(pin.shift_1, OUTPUT);
    pinMode(pin.shift_2, OUTPUT);
    pinMode(pin.speed_, OUTPUT);
    pinMode(pin.s_speed, OUTPUT);
    pinMode(pin.fan, OUTPUT);
    pinMode(pin.headlight, OUTPUT);
    pinMode(pin.thermistor, INPUT);
}

uint8_t serial_loop_counter = 0;        // Should be in a class but fine here for now

bool is_input(){
	if(Serial.available() > 0) {
        serial_loop_counter++;
		return true;
	}
	return false;
}

bool serial_delay_passed(){
    if(serial_loop_counter >= serial_delay){
        serial_loop_counter = 0;
        return true;
    }
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

void run_input(){
	uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
	char tmp_code[16];
  char tmp_data[16];
	uint16_t end_index = strlen(input);
	uint16_t index = 0;
  uint8_t data_index = 0;
  uint8_t code_index = 0;
	if(input[index] == '{'){					// look for start charcter
		while(index <= end_index){				// end if strlen exceed
			if(input[index] == '}'){ 			// break if end characther
				break;
			} else {
				// get the data packet designator
          // First clear temp data buffer
			memset(tmp_code, 0, tmp_len);
          	memset(tmp_data, 0, tmp_len);
				code_index = 0;				// go to start of data buffer
				while(true){				// until data encountered
					index++;          // Advance to next charachter in input
					if(isalpha(input[index]) && input[index] != '['){
						tmp_code[code_index] = input[index];	// read designator into tmp buffer
						code_index++;                        // advance to next buffer character
					} else {
            tmp_code[code_index] = '\0';       
						break;	// If bad nonalpha or end char encounter
					}
				}
    			// get data
				if(input[index] == '['){		// find data charchter
          data_index = 0;
					while(true){					// enter data loop	
						index++;
						if(input[index] == ']'){	// break if end data character
              tmp_data[data_index] = '\0';
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
					if(strcmp(command.commands[code_index].code, tmp_code) == 0){
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

void check_temp(){
  uint16_t temp = analogRead(pin.thermistor);
  temp = 30*log(temp) - 95;
  if(temp < 25){
 	control.f_speed = 0;
  } else if(temp > 70){
 	control.f_speed = 100;
  } else {
 	control.f_speed = map(temp, 25, 70, 0, 100);
  }
}

void update(){
  fan.set(map(control.f_speed, 0, 100, 100, 255));
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
