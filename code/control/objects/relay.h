// Compiled successfully 2025-01-02

#ifndef RELAY_h
#define RELAY_h

#include <Arduino.h>

class Relay {
  public:
	Relay(uint8_t pin_def, bool nc_def = false) : pin(pin_def), nc(nc_def), closed(nc_def){
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);		// Always start in de-energized state
	}
	void close(){
		digitalWrite(pin, nc ? LOW : HIGH);
		closed = true;
	}
	void open(){
		digitalWrite(pin, nc ? HIGH : LOW);
		closed = false;
	}
	void set(bool state){
		if(state){
			close();
		} else {
			open();
		}
	}
	void flip(){
		set(!closed);
	}
	inline bool isClosed() const {
		return closed;
	}
	inline bool isOpen() const {
		return !closed;
	}
  private:
	uint8_t pin;
	bool nc;
	bool closed;
};

#endif