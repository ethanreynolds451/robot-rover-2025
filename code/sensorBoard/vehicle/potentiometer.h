#ifndef POTENTIOMETER_h
#define POTENTIOMETER_h

class Potentiometer {
  public:
    Potentiometer(uint8_t pin_def, uint16_t max_def, uint16_t min_def, float range_def, uint16_t center_def) : pin(pin_def), min_val(min_def), max_val(max_def), range(range_def), center(center_def) {}
    uint16_t get_value(){
      return analogRead(pin);
    }
    uint8_t get_percent(){
      return (get_value() * 100) / 1023;
    }
    uint16_t get_degrees(){
      return static_cast<uint16_t>(range * 360.0 * get_value() / 1023.0);
    }
    void set_center(){
      center = get_value();
    }
    void set_center(uint16_t center_def){
      center = center_def;
    }
  private:
    uint8_t pin;
    uint16_t min_val = 0;
    uint16_t max_val = 1023;
    uint16_t center = 512;
    float range = 0.75;
};

#endif