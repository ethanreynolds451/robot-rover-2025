#include "libraries.h"
#include "definitions.h"
#include "functions.h"


void setup(){
    setup_function(); 
}

void loop(){
    if(loop delay.passed()){
        update_sensors(); 
    }
  	update();
    if(send_delay.passed()){
        send_data();
    }

}