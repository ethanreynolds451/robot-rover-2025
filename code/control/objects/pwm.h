#ifndef PWM_h
#define PWM_h

#include "dependencies/libraries.h"

class PWM {
  public:
	PWM(uint8_t pin_def, uint8_t max_pwm_def=0, uint8_t min_pwm_def=255) 
		: pin(pin_def), max_pwm(max_pwm_def), min_pwm(min_pwm_def)  {}
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
	void set_power(uint8_t power){
		// Map 0-100% to min_pwm-max_pwm
		duty_cycle = map(power, 0, 100, min_pwm, max_pwm);
		start();
	}
	uint8_t get_power(){
		return duty_cycle;
	}
  private:
	uint8_t pin;
	uint8_t max_pwm;
	uint8_t min_pwm;
	uint8_t duty_cycle;
};

#endif