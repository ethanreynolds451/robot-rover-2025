#ifndef DEFINITIONS_h
#define DEFINITIONS_h

static const long input_timeout = 30000;	// If no command recieved for interval, cut all motors
static const uint16_t baud_rate = 9600;
static const uint8_t string_limit = 255;
static const uint8_t pwm_min = 50;
static const uint8_t pwm_max = 200;
static const uint16_t loop_delay = 100;
static const uint16_t serial_delay = 50;

char input[string_limit];

class Pin {
public:
	//Digital
	static constexpr uint8_t brake = 2;
	static constexpr uint8_t reverse_1 = 4;
	static constexpr uint8_t reverse_2 = 12;
	static constexpr uint8_t s_reverse_1 = 7;
	static constexpr uint8_t s_reverse_2 = 8;
	static constexpr uint8_t shift_1 = 5;
	static constexpr uint8_t shift_2 = 6;
	static constexpr uint8_t speed_ = 9;
	static constexpr uint8_t s_speed = 10;
	static constexpr uint8_t fan = 3;
	static constexpr uint8_t headlight = 11;
	//Analog
	static constexpr uint8_t SDA = A4;
	static constexpr uint8_t SCL = A5;
};

Pin pin;

class Address {
	public:
		static constexpr int pcf = 0x20;      // Default address
};

Address address; 

class Relay {
public:
	Relay(uint8_t pin_def) : pin(pin_def) {}
	void close(){
		digitalWrite(pin, HIGH);
		closed = true;
	}
	void open(){
		digitalWrite(pin, LOW);
		closed = false;
	}
  void set(bool value){
      if(value){
          close();
      } else if(!value){
          open();
      }
  }
  void flip(){
    if(isClosed()){
        open();
    } else if(isOpen()){
        close();
    }
  }
	bool isClosed(){
		return closed;
	}
	bool isOpen(){
		return !closed;
	}
private:
	uint8_t pin;
	bool closed = false;
};

Relay brake_relay(pin.brake);
Relay reverse_1_relay(pin.reverse_1);
Relay reverse_2_relay(pin.reverse_2);
Relay s_reverse_1_relay(pin.s_reverse_1);
Relay s_reverse_2_relay(pin.s_reverse_2);
Relay shift_1_relay(pin.shift_1);
Relay shift_2_relay(pin.shift_2);

class PWM {
public:
	PWM(uint8_t pin_def) : pin(pin_def) {}
	void stop(){
		analogWrite(pin, 0);
	}
	void start(){
		analogWrite(pin, duty_cycle);
	}
  void set(uint8_t power){
      duty_cycle = power;
      start();
  }
	uint8_t get_power(){
		return duty_cycle;
	}
private:
	uint8_t pin;
	uint8_t duty_cycle;
};

PWM speed_(pin.speed_);
PWM s_speed(pin.s_speed);

class Control {
    public:
        bool brake = false;			//br
        bool reverse = false;		//rv
        bool s_reverse = false;		//srv
        bool shift_up = false;		//su
        uint8_t speed_ = 0;			//sp
        uint8_t s_speed = 0;		//ssp
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
        void set_defaults(){
            bool brake = false;			//br
            bool reverse = false;		//rv
            bool s_reverse = false;		//srv
            bool shift_up = false;		//su
            uint8_t speed_ = 0;			//sp
            uint8_t s_speed = 0;		//ssp
        }
};

Control control;

class Command {
  private:
    struct _commands {
            uint8_t index;
            char code[4];
    };
  public:
    static const uint8_t number_of = 6;
    const _commands commands[number_of] = {
        {0, "br"},		// brake
        {1, "rv"},		// reverse
        {2, "srv"},		// steer reverse
        {3, "su"},		// shift up
        {4, "sp"},		// speed
        {5, "ssp"}		// steer speed
    };
    void execute(uint8_t code, const char* val){
            if(code == 0) {
                control.set_brake(atoi(val));
            } else if(code == 1) {
                control.set_direction(atoi(val));
            } else if(code == 2) {
                control.set_s_direction(atoi(val));
            } else if(code == 3) {
                control.set_shift(atoi(val));
            } else if(code == 4) {
                control.set_speed(atoi(val));
            } else if(code == 5) {
                control.set_s_speed(atoi(val));
            }
    }
};

Command command;

class Time {
public:
    Time(unsigned long x) : interval(x) {} // Constructor with member initializer list
    bool passed() {
        return wait(interval);
    }
  	void reset() {
  		previousmillis = millis();
  	}
private:
    bool wait(unsigned long time) {
        // return false if we're still "delaying", true if time ms has passed.
        // this should look a lot like "blink without delay"
        unsigned long currentmillis = millis();
        if (currentmillis - previousmillis >= time) {
            previousmillis = currentmillis;
            return true;
        }
        return false;
    }
    unsigned long interval; // Interval for this timer instance
    unsigned long previousmillis = 0; // Previous millis for this timer instance
};

#endif 
