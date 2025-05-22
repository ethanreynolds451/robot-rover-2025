#ifndef DEFINITIONS_h
#define DEFINITIONS_h

uint8_t input_timeout = 1000;	// If no command recieved for interval, cut all motors
uint16_t baud_rate = 9600;
uint8_t string_limit = 255;

class Code {
public:
	static constexpr char brake = "br";
	static constexpr char reverse = "rv";
	static constexpr char s_reverse = "srv";
	static constexpr char shift_up = "su";
	static constexpr char speed = "sp";
	static constexpr char s_speed = "ssp";
}

class Pin {
public:
	//Digital
	static constexpr uint8_t brake = 12;
	static constexpr uint8_t reverse_1 = 2;
	static constexpr uint8_t reverse_2 = 4;
	static constexpr uint8_t s_reverse_1 = 5;
	static constexpr uint8_t s_reverse_2 = 6;
	static constexpr uint8_t shift_1 = 7;
	static constexpr uint8_t shift_2 = 8;
	static constexpr uint8_t speed = 9;
	static constexpr uint8_t s_speed = 10;
	static constexpr uint8_t fan = 3;
	static constexpr uint8_t headlight = 11;
	//Analog
	static constexpr uint8_t sda = A4;
	static constexpr uint8_t scl = A5;
}

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
	bool isClosed(){
		return closed;
	}
	bool isOpen(){
		return !closed;
	}
private:
	uint8_t pin;
	bool closed = false;
}

class PWM {
public:
	PWM(uint8_t pin_def) : pin(pin_def) {}
	void set_power(power){
		duty_cycle = power;
		analogWrite(pin, duty_cycle);
	}
	void stop(){
		analogWrite(pin, 0);
	}
	void start(){
		analogWrite(pin, duty_cycle);
	}
	uint8_t get_power(){
		return duty_cycle;
	}
private:
	uint8_t pin;
	uint8_t duty_cycle;
}

class Time {
public:
    Time(unsigned long x) : interval(x) {} // Constructor with member initializer list
    bool passed() {
        return wait(interval);
    }
	void reset() {
		currentmillis = 0;
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

