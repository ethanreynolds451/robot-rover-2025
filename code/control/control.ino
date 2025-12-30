#include "definitions/global.h"
#include "objects/timer.h"
#include "objects/vehicle.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

// Create timers to repeat functions at regular intervals
Timer loop_timer(loop_delay);
Timer timeout(input_timeout);
Timer update_fan(fan_delay);

// Create vehicle object
Vehicle car(baud_rate);

void setup(){    
  car.initialize(); 
}

void loop(){
    if(loop_timer.passed()){
        if(car.check_for_command()){
                timeout.reset();
            }
        } else {
            if(timeout.passed()){       // After timout of no input, reset vehicle
                car.timeout_error();
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
    }
    if (update_fan.passed()){
        car.set_fan_from_temp();
    }
    if timeout.passed(){
        // Reset vehicle to default state
        car.reset();
    }
}
