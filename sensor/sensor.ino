#include "libraries.h"
#include "definitions.h"
#include "functions.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

void setup(){
    setup_function(); 
}

void loop(){
    if(loop_delay.passed()){
        update_sensors(); 
    }
    if(send_delay.passed()){
        send_data();
    }
}
