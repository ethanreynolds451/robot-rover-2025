#ifndef DEFINITIONS_h
#define DEFINITIONS_h

static const long baudrate = 115200;
static const uint32_t gps_baudrate = 4800;
static const uint16_t serial_delay = 10;
static const uint16_t loop_interval = 10;
static const uint16_t send_interval = 25;
static const uint8_t string_limit = 64;

static const uint8_t number_of_HCSR04 = 6;
static const uint8_t number_of_lof = 4;
static const uint8_t number_of_qmc = 1;
static const uint8_t number_of_mpu = 2;

static const uint8_t sensor_retry = 3;

PCF8575 PCF(0x20);

namespace Pin {
  static constexpr uint8_t HCSR04[number_of_HCSR04 + 1] = {5, 6, 7, 8, 9, A0, A1};   // 0 is trig pin
  static constexpr uint8_t x_shut[number_of_lof] = {0, 1, 2, 3}; // These are PCF pins - mod for test
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

namespace Address {
  static constexpr uint8_t VL53L0X[number_of_lof] = {0x29, 0x30, 0x31, 0x32}; // First default, rest must be programmed ON EACH POWER CYCLE IS VOLATILE
  static constexpr uint8_t QMC[number_of_qmc] = {0x42};           // Default
  static constexpr uint8_t mpu[number_of_mpu] = {0x68, 0x69};     // First default, second pulled up to 5v
  static constexpr uint8_t PCF = 0x20;     // Default according to ChatGPT, check specific model
  bool detect(uint8_t address) {      // Thanks chat GPT, script to detect if i2c address is on bus, non-blocking and will not freze (hopefully)
    // Enable internal pull-ups on SDA and SCL pins
    pinMode(Pin::SDA, INPUT_PULLUP);
    pinMode(Pin::SCL, INPUT_PULLUP);
    // Small delay to let lines settle
    delay(10);
    // Check if lines are actually HIGH (pulled up)
    bool sda_high = digitalRead(Pin::SDA);
    bool scl_high = digitalRead(Pin::SCL);
    if (!sda_high || !scl_high) {
    return false; // Skip scanning, no proper bus setup
    }
    unsigned long start = millis();
    while (millis() - start < 100) { // 100 ms timeout
    Wire.beginTransmission(address);
    uint8_t result = Wire.endTransmission(true);
    if (result == 0) {
      return true;  // Device responded at this address
    }
    delay(5); // small delay before retrying
    }
    return false;  // No device responded
  }
};


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

// Composite class to access all sensors, includes all relevant sensor objects
class Sensor {
public:
  Sensor(); // For constructor (needed to initialize arrays of sensors)
  HCSR04 ultrasonic;                      // Allows for direct definition of array
  VL53L0X* lof[number_of_lof];        // Pointer to array of sensor, MUST USE POINTER NOT DOT NOTATION
  Potentiometer steer_position;
  Adafruit_mpu6050* mpu[number_of_mpu];
  QMC5883LCompass* qmc[number_of_qmc];
  TinyGPSPlus gps;
  SoftwareSerial gps_serial;                    // GPS uses software serial to communicate

  bool start_lof(){                                     // Still work in progress
    bool return_val = true;
    // Set the I2C addresses of the lof sensors
    for(int j = 0; j < number_of_lof; j++){
      PCF.write(Pin::x_shut[j], LOW);      // Deactivate all lof sensors
    }
    Serial.println("Checkpoint 1");
    for(int i = 0; i < number_of_lof; i++){
        lof[i] = new VL53L0X();                   // Create sensor object  
        PCF.write(Pin::x_shut[i], LOW);       // Activate the one to set address
        Serial.println("Checkpoint 1.1");
        delay(50);
        if (!address.detect(0x29)) {
          error.lof[i] = 1;   // address not found error
          return_val = false;
          continue;  // skip to the next sensor
        }
        Serial.println("Checkpoint 1.1.5");
        if (!lof[i]->init()) {
          return_val = false;
          error.lof[i] = 2;   // failed to initialize error
        } else {
          lof[i]->setAddress(Address::VL53L0X[i]);
          PCF.write(Pin::x_shut[i], LOW);   // Deactivate after setting
        }
        Serial.println("Checkpoint 1.2");
    }
    Serial.println("Checkpoint 2");
    for(int i = 0; i < number_of_lof; i++){
      PCF.write(Pin::x_shut[i], HIGH);      // Activate all lof sensors
      lof[i]->startContinuous();
    }
    delay(10);
    Serial.println("Checkpoint 3");
    for(int i = 0; i < number_of_lof; i++){
      lof[i]->startContinuous();
    }
    return return_val;
  }   // add address verification, retry to set address if didn't work, exit after n times

