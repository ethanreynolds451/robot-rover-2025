#ifndef VEHICLE_h
#define VEHICLE_h

#include "components.h"

class Vehicle {
    public:
        RobotSerial computer;         // Made this public to allow direct access to serial interface
        Vehicle(uint16_t baud_rate) 
            :   computer(baud_rate),
                brake_relay(Pin::brake),
                reverse_1_relay(Pin::reverse_1),
                reverse_2_relay(Pin::reverse_2),
                s_reverse_1_relay(Pin::s_reverse_1),
                s_reverse_2_relay(Pin::s_reverse_2),
                shift_1_relay(Pin::shift_1),
                shift_2_relay(Pin::shift_2),
                speed_(Pin::speed_),
                s_speed(Pin::s_speed),
                fan(Pin::fan, 100, 255),
                internal_temp(Pin::thermistor, 30, 125),
                voltage(Pin::battery_monitor, BATTERY_VOLTAGE_SLOPE, 0, BATTERY_TYPE),
                display(Address::pcf, Pin::digit_1, Pin::digit_2, Pin::digit_3, Pin::digit_4)   
            {}
        void begin(){
            // Pinmodes are already set within each class constructor or inirializer
            reset();            // Ensure vehicle is set to default state
            computer.begin();   // Start serial communication with onboard computer
            display.begin();    // Start display (PCF8575 with Wire I2C)
        }        
        void get_command(){
            computer.read();
            if computer.is_command() {
                 computer.get_into(current_command, STRING_LIMIT);
                 return true;
            }
            return false; 
        }
        void get_and_run_command(){
            if(get_command()){
                run_input();
                return true;
            }
            return false;
        }
        // Setters
        void set_brake(bool active){
            OutputStates::brake = active;
            update_outputs();
        }
        void set_direction(bool set_reverse){
            OutputStates::reverse = set_reverse;
            update_outputs();
        }
        void set_shift(bool set_series){
            OutputStates::shift_up = set_series;
            update_outputs();
        }
        void set_speed(uint8_t set_speed){
            OutputStates::speed_ = set_speed;
            update_outputs();
        }
        void set_s_direction(bool set_reverse){
            OutputStates::s_reverse = set_reverse;
            update_outputs();
        }
        void set_s_speed(uint8_t set_speed){
            OutputStates::s_speed = set_speed;
            update_outputs();
        }
        void set_f_speed(uint8_t set_speed){
            OutputStates::f_speed = set_speed;
            update_outputs();
        }
        void reset(){
            OutputStates::reset();
            update_outputs();
        }
        void set_fan_from_temp(){
            temp = internal_temp.read();
            if(temp < MIN_FAN_TEMP){
                OutputStates::f_speed = 0;
            } else if(temp > MAX_FAN_TEMP){
                OutputStates::f_speed = 100;
            } else {
                OutputStates::f_speed = map(temp, MIN_FAN_TEMP, MAX_FAN_TEMP, 0, 100);
            }
            update_outputs();
        }
        void display_voltage(){
            float voltage = voltage.read_voltage();
            char buffer[64];
            // Display voltage on serial for debug
                snprintf(buffer, sizeof(buffer), "Battery Voltage: %.2f V\n", voltage);
                computer.write(buffer);
            display.print_decimal(voltage);
        }
        void display_voltage_as_percent(){
            // Round percent to nearest whole number
            int percent = int(round(voltage.read_percentage()));
            char buffer[64];
            // Display voltage on serial for debug
                sprintf(buffer, sizeof(buffer), "Battery Voltage: %d%%\n", percent);
                computer.write(buffer);
            display.print_integer(percent);     // Print as an integer
        }
        void display_temperature(){
            float temperature = internal_temp.read();
            char buffer[64];
            // Display temperature on serial for debug
                snprintf(buffer, sizeof(buffer), "Internal Temperature: %.2f C\n", temperature);
                computer.write(buffer);
            display.print_decimal(temperature);
        }
        void read_data(){
            Data::internal_temp = internal_temp.read();
            Data::battery_voltage = voltage.read_voltage();
            Data::battery_percentage = voltage.read_percentage();
        }
        void send_data() {
            // {tmp[0]vlt[0]pct[0]}
            char buffer[STRING_LIMIT];
            using namespace Code;
            snprintf(
                buffer,
                sizeof(buffer),
                "%s%s%s%0.2f%s%s%s%0.2f%s%s%s%0.2f%s%s\n",
                
                Delimiter::start,

                Data::key[Data::Index::internal_temp],
                Delimiter::v_start,
                Data::temp,
                Delimiter::v_end,
                
                Data::key[Data::Index::battery_voltage],
                Delimiter::v_start,
                Data::battery_voltage,
                Delimiter::v_end,

                Data::key[Data::Index::battery_percentage],
                Delimiter::v_start,
                Data::battery_percentage,
                Delimiter::v_end,

                Delimiter::end
            );

            computer.write(buffer);
        }
        void read_and_send_data(){
            read_data();
            send_data();
        }
        void send_states(){
            // {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}
            // Format later if needed, output just for debug now and not processed by computer
            Serial.println("br: " + String(OutputStates::brake) + 
                           " rv: " + String(OutputStates::reverse) + 
                           " srv: " + String(OutputStates::s_reverse) + 
                           " su: " + String(OutputStates::shift_up) + 
                           " sp: " + String(OutputStates::speed_) + 
                           " ssp: " + String(OutputStates::s_speed) + 
                           " fan: " + String(OutputStates::f_speed));
        }
        void timeout_error(){
            reset();
            computer.write("Vehicle reset due to input timeout.\n");
        }
        void execute_command_as_string(uint8_t code, const char* val){
            if(code == Command::Index::brake) {
                set_brake(atoi(val));
            } else if(code == Command::Index::reverse) {
                set_direction(atoi(val));
            } else if(code == Command::Index::steering_reverse) {
                set_s_direction(atoi(val));
            } else if(code == Command::Index::shift_up) {
                set_shift(atoi(val));
            } else if(code == Command::Index::speed) {
                set_speed(atoi(val));
            } else if(code == Command::Index::steering_speed) {
                set_s_speed(atoi(val));
            } else if(code == Command::Index::fan) {
                set_f_speed(atoi(val));
            }
        }
    private:
        // Vehicle objects
        namespace OutputStates::{
            Relay brake;
            Relay reverse_1;
            Relay reverse_2;
            Relay s_reverse_1;
            Relay s_reverse_2;
            Relay shift_1;
            Relay shift_2;
            PWM speed;
            PWM s_speed;
            PWM fan;
        };
        logDivider internal_temp;
        batteryMonitor voltage;
        fourDigitDisplay display;

