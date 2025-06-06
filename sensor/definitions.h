#ifndef DEFINITIONS_h
#define DEFINITIONS_h

static const long baud_rate = 115200;
static const uint16_t loop_interval = 10;
static const uint16_t send_interval = 25;
static const uint8_t string_limit = 64;

static const uint8_t number_of_HCSR04 = 6;
static const uint8_t number_of_lof = 4;
static const uint8_t number_of_qmc = 1;
static const uint8_t number_of_mpu = 2;

class Pin {
public:
  static constexpr uint8_t HCSR04[number_of_HCSR04 + 1] = {5, 6, 7, 8, 9, A0, A1};   // 0 is trig pin
  static constexpr uint8_t x_shut[number_of_lof] = {0, 1, 2, 3}; // These are PCF pins
  static constexpr uint8_t steer_position = A5;
  static constexpr uint8_t TX = 2;
  static constexpr uint8_t RX = 3;
  static constexpr uint8_t IR = 4;
  static constexpr uint8_t SDA = A4;
  static constexpr uint8_t SCL = A5;
  static constexpr uint8_t MISO = 12;
  static constexpr uint8_t MOSI = 11;
  static constexpr uint8_t SCK = 13;
  static constexpr uint8_t CS = 10;
};

class Address {
public:
  static constexpr uint8_t VL53L0X[number_of_lof] = {0x29, 0x30, 0x31, 0x32}; // First default, rest must be programmed ON EACH POWER CYCLE IS VOLATILE
  static constexpr uint8_t QMC[number_of_qmc] = {0x42};           // Default
  static constexpr uint8_t MPU[number_of_mpu] = {0x68, 0x69};     // First default, second pulled up to 5v
  static constexpr uint8_t PCF = 0x20;     // Default according to ChatGPT, check specific model
};


class Potentiometer {
  public:
    Potentiometer(uint8_t pin_def, uint16_t max_def, uint16_t min_def, float range_def, uint16_t center_def) : pin(pin_def), min_val(min_def), max_val(max_def), range(range_def), center(center_def) {}
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

// Composite class to access all sensors, includes all relevant sensor objects
class Sensor {
public:
  Sensor(); // For constructor (needed to initialize arrays of sensors)
  HCSR04 ultrasonic;                      // Allows for direct definition of array
  VL53L0X* lof[number_of_lof];        // Pointer to array of sensor, MUST USE POINTER NOT DOT NOTATION
  Potentiometer steer_position;
  Adafruit_MPU6050* mpu[number_of_mpu];
  QMC5883LCompass* qmc[number_of_qmc];
  SoftwareSerial gps;                    // Uses software serial to communicate
  void begin() {
    for(int i = 0; i < number_of_lof; i++){
        lof[i] = new VL53L0X();  
        // Code to assign each to its respective address, 10ms delay blocking 
        for(int i = 0; i <= number_of_lof; i++){
          while(true){
            digitalWrite(Pin::xshut[i], HIGH);
            // Set the i2c address
            
          }
        }
        lof[i]->init(); 
        lof[i]->setAddress(address.VL53L0X[i]);
        lof[i]->startContinuous();
    }
    IrReceiver.begin(Pin::IR);
  }
  class Values {
   public:
    uint16_t ultrasonic[number_of_HCSR04];
    uint16_t lof[number_of_lof];
    unsigned long ir;
    struct vector3_values {
      int16_t x;
      int16_t y;
      int16_t z;
    };
    vector3_values qmc[number_of_qmc];;
    struct mpu_values {
      vector3_values accel;
      vector3_values gyro;
    };
    mpu_values mpu[number_of_mpu];
    struct gps_values {
      double lat;
      double lng;
      double alt;
      double spd;   // km per hour
      double deg;   // bearing, compare with magnetometer
      bool fix;   // Valid gps fix
    };
    gps_values gps;
  };

  Values value;

  void read(const String& sensor){

  }
  void read_all(){
    read_ultrasonic(0); 
    read_lof(0); 
  }
private:
  void read_ultrasonic(uint8_t index) {
    if (index == 0){
      for (int i = 0; i < number_of_HCSR04; i++) {
        value.ultrasonic[i] = ultrasonic.dist(i);
      }
    } else if (index <= number_of_HCSR04) {
      value.ultrasonic[index - 1] = ultrasonic.dist(index - 1);
    }
  }
  void read_lof (uint8_t index) {
    if (index == 0){
      for (int i = 0; i < number_of_lof; i++) {
        value.lof[i] = 
      }
    } else if (index <= number_of_HCSR04) {
      value.ultrasonic[index - 1] = ultrasonic.dist(index - 1);
    }
  }
  void read_steering () {

  }
  void read_mpu(uint8_t index){

  }
  void read_qmc(uint8_t index){

  }
  void read_gps(){

  }
  void read_ir(){

  }
};

Sensor::Sensor()
  : ultrasonic(Pin::HCSR04[0], new int[number_of_HCSR04]{Pin::HCSR04[1], Pin::HCSR04[2], Pin::HCSR04[3], Pin::HCSR04[4], Pin::HCSR04[5], Pin::HCSR04[6]}, number_of_HCSR04),
    steer_position(Pin::steer_position, 1023, 0, 0.75, 512),
    gps(Pin::TX, Pin::RX) {}

Sensor sensor;

class Data {
  private:
    struct packets {
          uint8_t index;
          char code[4];
    };
  public:
    char output[string_limit];
    static const uint8_t number_of = 7;
    const packets code[number_of] = {
        {0, "hc"},		// brake
        {1, "vl"},		// reverse
        {2, "str"},		// steer reverse
        {3, "mpu"},		// shift up
        {4, "qmc"},		// speed
        {5, "gps"},		// steer speed
        {6, "ir"}    // fan speed
    };
    char* get(){
      memset(output, 0, string_limit);
      //sensor.value.ultrasonic[index];
      //sensor.value.lof[index];
      strcpy(output, "Hello World");
      return output;
    }
};

Data data;

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

Time loop_delay(loop_interval);
Time send_delay(send_interval);

#endif

// Other GPS vars, not needed
//      int hour;
//      int min;
//      int sec;
//      int day;
//      int month;
//      int year;
//      int satelites;
//      int percision;
