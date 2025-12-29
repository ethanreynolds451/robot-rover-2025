#ifndef PWM_h
#define PWM_h

class PWM {
  public:
	PWM(uint8_t pin_def, uint8_t max_pwm, uint8_t min_pwm) : pin(pin_def) {}
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
	uint8_t max_pwm;
	uint8_t min_pwm;
	uint8_t duty_cycle;
};

#endif