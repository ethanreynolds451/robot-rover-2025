#include "libraries.h"
#include "definitions.h"
#include "functions.h"

Time timeout(input_timeout);

void setup(){ 
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
}

void loop(){
  update();
	if(is_input()){
		read_input();
		run_input();
		timeout.reset();
	} else {
		if(timeout.passed()){
			input_error();
		}
	}
 	delay(loop_delay);
}
