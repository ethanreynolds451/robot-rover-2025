#ifndef DEFINITIONS_h
#define DEFINITIONS_h

static const long baud_rate = 115200;
static const uint16_t loop_delay = 10;
static const uint8_t string_limit = 64;
static const uint8_t number_of_HCSR04 = 6;

char output[string_limit];

class Pin {
public:
  // Ultrasonic Sensors
  static constexpr uint8_t HCSR04_t = 5;   // Only one trig pin
  static constexpr uint8_t HCSR04_1 = 6;
  static constexpr uint8_t HCSR04_2 = 7;
  static constexpr uint8_t HCSR04_3 = 8;
  static constexpr uint8_t HCSR04_4 = 9;
  static constexpr uint8_t HCSR04_5 = A0;
  static constexpr uint8_t HCSR04_6 = A1;
  // Potentiometers
  static constexpr uint8_t steer_position = A5;
  // Signal
  static constexpr uint8_t TX = 2;
  static constexpr uint8_t RX = 3;
  static constexpr uint8_t SDA = A4;
  static constexpr uint8_t SCL = A5;
  // SD Card
  static constexpr uint8_t MISO = 12;
  static constexpr uint8_t MOSI = 11;
  static constexpr uint8_t SCK = 13;
  static constexpr uint8_t CS = 10;
};

Pin pin;

class Potentiometer {
  public:
    Relay(uint8_t pin_def, uint16_t max_def, uint16_t min_def, float range_def, uint16_t center_def) : pin(pin_def), min(min_def), max(max_def), range(range_def), center(center_def) {}
    uint16_t get_value(){
      return analogRead(pin);
    }
    uint8_t get_percent(){
      return 100*(1/1023);
    }
    uint16_t get_degrees(){
      return range*360*(1/1023);
    }
    void set_center(){
      cenetr = get_value();
    }
    void set_center(uint16_t center_def){
      center = center_def;
    }
  private:
    uint8_t pin;
    uint16_t min = 0;
    unit16_t max = 1023;
    unit16_t center = 512;
    float range = 0.75;
};



class Sensor {
public:
  // Create instance of HCSR04 array using predefined class
  HCSR04 ultrasonic(pin.HCSR04_t, new int[number_of_HCSR04]{pin.HCSR04_1, pin.HCSR04_2, pin.HCSR04_3, pin.HCSR04_4, pin.HCSR04_5, pin.HCSR04_6}, number_of_HCSR04);
  // Steering potentiometer
  Potentiometer steer_position(pin.steer_position);
  // GPS module
  // Array of LOF sensors
  // Two gyroscopes
  // Magnetometer                                                         
  // IR sensor                                                          

                                                            
  char* read(){
    return "something";   
  }
};

Sensor sensor;

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

Time send(send_delay);