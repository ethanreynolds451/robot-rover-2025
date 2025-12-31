#ifndef VEHICLE_h
#define VEHICLE_h

#include "dependencies/definitions.h"
#include "dependencies/libraries.h"

#include "pwm.h"
#include "relay.h"
#include "serial.h"
#include "voltageDivider.h"
#include "batteryMonitor.h"

class Vehicle {
    public:
        Vehicle(baud_rate) : baud_rate(baud_rate) {
            // Create objects that are components of control system
            SerialControl computer(baud_rate);
            Relay brake_relay(pin.brake);
            Relay reverse_1_relay(pin.reverse_1);
            Relay reverse_2_relay(pin.reverse_2);
            Relay s_reverse_1_relay(pin.s_reverse_1);
            Relay s_reverse_2_relay(pin.s_reverse_2);
            Relay shift_1_relay(pin.shift_1);
            Relay shift_2_relay(pin.shift_2);
            PWM speed_(pin.speed_);
            PWM s_speed(pin.s_speed);
            PWM fan(pin.fan);
            logDivider internal_temp(pin.thermistor, 30, 125);      // Added diode to reduce noise, adjusted offset from -95 to -125
            batteryMonitor voltage(pin.batter_monitor, 1/.60, 0, "flooded_lead_acid");
            fourDigitDisplay display(address.pcf);
        }
        void initialize(){
            reset_vehicle();    // Ensure vehicle is set to default state
            set_pinmodes();     // Initialize hardware pins
            computer.begin();   // Start serial communication with onboard computer
        }
        char* read_serial(){
            computer.read_input();
            return computer.read();
        }
        void send_serial(const char* output){
            computer.send_output(output);
        }
        void get_command(){
            computer.read();
            if computer.is_command() {
                 computer.get_into(current_command, string_limit);
                 return true;
            }
            return false; 
        }
        void check_for_command(){
            if(get_command()){
                run_input();
                return true;
            }
            return false;
        }
        // Setters
        void set_brake(bool active){
            output_states.brake = active;
            update_outputs();
        }
        void set_direction(bool set_reverse){
            output_states.reverse = set_reverse;
            update_outputs();
        }
        void set_shift(bool set_series){
            output_states.shift_up = set_series;
            update_outputs();
        }
        void set_speed(uint8_t set_speed){
            output_states.speed_ = map(set_speed, 0, 100, pwm_min, pwm_max);
            update_outputs();
        }
        void set_s_direction(bool set_reverse){
            output_states.s_reverse = set_reverse;
            update_outputs();
        }
        void set_s_speed(uint8_t set_speed){
            output_states.s_speed = map(set_speed, 0, 100, pwm_min, pwm_max);
            update_outputs();
        }
        void set_f_speed(uint8_t set_speed){
            output_states.f_speed = map(set_speed, 0, 100, pwm_min, pwm_max);
            update_outputs();
        }
        void reset(){
            set_defaults();
            update_outputs();
        }
        void set_fan_from_temp(){
            temp = internal_temp.read();
            if(temp < 25){
                output_states.f_speed = 0;
            } else if(temp > 50){
                output_states.f_speed = 100;
            } else {
                output_states.f_speed = map(temp, 25, 50, 0, 100);
            }
            update_outputs();
        }
        void display_voltage(){
            float voltage = voltage.read_voltage();
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "Battery Voltage: %.2f V\n", voltage);
            computer.write(buffer);
        }
        void display_voltage_as_percent(){
            float voltage = voltage.read_voltage();
            float percent = voltage.read_percentage();
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "Battery Voltage: %.2f V (%.1f%%)\n", voltage, percent);
            computer.write(buffer);
        }
        void timeout_error(){
            reset();
            computer.write("Vehicle reset due to input timeout.\n");
        }
        void execute_command_as_string(uint8_t code, const char* val){
            if(code == 0) {
                set_brake(atoi(val));
            } else if(code == 1) {
                set_direction(atoi(val));
            } else if(code == 2) {
                set_s_direction(atoi(val));
            } else if(code == 3) {
                set_shift(atoi(val));
            } else if(code == 4) {
                set_speed(atoi(val));
            } else if(code == 5) {
                set_s_speed(atoi(val));
            } else if(code == 6) {
                set_f_speed(atoi(val));
            }
        }
    private:
        namespace output_states {
            bool brake = true;			//br
            bool reverse = false;		//rv
            bool s_reverse = false;		//srv
            bool shift_up = false;		//su
            uint8_t speed_ = 0;			//sp
            uint8_t s_speed = 0;		//ssp
            uint8_t f_speed = 0;        //fan
        }
        namespace default_output_states {
            static const bool brake = true;		
            static const bool reverse = false;		
            static const bool s_reverse = false;		
            static const bool shift_up = false;		
            static const uint8_t speed_ = 0;		
            static const uint8_t s_speed = 0;	
            static const uint8_t f_speed = 0;
        }
        char[string_limit] current_command;
        void set_pinmodes(){     
            // Set pinmodes
            pinMode(pin.brake, OUTPUT);
            pinMode(pin.reverse_1, OUTPUT);
            pinMode(pin.reverse_2, OUTPUT);
            pinMode(pin.s_reverse_1, OUTPUT);
            pinMode(pin.s_reverse_2, OUTPUT);
            pinMode(pin.shift_1, OUTPUT);
            pinMode(pin.shift_2, OUTPUT);
            pinMode(pin.speed_, OUTPUT);
            pinMode(pin.s_speed, OUTPUT);
            pinMode(pin.fan, OUTPUT);
            pinMode(pin.headlight, OUTPUT);
            pinMode(pin.thermistor, INPUT);
        }
        void set_defaults(){
            output_states.brake = default_output_states.brake;
            output_states.reverse = default_output_states.reverse;
            output_states.s_reverse = default_output_states.s_reverse;
            output_states.shift_up = default_output_states.shift_up;
            output_states.speed_ = default_output_states.speed_;
            output_states.s_speed = default_output_states.s_speed;
            output_states.f_speed = default_output_states.f_speed;
        }
        void update_outputs(){
            fan.set(map(control.f_speed, 0, 100, 100, 255));
            brake_relay.set(!control.brake);
            reverse_1_relay.set(control.reverse);
            reverse_2_relay.set(control.reverse);
            s_reverse_1_relay.set(control.s_reverse);
            s_reverse_2_relay.set(control.s_reverse);
            shift_1_relay.set(control.shift_up);
            shift_2_relay.set(control.shift_up);
            speed_.set(control.speed_);
            s_speed.set(control.s_speed);
        }
        void run_input(){
            uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
            char tmp_code[16];
            char tmp_data[16];
            uint16_t end_index = strlen(input);
            uint16_t index = 0;
            uint8_t data_index = 0;
            uint8_t code_index = 0;
            if(input[index] == '{'){					// look for start charcter
                while(index <= end_index){				// end if strlen exceed
                    if(input[index] == '}'){ 			// break if end characther
                        break;
                    } else {
                        // get the data packet designator
                // First clear temp data buffer
                    memset(tmp_code, 0, tmp_len);
                    memset(tmp_data, 0, tmp_len);
                        code_index = 0;				// go to start of data buffer
                        while(true){				// until data encountered
                            index++;          // Advance to next charachter in input
                            if(isalpha(input[index]) && input[index] != '['){
                                tmp_code[code_index] = input[index];	// read designator into tmp buffer
                                code_index++;                        // advance to next buffer character
                            } else {
                                tmp_code[code_index] = '\0';       
                                break;	// If bad nonalpha or end char encounter
                            }
                        }
                        // get data
                        if(input[index] == '['){		// find data charchter
                            data_index = 0;
                            while(true){					// enter data loop	
                                index++;
                                if(input[index] == ']'){	// break if end data character
                                    tmp_data[data_index] = '\0';
                                    break;
                                } else {
                                    tmp_data[data_index] = input[index];
                                    data_index++;
                                }
                            }
                        }
                        // run command with data
                        uint8_t code_index = 0;
                        while(code_index <= command.number_of){
                            if(strcmp(command.commands[code_index].code, tmp_code) == 0){
                                command.execute(code_index, tmp_data);
                                break;
                            } else {
                                code_index++;
                            }
                        }
                    }
                }
            }
        }
};  

#endif