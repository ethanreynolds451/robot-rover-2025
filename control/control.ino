#include "libraries.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

Time loop_timer(loop_delay);
Time timeout(input_timeout);
Time update_fan(fan_delay);

void setup(){    
  setup_function(); 
}

// Move this when needed
bool serial_delay_passed(){
    if(serial_loop_counter >= serial_delay){
        serial_loop_counter = 0;
        return true;
    }
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
            if(timeout.passed()){       // After timout of no input, reset vehicle
                input_error();
            }
        }
        if(echo_enabled){
            Serial.println("br: " + String(control.brake) + 
                           " rv: " + String(control.reverse) + 
                           " srv: " + String(control.s_reverse) + 
                           " su: " + String(control.shift_up) + 
                           " sp: " + String(control.speed_) + 
                           " ssp: " + String(control.s_speed) + 
                           " fan: " + String(control.f_speed));
        }
        delay(loop_delay);
    }
    if (update_fan.passed()){
        check_temp();
    }
}
