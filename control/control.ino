#include "libraries.h"
#include "definitions.h"
#include "functions.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

void setup(){ 
  _setup(); 
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
  if (update_fan.passed()){
    check_temp();
  }
 	delay(loop_delay);
}