        char[STRING_LIMIT] current_command;
    
        void update_outputs(){
            fan.set(OutputStates::f_speed);
            brake_relay.set(!OutputStates::brake);
            reverse_1_relay.set(OutputStates::reverse);
            reverse_2_relay.set(OutputStates::reverse);
            s_reverse_1_relay.set(OutputStates::s_reverse);
            s_reverse_2_relay.set(OutputStates::s_reverse);
            shift_1_relay.set(OutputStates::shift_up);
            shift_2_relay.set(OutputStates::shift_up);
            speed_.set_power(OutputStates::speed_);
            s_speed.set_power(OutputStates::s_speed);
        }

        void run_input(){
            uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
            char tmp_code[16];
            char tmp_data16];
            uint16_t end_index = strlen(input);
            uint16_t index = 0;
            uint8_t data_index = 0;
            uint8_t code_index = 0;
            if(input[index] == '{'){					// look for start charcter
                while(index <= end_index){				// end if strlen exceed
                    if(input[index] == '}'){ 			// break if end characther
                        break;
                    } else {
                        // get the Data::packet designator
                // First clear temp Data::buffer
                    memset(tmp_code, 0, tmp_len);
                    memset(tmp_data 0, tmp_len);
                        code_index = 0;				// go to start of Data::buffer
                        while(true){				// until Data::encountered
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
                        if(input[index] == '['){		// find Data::charchter
                            Data::index = 0;
                            while(true){					// enter Data::loop	
                                index++;
                                if(input[index] == ']'){	// break if end Data::character
                                    tmp_dataData::index] = '\0';
                                    break;
                                } else {
                                    tmp_dataData::index] = input[index];
                                    Data::index++;
                                }
                            }
                        }
                        // run command with data
                        uint8_t code_index = 0;
                        while(code_index <= command.number_of_commands){
                            if(strcmp(Code::commands[code_index].code, tmp_code) == 0){
                                execute_command_as_string(code_index, tmp_data;
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