#include "libraries.h"
#include "definitions.h"
#include "functions.h"

Time timeout(input_timeout);

void setup(){
	Serial.begin(baud_rate);
}

void loop(){
	if(is_input()){
		read_input();
		run_input();
		timeout.reset();
	} else {
		if(timeout.passed()){
			input_error();
		}
	}
}

