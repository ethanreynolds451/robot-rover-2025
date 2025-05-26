#include "libraries.h"
#include "definitions.h"
#include "functions.h"

void setup(){
	Serial.begin(baud_rate);
}

void loop(){
  	update();
	send_data();
}