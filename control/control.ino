#include "libraries.h"
#include "definitions.h"
#include "functions.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

void setup(){ 
  setup_function(); 
}

void loop(){
    if(loop_timer.passed()){
        update_control();
        if(is_input()){
            if(serial_delay_passed()){
                read_input();
                run_input();
                timeout.reset();
            }
        } else {
            if(timeout.passed()){
                input_error();
            }
        }
        delay(loop_delay);
    }
    if (update_fan.passed()){
        check_temp();
    }
}
