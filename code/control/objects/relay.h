#ifndef RELAY_h
#define RELAY_h

#include "dependencies/libraries.h"

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

#endif