  bool start_mpu(){
    bool return_val = true;
    for(int i = 0; i < number_of_mpu; i++){
      mpu[i] = new Adafruit_MPU6050();
      if (!address.detect(address.mpu[i])) {
        error.mpu[i] = 1;   // address not found error
        return_val = false;
        continue;  // skip to the next sensor
      } else if (!mpu[i].begin()) {
          for (int j = 0; j < sensor_retry; j++) {
            delay(500);
            if(mpu[j].begin()){
              continue;
            }
            return_val = false;
         }
      }
      mpu[i].setAccelerometerRange(MPU6050_RANGE_2_G);    // estimate for low speed vehcile, increase if needed
      mpu[i].setGyroRange(MPU6050_RANGE_250_DEG);         // estimate for low speed vehcile, increase if needed
      mpu[i].setFilterBandwidth(MPU6050_BAND_44_HZ);         // based on 25 ms relay timeout
    }
    return return_val;
  }

  bool start_qmc(){
    bool return_val = true;
    for(int i = 0; i < number_of_qmc; i++){
      qmc[i] = new QMC5883LCompass();
      if (!address.detect(address.qmc[i])) {
        error.qmc[i] = 1;   // address not found error
        return_val = false;
        continue;  // skip to the next sensor
      } else {
        qmc[i].init();    // void function
      }
    }
    return return_val;
  }

  void start_ultrasonic(){
    bool return_val = true;
    pinMode(Pin::HCSR04[0], OUTPUT);
    for(int i = 1; i < number_of_HCSR04; i++){
        pinMode(Pin::HCSR04[i], INPUT);
        delay(10);
        if (ultrasonic.dist(i) == 0) {
          error.ultrasonic[i] = 1;   // address error for sensor not connected
          return_val = false;
        }
      }
    return return_val;
  }

  void start_steering(){
    pinMode(Pin::steer_position, INPUT);    // No way to perform initial check, maybe with gyro later?
  }

  bool start_gps(){
    bool return_val = true;
    gps_serial.begin(gps_baudrate);
    // Suggestion from chat GPT, not sure if this will work
    unsigned long start = millis();
    while (millis() - start < 1000) {  // Wait for 1 second
      while (gps_serial.available()) {
        gps.encode(gps_serial.read());
      }
    }
    if (gps.charsProcessed() < 10) {
      error.gps = 1;      // Use device not found error
    }
    return return_val;
  }

  void begin() {
    Serial.println("Starting sensor setup");
    start_ultrasonic();
    start_steering();
    IrReceiver.begin(Pin::IR);    // No hardware initialization, just wont get any data if its not connected right
    if (!start_lof() || !start_mpu() || !start_qmc() || !start_gps()){
      Serial.println("There was an error starting one or more sensors; see error log for more details");
    } else {
      Serial.println("All sensors started successfully");
    }
    delay(100);     // Make sure sensors have time before starting to read
  }
  
  class Values {
   public:
    uint16_t ultrasonic[number_of_HCSR04];
    uint16_t lof[number_of_lof];
    uint16_t steer_position;
    unsigned long ir;
    struct vector3_values {
      int16_t x;
      int16_t y;
      int16_t z;
    };
    uint16_t qmc_bearing[number_of_qmc];
    vector3_values qmc[number_of_qmc];
    struct mpu_values {
      vector3_values accel;
      vector3_values gyro;
      int temp;
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

