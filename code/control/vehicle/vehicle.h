#ifndef VEHICLE_h
#define VEHICLE_h

#include "components.h"

class Vehicle {
    public:
        Vehicle(baud_rate) 
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
        // Gotten to here in rewrite
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
            output_states.speed_ = set_speed;
            update_outputs();
        }
        void set_s_direction(bool set_reverse){
            output_states.s_reverse = set_reverse;
            update_outputs();
        }
        void set_s_speed(uint8_t set_speed){
            output_states.s_speed = set_speed;
            update_outputs();
        }
        void set_f_speed(uint8_t set_speed){
            output_states.f_speed = set_speed;
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
            temp = internal_temp.read();
            battery_voltage = voltage.read_voltage();
            battery_percentage = voltage.read_percentage();
        }
        void send_data(){
            // {tmp[0]vlt[0]pct[0]}
            char buffer[STRING_LIMIT];
            sprintf(buffer, "{Code::data[0].code}[%0.2f]{Code::data[1].code}[%0.2f]{Code::data[2].code}[%0.2f]\n",
                    data.temp,
                    data.battery_voltage,
                    data.battery_percentage);
            computer.write(buffer);
        }
        void read_and_send_data(){
            read_data();
            send_data();
        }
        void send_states(){
            // {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}
            // Format later if needed, output just for debug now and not processed by computer
            Serial.println("br: " + String(output_states.brake) + 
                           " rv: " + String(output_states.reverse) + 
                           " srv: " + String(output_states.s_reverse) + 
                           " su: " + String(output_states.shift_up) + 
                           " sp: " + String(output_states.speed_) + 
                           " ssp: " + String(output_states.s_speed) + 
                           " fan: " + String(output_states.f_speed));
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
        SerialControl computer;
        namespace Control {
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
        }
    
        logDivider internal_temp;
        batteryMonitor voltage;
        fourDigitDisplay display;

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
        namespace data {
            float temp; 
            float battery_voltage;
            float battery_percentage; 
        }
        char[STRING_LIMIT] current_command;
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
            fan.set(control.f_speed);
            brake_relay.set(!control.brake);
            reverse_1_relay.set(control.reverse);
            reverse_2_relay.set(control.reverse);
            s_reverse_1_relay.set(control.s_reverse);
            s_reverse_2_relay.set(control.s_reverse);
            shift_1_relay.set(control.shift_up);
            shift_2_relay.set(control.shift_up);
            speed_.set_power(control.speed_);
            s_speed.set_power(control.s_speed);
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
                        while(code_index <= command.number_of_commands){
                            if(strcmp(Code::commands[code_index].code, tmp_code) == 0){
                                execute_command_as_string(code_index, tmp_data);
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