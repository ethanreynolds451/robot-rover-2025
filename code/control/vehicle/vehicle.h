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
                speed(Pin::speed),
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

        // Command functions     
        void get_command(){
            computer.read();
            if computer.is_command() {
                 // This only checks the start delimiter, use more rigerous data integrity checks later
                 computer.get_into(current_command, STRING_LIMIT);
                 return true;
            }
            return false; 
        }
        void get_and_run_command(){
            if(get_command()){
                run_input(current_command);
                return true;
            }
            return false;
        }

        // Direct setters and getters to access individual states and data values
        void set_brake(bool active){
            OutputStates::current.brake = active;
            update_outputs();
        }
        void set_direction(bool set_reverse){
            OutputStates::current.reverse = set_reverse;
            update_outputs();
        }
        void set_shift(bool set_series){
            OutputStates::current.shift_up = set_series;
            update_outputs();
        }
        void set_speed(uint8_t set_speed){
            OutputStates::current.speed = set_speed;
            update_outputs();
        }
        void set_s_direction(bool set_reverse){
            OutputStates::current.s_reverse = set_reverse;
            update_outputs();
        }
        void set_s_speed(uint8_t set_speed){
            OutputStates::current.s_speed = set_speed;
            update_outputs();
        }
        void set_f_speed(uint8_t set_speed){
            OutputStates::current.f_speed = set_speed;
            update_outputs();
        }
        void reset(){
            OutputStates::reset();
            update_outputs();
        }

        // Direct getters to retrieve individual states
        void get_brake(){
            return OutputStates::current.brake;
        }
        void get_direction(){
            return OutputStates::current.reverse;
        }
        void get_shift(){
            return OutputStates::current.shift_up;
        }
        uint8_t get_speed(){
            return OutputStates::current.speed;
        }
        bool get_s_direction(){
            return OutputStates::current.s_reverse;
        }
        uint8_t get_s_speed(){
            return OutputStates::current.s_speed;
        }
        uint8_t get_f_speed(){
            return OutputStates::current.f_speed;
        }
        float get_internal_temp(){
            return Data::current.internal_temp;
        }
        float get_battery_voltage(){
            return Data::current.battery_voltage;
        }
        float get_battery_percentage(){
            return Data::current.battery_percentage;
        }

        // Sensor reader functions
        float read_internal_temp(){
            Data::current.internal_temp = internal_temp.read();
            return Data::current.internal_temp;
        }
        float read_battery_voltage(){
            Data::current.battery_voltage = voltage.read_voltage();
            return Data::current.battery_voltage;
        }
        float read_battery_percentage(){
            Data::current.battery_percentage = voltage.read_percentage();
            return Data::current.battery_percentage;
        }

        // Vehicle functions for control loop
        void set_fan_from_temp(){
            temp = internal_temp.read();
            if(temp < MIN_FAN_TEMP){
                OutputStates::current.f_speed = 0;
            } else if(temp > MAX_FAN_TEMP){
                OutputStates::current.f_speed = 100;
            } else {
                OutputStates::current.f_speed = map(temp, MIN_FAN_TEMP, MAX_FAN_TEMP, 0, 100);
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
            Data::current.internal_temp = internal_temp.read();
            Data::current.battery_voltage = voltage.read_voltage();
            Data::current.battery_percentage = voltage.read_percentage();
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

                Data::current.key[Data::current.Index::internal_temp],
                Delimiter::v_start,
                Data::current.temp,
                Delimiter::v_end,
                
                Data::current.key[Data::current.Index::battery_voltage],
                Delimiter::v_start,
                Data::current.battery_voltage,
                Delimiter::v_end,

                Data::current.key[Data::current.Index::battery_percentage],
                Delimiter::v_start,
                Data::current.battery_percentage,
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
            Serial.println("br: " + String(OutputStates::current.brake) + 
                           " rv: " + String(OutputStates::current.reverse) + 
                           " srv: " + String(OutputStates::current.s_reverse) + 
                           " su: " + String(OutputStates::current.shift_up) + 
                           " sp: " + String(OutputStates::current.speed) + 
                           " ssp: " + String(OutputStates::current.s_speed) + 
                           " fan: " + String(OutputStates::current.f_speed));
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
        };
        logDivider internal_temp;
        batteryMonitor voltage;
        fourDigitDisplay display;

        char[STRING_LIMIT] current_command;
    
        void update_outputs(){
            fan.set(OutputStates::current.f_speed);
            brake_relay.set(!OutputStates::current.brake);
            reverse_1_relay.set(OutputStates::current.reverse);
            reverse_2_relay.set(OutputStates::current.reverse);
            s_reverse_1_relay.set(OutputStates::current.s_reverse);
            s_reverse_2_relay.set(OutputStates::current.s_reverse);
            shift_1_relay.set(OutputStates::current.shift_up);
            shift_2_relay.set(OutputStates::current.shift_up);
            speed.set_power(OutputStates::current.speed);
            s_speed.set_power(OutputStates::current.s_speed);
        }

        bool run_input(char* input_string){                                               // Returns true if all commands read successfully
            char input[STRING_LIMIT];
            strcpy(input, input_string);
            static constexpr uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
            char tmp_delimiter[tmp_len];
            char tmp_code[tmp_len];
            char tmp_data[tmp_len];
            uint16_t end_index = strlen(input);
            uint16_t index = 0;
            uint8_t data_index = 0;
            uint8_t code_index = 0;
            using namespace Code;

            memset(tmp_delimiter, 0, tmp_len);
            strcpy(tmp_delimiter, Delimiter::start);

            // Step 1: Check for the start delimiter (iterate if multiple characters)
            for(int i = 0; i < strlen(Delimiter::start); i++){
                if(input[index] == Delimiter::start[i]){		
                    index++;	
                } else {
                    return 0;					
                }		
            }
            // This will advance index to the character after the start delimiter

            // Step 2: Check for the end delimiter
            memset(tmp_delimiter, 0, tmp_len);
            strcpy(tmp_delimiter, Delimiter::start);
            unit8_t reverse_index = end_index;
            for(int i = strlen(tmp_delimiter); i > 0; i--){		// check from end to start
                if(input[reverse_index] == tmp_delimiter[i]){		
                    reverse_index--;	
                } else {
                    return 0;			
                }		
            }
            // This will advance reverse_index to the character before the end delimiter

            // The data to read can now be constrained between the start and end delimiters

            // Siep 3: Read commands and data between the delimiters
            while(index <= reverse_index){	

            // A) get command code
                memset(tmp_code, 0, tmp_len);
                memset(tmp_delimiter, 0, tmp_len);
                strcpy(tmp_delimiter, Delimiter::v_start);
                code_index = 0;				// go to start of data buffer
                while(true){				// until data encountered
                    if(isalpha(input[index]) && input[index] != tmp_delimiter[0]){
                        tmp_code[code_index] = input[index];	// read designator into tmp buffer
                        code_index++;                        // advance to next buffer character
                        index++;                             // advance to next input character
                    } else {
                        tmp_code[code_index] = '\0';       
                        break;	// If bad nonalpha or end char encounter
                    }
                }
                // This will leave off at the first character of the value delimiter

            // B) get the data 
        
                // Check the rest of the start delimiter (or just advance to the next char if single char delimiter)
                for(int i = 0; i < strlen(tmp_delimiter); i++){
                    if(input[index] == tmp_delimiter[i]){		
                        index++;	
                    } else {
                        return 0;					
                    }		
                }
                // This will advance index to the character after the value start delimiter

                // Reset buffers and prepare to read data
                memset(tmp_data 0, tmp_len);
                memset(tmp_delimiter, 0, tmp_len);
                strcpy(tmp_delimiter, Delimiter::v_end);

                // Read data until end delimiter
                data_index = 0;
                while(true){					  
                    if(input[index] != tmp_delimiter[0]){	
                        tmp_data[data_index] = input[index];
                        data_index++;               // advance to next buffer character 
                        index++;                    // advance to next input character
                    } else {
                        tmp_data[data_index] = '\0';
                        break;
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
                index++;          // Advance to next charachter in input

            }
            return 0;  // Return false if no end deimiter not read successfully
            
        }
};  

#endif