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
	uint16_t i = 0;
	while(Serial.available()){
		input[i] = Serial.read();
		if(i == string_limit){
			break;
		}
		i++;
	}
}

void decode_input(){
	
}

void execute_input(){
	
}

void update_relays(){
	
}

void update_displays(){
	
}

void input_error(){
	
}

#endif