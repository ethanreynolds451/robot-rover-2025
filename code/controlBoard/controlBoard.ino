#include "vehicle/vehicle.h"

#include "dependencies/timer.h"

// Command format: {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

uint8_t echo_enabled = 1;     // Set to 1 to enable serial echo for debugging

// Create timers to repeat functions at regular intervals
Timer mainloop_timer(10);        // Must be at least 6 for data integrity
Timer timeout(5000);
Timer update_fan(10000);
Timer update_voltage(500);
Timer send_data(1000);

Vehicle car(BAUD_RATE);     // Create vehicle object

void setup(){    
  car.begin(); 
}

void loop(){
    if(mainloop_timer.passed()){
        if(car.get_and_run_command()){
            if(echo_enabled){
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
    }
    if (send_data.passed()){
        car.read_and_send_data();
    }
    if (update_voltage.passed()){
        car.display_voltage();
    }
}