// Compiled successfully 2025-01-02

#ifndef PWM_h
#define PWM_h

#include <Arduino.h>

class PWM {
  public:
	PWM(uint8_t pin_def, uint8_t min_pwm_def=0, uint8_t max_pwm_def=255) 
		: pin(pin_def), min_pwm(min_pwm_def), max_pwm(max_pwm_def), duty_cycle(0), power(0), stopped(true) {
			pinMode(pin, OUTPUT);
			analogWrite(pin, duty_cycle);
		}
	void stop(){
		analogWrite(pin, 0);
		stopped = true;
	}
	inline void set(uint8_t duty){
		duty_cycle = duty;
		stopped = (duty_cycle == 0);
	}
	void set_power(uint8_t pwr){
		// Map 0-100% to min_pwm-max_pwm
		power = constrain(pwr, 0, 100);
		uint8_t pwm_value = static_cast<uint8_t>(map(power, 0, 100, min_pwm, max_pwm));
		set(pwm_value);
	}
	void run() {
    	analogWrite(pin, duty_cycle);  // use saved value
	}
	void run(uint8_t duty) {
		set(duty);                  // update and write
		run();
	}
	void run_power(uint8_t pwr){
		set_power(pwr);
		run();
	} 
	inline uint8_t get() const {
		return duty_cycle;
	}
	inline uint8_t get_power() const {
		return power;
	}
	inline bool is_stopped() const {
		return stopped;
	}
  private:
	uint8_t pin;
	uint8_t max_pwm;
	uint8_t min_pwm;
	uint8_t duty_cycle;
	uint8_t power; 
	bool stopped;
};

#endif