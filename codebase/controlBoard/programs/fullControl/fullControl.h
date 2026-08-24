#ifndef FULL_CONTROL_H
#define FULL_CONTROL_H

#include "../../libraries/libraries.h"
#include "../../src/vehicle/vehicle.h"
#include "../../src/timer/timer.h"

#include "fullControlConfig.h"

namespace fullControl {

    // Command format: {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

    // Create timers to repeat functions at regular intervals
    Timer check_for_command(params::check_for_command_interval);  
    Timer timeout(params::control_timeout);
    Timer update_fan(params::update_fan_interval);
    Timer update_voltage(params::update_voltage_display_interval);
    Timer send_data(params::send_data_interval);

    Vehicle car(BAUD_RATE);     // Create vehicle object

    void initialize(){    
        car.begin();
    }

    void run(){
        if(check_for_command.passed()){
            if(car.get_and_run_command()){
                if(params::echo_enabled){
                    car.send_states();
                }
                timeout.reset();
            } else {
                if(timeout.passed()){       // After timout of no input, reset vehicle
                    car.timeout_error();    
                }
            }
        }
        if (update_fan.passed()){
            car.set_fan_from_temp();
            car.display_temperature();
        }
        if (send_data.passed()){
            car.read_and_send_data();
        }
        if (update_voltage.passed()){
            car.display_voltage();
            car.display_voltage_as_percent();
        }
    }

}

#endif