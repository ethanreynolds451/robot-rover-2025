#ifndef VEHICLE_h
#define VEHICLE_h

#include "vehicleCommunications/vehicleCommunications.h"
#include "vehicleDisplay/vehicleDisplay.h"
#include "vehcileMotorControl/vehicleMotorControl.h"
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
                parser(STRING_LIMIT)
            {}
        void begin(){
            // Pinmodes are already set within each class constructor or inirializer
            reset();            // Ensure vehicle is set to default state
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
                this->error_index = 0; 
                // Extract command into input buffer, use error index to track failure location if applicable
                return parser.extract_commands(OutputStates::input_buffer, this->current_command, this->error_index);
            }
        }

        // This should be the only command interface function used externally in deployment
        // Returns true if there was no error at any part of the process
        bool get_and_run_command(){
            // Save the error for future reference 
            this->command_error = get_and_extract_command();
            if (!this->command_error){
                // May add better error management here in the futrue
                if (OutputStates::validate_input()){
                    if (OutputStates::set_from_input()){
                        update_outputs();
                        return true;
                    }
                }
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
            return InputData::current.internal_temp;
        }
        float get_battery_voltage(){
            return InputData::current.battery_voltage;
        }
        float get_battery_percentage(){
            return InputData::current.battery_percentage;
        }

        // Sensor reader functions
        float read_internal_temp(){
            namespace D = InputData;
            D::current.internal_temp = internal_temp.read();
            return D::current.internal_temp;
        }
        float read_battery_voltage(){
            namespace D = InputData;
            D::current.battery_voltage = voltage.read_voltage();
            return D::current.battery_voltage;
        }
        float read_battery_percentage(){
            namespace D = InputData;
            D::current.battery_percentage = voltage.read_percentage();
            return D::current.battery_percentage;
        }

        // Vehicle functions for control loop
        void set_fan_from_temp(){
            uint16_t temp = internal_temp.read();
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
            namespace D = InputData;
            D::current.internal_temp = internal_temp.read();
            D::current.battery_voltage = voltage.read_voltage();
            D::current.battery_percentage = voltage.read_percentage();
        }
        void send_data() {
            // {tmp[0]vlt[0]pct[0]}
            char buffer[STRING_LIMIT];
            namespace C = Code::Data;
            namespace D = Code::Delimiter;
            namespace V = InputData;
            snprintf(
                buffer,
                sizeof(buffer),
                "%s%s%s%0.2f%s%s%s%0.2f%s%s%s%0.2f%s%s\n",
                
                D::start,

                C::str[C::Index::internal_temp],
                D::v_start,
                V::current.internal_temp,
                D::v_end,
                
                C::str[C::Index::battery_voltage],
                D::v_start,
                V::current.battery_voltage,
                D::v_end,

                C::str[C::Index::battery_percentage],
                D::v_start,
                V::current.battery_percentage,
                D::v_end,

                D::end
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
        // This one calls the vehicle specific functions
        void set_command_as_string(uint8_t code, const char* val){
            namespace I = Code::Command::Index;
            if(code == I::brake) {
                set_brake(atoi(val));
            } else if(code == I::reverse) {
                set_direction(atoi(val));
            } else if(code == I::steering_reverse) {
                set_s_direction(atoi(val));
            } else if(code == I::shift_up) {
                set_shift(atoi(val));
            } else if(code == I::speed) {
                set_speed(atoi(val));
            } else if(code == I::steering_speed) {
                set_s_speed(atoi(val));
            } else if(code == I::fan) {
                set_f_speed(atoi(val));
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

        commandParser parser; 

        // Buffer for command processing
        char current_command[STRING_LIMIT];
        uint8_t command_error = 0; 
        size_t error_index = 0; 
    
        void update_outputs(){
            fan_pwm.set(OutputStates::current.f_speed);
            brake_relay.set(!OutputStates::current.brake);
            reverse_1_relay.set(OutputStates::current.reverse);
            reverse_2_relay.set(OutputStates::current.reverse);
            s_reverse_1_relay.set(OutputStates::current.s_reverse);
            s_reverse_2_relay.set(OutputStates::current.s_reverse);
            shift_1_relay.set(OutputStates::current.shift_up);
            shift_2_relay.set(OutputStates::current.shift_up);
            speed_pwm.set_power(OutputStates::current.speed);
            s_speed_pwm.set_power(OutputStates::current.s_speed);
        }
};  

#endif