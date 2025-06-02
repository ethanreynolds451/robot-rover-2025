#include "libraries.h"
#include "definitions.h"
#include "functions.h"


void setup(){
    setup_function(); 
}

void loop(){
  	update();
    if(send.passed()){
        send_data();
    }
    delay(loop_delay);
}