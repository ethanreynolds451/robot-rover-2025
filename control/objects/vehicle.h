#ifndef VEHICLE_h
#define VEHICLE_h

void setup_function(){
    Serial.begin(baud_rate);
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

void check_temp(){
  uint16_t temp = analogRead(pin.thermistor);
  // Added diode to reduce noise, adjusted offset from -95 to -125
  temp = 30*log(temp) - 125;
  // Serial.println("Temp: " + String(temp));	// Debug line
  if(temp < 25){
 	control.f_speed = 0;
  } else if(temp > 50){
 	control.f_speed = 100;
  } else {
 	control.f_speed = map(temp, 25, 50, 0, 100);
  }
}

void update_control(){
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

void reset_vehicle(){
  control.set_defaults();
  control.set_brake(true);
  update_control();
}

void input_error(){
  reset_vehicle();
  Serial.println("Input timeout, vehicle reset");
}

class Vehicle {
  public:
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


    bool brake = true;			//br
    bool reverse = false;		//rv
    bool s_reverse = false;		//srv
    bool shift_up = false;		//su
    uint8_t speed_ = 0;			//sp
    uint8_t s_speed = 0;		//ssp
    uint8_t f_speed = 0;        //fan
    void set_brake(bool active){
        brake = active;
    }
    void set_direction(bool set_reverse){
        reverse = set_reverse;
    }
    void set_shift(bool set_series){
        shift_up = set_series;
    }
    void set_speed(uint8_t set_speed){
        speed_ = map(set_speed, 0, 100, pwm_min, pwm_max);
    }
    void set_s_direction(bool set_reverse){
        s_reverse = set_reverse;
    }
    void set_s_speed(uint8_t set_speed){
        s_speed = map(set_speed, 0, 100, pwm_min, pwm_max);
    }
    void set_f_speed(uint8_t set_speed){
        f_speed = map(set_speed, 0, 100, pwm_min, pwm_max);
    }
    void set_defaults(){
        brake = true;		
        reverse = false;		
        s_reverse = false;		
        shift_up = false;		
        speed_ = 0;		
        s_speed = 0;	
    }
    void execute(uint8_t code, const char* val){
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
};

    

#endif