  class Errors {
    private:
      struct packet {
        uint8_t index;
        char code[8];
      };
      static const uint8_t number_of = 5;
      const codes packet[number_of] = {
          {0, "none"},		// no error
          {1, "addr"},		// address not found
          {2, "init"},		// failed to initialize
          {3, "read"},		// failed to read data
          {4, "other"}		// any other failure
        };
   public:
    uint8_t ultrasonic[number_of_HCSR04];
    uint8_t lof[number_of_lof];
    uint8_t mpu[number_of_mpu];
    uint8_t qmc[number_of_qmc];
    uint8_t gps;
  };

  Errors error;

  void read(const String& sensor){

  }
  void read_all(){
    read_ultrasonic(0);
    read_lof(0);
    read_mpu(0);
    read_qmc(0);
    read_steering();
    read_gps();
  }

  void read_ultrasonic(uint8_t index = 0) {
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
        value.lof[i] = lof[i]->readRangeContinuousMillimeters();
      }
    } else if (index <= number_of_lof) {
      value.lof[index - 1] = lof[index - 1]->readRangeContinuousMillimeters();
    }
  }

  void read_mpu(uint8_t index){
    sensors_event_t a, g, temp;
    if (index == 0){
      for (int i = 0; i < number_of_mpu; i++) {
        mpu[i].getEvent(&a, &g, &temp);
        value.mpu[i].accel.x = a.acceleration.x;
        value.mpu[i].accel.y = a.acceleration.y;
        value.mpu[i].accel.z = a.acceleration.z;
        value.mpu[i].gyro.x = g.gyro.x;
        value.mpu[i].gyro.y = g.gyro.y;
        value.mpu[i].gyro.z = g.gyro.z;
        value.mpu[i].temp = temp.temperature;
      }
    } else if (index <= number_of_mpu) {
        mpu[index - 1].getEvent(&a, &g, &temp);
        value.mpu[index - 1].accel.x = a.acceleration.x;
        value.mpu[index - 1].accel.y = a.acceleration.y;
        value.mpu[index - 1].accel.z = a.acceleration.z;
        value.mpu[index - 1].gyro.x = g.gyro.x;
        value.mpu[index - 1].gyro.y = g.gyro.y;
        value.mpu[index - 1].gyro.z = g.gyro.z;
        value.mpu[index - 1].temp = temp.temperature;
    }
  }

  void read_qmc(uint8_t index){
    if (index == 0){
      for (int i = 0; i < number_of_qmc; i++) {
        qmc[i].read();
        value.qmc_bearing[i] = qmc[i].getAzimuth();
        value.qmc[i].x = qmc[i].getX();
        value.qmc[i].y = qmc[i].getY();
        value.qmc[i].z = qmc[i].getZ();
      }
    } else if (index <= number_of_qmc) {
        qmc[index - 1].read();
        value.qmc_bearing[index-1] = qmc[index-1].getAzimuth();
        value.qmc[index-1].x = qmc[index-1].getX();
        value.qmc[index-1].y = qmc[index-1].getY();
        value.qmc[index-1].z = qmc[index-1].getZ();
    }
  }

  void read_steering () {
    value.steer_position = steer_position.get_degrees();
  }

  void read_gps(){
    if (gps_serial.available() > 0){
      delay(serial_delay);      // Wait for data to finish coming in
      if (gps.encode(gps_serial.read())){
        if (gps.location.isValid()) {
          value.gps.lat = gps.location.lat();
          value.gps.lng = gps.location.lng();
        }
        if (gps.altitude.isValid()) {
          value.gps.alt = gps.altitude.meters();
        }
        if (gps.course.isValid()){
          value.gps.deg = gps.course.deg();
        }
        if(gps.speed.isValid()){
          value.gps.spd = gps.speed.kmph();
        }
        if (gps.satellites.isValid()){
          value.gps.fix = gps.satellites.value();
        }
      } else {
        error.gps = 3;       // Failed to read data
      }
    }
    // If data not available, nothing to read - add something to keep track of how long it has been since successful read
  }

  void read_ir(){
    if (ir.decode()) {
      value.ir = ir.decodedIRData.command;
      ir.resume();
    } else {
      value.ir = 0;   // no data recieved
    }
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