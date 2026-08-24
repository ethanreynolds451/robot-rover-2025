// This file is hardlinked and exists in both control and sensor

// Compiled successfully 2025-01-02

/*
  Timer class for non-blocking delays using millis()
*/

#ifndef TIMER_h
#define TIMER_h

#include <Arduino.h>      // Include Arduino library for millis() function

class Timer {
  public:
    Timer(unsigned long x) : interval(x) {}
    inline bool passed(){
      unsigned long currentmillis = millis();
          if (currentmillis - previousmillis >= interval) {
              previousmillis = currentmillis;
              return true;
          }
          return false;
    }
  	inline void reset() { 
      previousmillis = millis(); 
    }

  private:
    unsigned long interval; // Interval for this timer instance
    unsigned long previousmillis = 0; // Previous millis for this timer instance
};

#endif