#ifndef VEHICLE_h
#define VEHICLE_h

#include "vehicleDefinitions/vehicleDefinitions.h"
#include "vehicleCommunications/vehicleCommunications.h"
#include "vehicleDisplay/vehicleDisplay.h"
#include "vehicleMotorControl/vehicleMotorControl.h"
#include "vehicleSensors/vehicleSensors.h"

class Vehicle {
    public:
        // Setup functions
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
                speed_pwm(Pin::speed),
                s_speed_pwm(Pin::s_speed),
                fan_pwm(Pin::fan, 100, 255),
                internal_temp(Pin::thermistor, 30, 125),
                voltage(Pin::battery_monitor, BATTERY_VOLTAGE_SLOPE, 0, BATTERY_TYPE),
                display(Address::pcf, Pin::digit_1, Pin::digit_2, Pin::digit_3, Pin::digit_4),
                data(STRING_LIMIT, STRING_LIMIT)
            {}
        void begin(){
            // Pinmodes are already set within each class constructor or inirializer
            reset_control();            // Ensure vehicle is set to default state
            computer.begin();   // Start serial communication with onboard computer
            display.begin();    // Start display (PCF8575 with Wire I2C)
        }   

        // Command interface functions     
        bool get_command(){
            computer.read();
            if (computer.is_command()) {
                 // This only checks the start delimiter, use more rigerous data integrity checks later
                 computer.get_into(current_command, STRING_LIMIT);
                 return true;
            }
            return false; 
        }

        // Returns the error code from the command parser
        uint8_t get_and_extract_command(){
            if(get_command()){
                // Reset the current error index
                this->error_index = 0; 
                // Extract command into input buffer, use error index to track failure location if applicable
                return data.input.extract(this->current_command, this->error_index);
            }
        }

        // This should be the only command interface function used externally in deployment
        // Returns true if there was no error at any part of the process
        bool get_and_run_command(){
            // Save the error for future reference 
            this->command_error = get_and_extract_command();
            if (this->command_error == dataIn::extraction_errors::SUCCESS){
                // May add better error management here in the futrue
                if (data.input.validate_and_set()){
                    update_outputs();
                    return true;
                }
            }
            return false;
        }

        // Direct setters and getters to access individual states and data values
        void set_brake(bool state){
            data.input.set_brake(state);
            if(data.input.validate_and_set()){
                update_outputs();
            }   
        }
        void set_direction(bool state){
            data.input.set_reverse(state);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void set_shift(bool state){
            data.input.set_shift_up(state);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void set_speed(uint8_t value){
            data.input.set_speed(value);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void set_s_direction(bool state){
            data.input.set_s_reverse(state);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void set_s_speed(uint8_t value){
            data.input.set_s_speed(value);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void set_f_speed(uint8_t value){
            data.input.set_f_speed(value);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
        void reset_input(){
            data.input.reset_input();
            data.input.set_commands();     // no need to validate since they are defaults
        }
        void reset_control(){
            data.input.reset();
            update_outputs();
        }

        // Direct getters to retrieve individual states
        void get_brake(){
            return data.input.get_brake();
        }
        void get_direction(){
            return data.input.get_reverse();
        }
        void get_shift(){
            return data.input.get_shift_up();
        }
        uint8_t get_speed(){
            return data.input.get_speed();
        }
        bool get_s_direction(){
            return data.input.get_s_reverse();
        }
        uint8_t get_s_speed(){
            return data.input.get_s_speed();
        }
        uint8_t get_f_speed(){
            return data.input.get_f_speed();
        }

        float get_internal_temp(){
            return data.output.get_internal_temp();
        }
        float get_battery_voltage(){
            return data.output.get_battery_voltage();
        }
        float get_battery_percentage(){
            return data.output.get_battery_percentage();
        }

        // Sensor reader functions
        float read_internal_temp(){
            float temp = internal_temp.read(); 
            data.output.set_internal_temp(temp);
            return temp;
        }
        float read_battery_voltage(){
            float volts = voltage.read_voltage();
            data.output.set_battery_voltage(volts);
            return volts;
        }
        float read_battery_percentage(){
            float percent = voltage.read_percentage();
            data.output.set_battery_percentage(percent);
            return percent;
        }

        // Vehicle functions for control loop
        void set_fan_from_temp(){
            uint16_t temp = internal_temp.read();
            if(temp < MIN_FAN_TEMP){
                data.input.set_f_speed(0);
            } else if(temp > MAX_FAN_TEMP){
                data.input.set_f_speed(100);
            } else {
                uint8_t speed = map(temp, MIN_FAN_TEMP, MAX_FAN_TEMP, 0, 100);
                data.input.set_f_speed(speed);
            }
            update_outputs();
        }

        void display_voltage(){
            float volts = voltage.read_voltage();
            char buffer[64];
            // Display voltage on serial for debug
                snprintf(buffer, sizeof(buffer), "Battery Voltage: %.2f V\n", volts);
                computer.write(buffer);
            display.print_decimal(volts);
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
            read_internal_temp();
            read_battery_voltage();
            read_battery_percentage();
        }
        void send_data() {
	        // Get the data into a var called buffer using data functions********
            char* buffer = data.output.get_string();
            computer.write(buffer);
        }
        void read_and_send_data(){
            read_data();
            send_data();
        }
        void send_states(){
            char* buffer = data.input.get_string();
            computer.write(buffer);
        }
        void timeout_error(){
            reset_control();
            computer.write("Vehicle reset due to input timeout.\n");
        }
        
        // This one calls the vehicle specific functions
        void set_command_as_string(uint8_t code, const char* val){
            data.input.set(code, val);
            if(data.input.validate_and_set()){
                update_outputs();
            }
        }
    
    private:
        // Vehicle objects
        Relay brake_relay;
        Relay reverse_1_relay;
        Relay reverse_2_relay;
        Relay s_reverse_1_relay;
        Relay s_reverse_2_relay;
        Relay shift_1_relay;
        Relay shift_2_relay;
        PWM speed_pwm;
        PWM s_speed_pwm;
        PWM fan_pwm;
        logDivider internal_temp;
        batteryMonitor voltage;
        fourDigitDisplayPCF display;

        dataManager data; 

        // Buffer for command processing
        char current_command[STRING_LIMIT];
        uint8_t command_error = 0; 
        size_t error_index = 0; 
    
        void update_outputs(){
            fan_pwm.set(data.input.get_f_speed());
            brake_relay.set(!data.input.get_brake());
            reverse_1_relay.set(data.input.get_reverse());
            reverse_2_relay.set(data.input.get_reverse());
            s_reverse_1_relay.set(data.input.get_s_reverse());
            s_reverse_2_relay.set(data.input.get_s_reverse());
            shift_1_relay.set(data.input.get_shift_up());
            shift_2_relay.set(data.input.get_shift_up());
            speed_pwm.set_power(data.input.get_speed());
            s_speed_pwm.set_power(data.input.get_s_speed());
        }
};  

#endif