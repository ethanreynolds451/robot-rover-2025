#ifndef SENSOR_h
#define SENSOR_h

// Split this into individual sensor files and instantiate in vehcile class

class Sensor {
public:
  Sensor(); // For constructor (needed to initialize arrays of sensors)

  void begin() {        // Calls to read will retrieve data from sensor(s) and store it in values array for further access / processing
    Serial.println("Starting sensor setup");
    start_ultrasonic();
    start_steering();
    start_ir(); 
    if (!start_lof() || !start_mpu() || !start_qmc() || !start_gps()){
    Serial.println("There was an error starting one or more sensors; see error log for more details");
    } else {
    Serial.println("All sensors started successfully");
    }
    delay(100);     // Make sure sensors have time before starting to read
  }

  void read(const String& sensor){    // Read an individual sensor, might add this later
    return;
  }

  void read_all(){                    // Read all the sensors
    read_ultrasonic(0);
    read_lof(0);
    read_mpu(0);
    read_qmc(0);
    read_steering();
    read_gps();
    read_ir();
  }

private:
  HCSR04 ultrasonic;                      // Allows for direct definition of array, no need to use pointers
  VL53L0X* lof[number_of_lof];        // Pointer to array of sensor, MUST USE POINTER NOT DOT NOTATION
  Potentiometer steer_position;
  Adafruit_MPU6050* mpu[number_of_mpu];
  QMC5883LCompass* qmc[number_of_qmc];
  IRrecv ir;
  TinyGPSPlus gps;
  SoftwareSerial gps_serial;                    // GPS uses software serial to communicate

  bool start_lof(){                                     // Still work in progress
   if(pcf_active){
    bool return_val = true;
    for(int i = 0; i < number_of_lof; i++){   // Initialize all pointers to nullptr
      lof[i] = nullptr;
    }
    // Set the I2C addresses of the lof sensors
    for(int i = 0; i < number_of_lof; i++){
      PCF.write(Pin::x_shut[i], LOW);      // Deactivate all lof sensors
    }
    delay(50);                                                       Serial.println("Checkpoint 1");
    for(int i = 0; i < number_of_lof; i++){
      bool addr_found = false;
      bool initiated = false;
      bool addr_set = false;
      lof[i] = new VL53L0X();                   // Create sensor object  // Activate the one to set address
      PCF.write(Pin::x_shut[i], LOW);                                                         Serial.println("Checkpoint 1.1");
      delay(50);
      for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if (!addr_found) {
          if (!Address::detect(0x29)) {
            error::lof[i] = 1;   // address not found error
                return_val = false;
          } else {
            addr_found = true;
          }                                           Serial.println("Checkpoint 1.1.5");
        } else if (!initiated) {
          if (!lof[i]->init()) {
            return_val = false;
            error::lof[i] = 2;   // failed to initialize error
          } else {
            initiated = true;
          }
        } else if(!addr_set){
          delay(10);
          lof[i]->setAddress(Address::lof[i]);
          delay(10);
          if (!Address::detect(Address::lof[i])) {        // Verify that sensor is active with address
            error::lof[i] = 4;   // unable to communicate error
            return_val = false; // skip to the next sensor
          } else {
            addr_set = true;
          }
        } else {
          PCF.write(Pin::x_shut[i], LOW);   // Deactivate after verifyinig
          error::lof[i] = 0;
          break;    // Move on to the next sensor
        }
      }
    }
    delay(10);                                                    Serial.println("Checkpoint 2");
    for(int i = 0; i < number_of_lof; i++){
      if(lof[i] != nullptr && error::lof[i] == 0){
        lof[i]->startContinuous();
      }
    }
   } else {
    return false; 
   }
  }   // add address verification, retry to set address if didn't work, exit after n times

  bool start_mpu(){
    bool return_val = true;
    for(int i = 0; i < number_of_mpu; i++){   // Initialize all pointers to nullptr
      mpu[i] = nullptr;
    }
    for(int i = 0; i < number_of_mpu; i++){
      bool addr_found = false;
      bool initiated = false;
      mpu[i] = new Adafruit_MPU6050();
      for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if(!addr_found) {
          if (!Address::detect(Address::mpu[i])) {
            error::mpu[i] = 1;          // address not found error
            return_val = false;
          } else {
            addr_found = true;
          }
        } else if (!initiated) {
          if (!mpu[i]->begin()) {
            error::mpu[i] = 2;    // Addr not found error
            return_val = false;
          } else {
            initiated = true;
          }
        } else {
          delay(50);
          mpu[i]->setAccelerometerRange(MPU6050_RANGE_2_G);    // estimate for low speed vehcile, increase if needed
          mpu[i]->setGyroRange(MPU6050_RANGE_250_DEG);         // estimate for low speed vehcile, increase if needed
          mpu[i]->setFilterBandwidth(MPU6050_BAND_44_HZ);         // based on 25 ms relay timeout
          error::mpu[i] = 0;
          break;
        }
      }
    }
    return return_val;
  }

  bool start_qmc(){
    bool return_val = true;
    for(int i = 0; i < number_of_qmc; i++){   // Initialize all pointers to nullptr
      qmc[i] = nullptr;
    }
    for(int i = 0; i < number_of_qmc; i++){
      qmc[i] = new QMC5883LCompass();
      bool addr_found = false;
      bool initiated = false;
      for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if(!addr_found){
          if (!Address::detect(Address::qmc[i])) {
            error::qmc[i] = 1;   // address not found error
            return_val = false;
            continue;  // skip to the next sensor
          } else {
            addr_found = true;
          }
        } else if(!initiated){
          qmc[i]->init();    // void function
          initiated = true;
        } else {
          error::qmc[i] = 0;
          break;
        }
      }
    }
    return return_val;
  }

  bool start_ultrasonic(){
    bool return_val = true;
    pinMode(Pin::HCSR04[0], OUTPUT);
    for(int i = 1; i < number_of_ultrasonic; i++){
        pinMode(Pin::HCSR04[i], INPUT);
        delay(10);
        if (ultrasonic.dist(i) == 0) {      // They are pulled down so will return 0 if not connected
          error::ultrasonic[i] = 4;   // address error for sensor not connected
          return_val = false;
        }
      }
    return return_val;
  }

  void start_steering(){
    pinMode(Pin::steer_position, INPUT);    // No way to perform initial check, maybe with gyro / compass later?
  }

  void start_ir(){
    ir.begin(Pin::IR);    // No hardware initialization, just wont get any data if its not connected right
  }

  bool start_gps(){
    bool return_val = true;
    gps_serial.begin(gps_baudrate);
    // Suggestion from chat GPT, not sure if this will work
    for (uint8_t tried = 0; tried < sensor_retry; tried++){
      unsigned long start = millis();
      while (millis() - start < 1000) {  // Wait for 1 second
        while (gps_serial.available()) {
          gps.encode(gps_serial.read());
        }
      }
      if (gps.charsProcessed() < 10) {
        error::gps = 1;      // Use device not found error
      } else {
        break;
      }
    }
    return return_val;
  }

  void read_ultrasonic(uint8_t index = 0) {
    if (index == 0){
      for (int i = 0; i < number_of_ultrasonic; i++) {
        value::ultrasonic[i] = ultrasonic.dist(i);
      }
    } else if (index <= number_of_ultrasonic) {
      value::ultrasonic[index - 1] = ultrasonic.dist(index - 1);
    }
  }

  void read_lof (uint8_t index) {
    if (index == 0){
      for (int i = 0; i < number_of_lof; i++) {
        value::lof[i] = lof[i]->readRangeContinuousMillimeters();
      }
    } else if (index <= number_of_lof) {
      value::lof[index - 1] = lof[index - 1]->readRangeContinuousMillimeters();
    }
  }

  void read_mpu(uint8_t index){
    sensors_event_t a, g, temp;
    if (index == 0){
      for (int i = 0; i < number_of_mpu; i++) {
        mpu[i]->getEvent(&a, &g, &temp);
        value::mpu[i].accel.x = a.acceleration.x;
        value::mpu[i].accel.y = a.acceleration.y;
        value::mpu[i].accel.z = a.acceleration.z;
        value::mpu[i].gyro.x = g.gyro.x;
        value::mpu[i].gyro.y = g.gyro.y;
        value::mpu[i].gyro.z = g.gyro.z;
        value::mpu[i].temp = temp.temperature;
      }
    } else if (index <= number_of_mpu) {
        mpu[index - 1]->getEvent(&a, &g, &temp);
        value::mpu[index - 1].accel.x = a.acceleration.x;
        value::mpu[index - 1].accel.y = a.acceleration.y;
        value::mpu[index - 1].accel.z = a.acceleration.z;
        value::mpu[index - 1].gyro.x = g.gyro.x;
        value::mpu[index - 1].gyro.y = g.gyro.y;
        value::mpu[index - 1].gyro.z = g.gyro.z;
        value::mpu[index - 1].temp = temp.temperature;
    }
  }

  void read_qmc(uint8_t index){
    if (index == 0){
      for (int i = 0; i < number_of_qmc; i++) {
        qmc[i]->read();
        value::qmc_bearing[i] = qmc[i]->getAzimuth();
        value::qmc[i].x = qmc[i]->getX();
        value::qmc[i].y = qmc[i]->getY();
        value::qmc[i].z = qmc[i]->getZ();
      }
    } else if (index <= number_of_qmc) {
        qmc[index - 1]->read();
        value::qmc_bearing[index-1] = qmc[index-1]->getAzimuth();
        value::qmc[index-1].x = qmc[index-1]->getX();
        value::qmc[index-1].y = qmc[index-1]->getY();
        value::qmc[index-1].z = qmc[index-1]->getZ();
    }
  }

  void read_steering () {
    value::steer_position = steer_position.get_degrees();
  }

  void read_gps(){
    if (gps_serial.available() > 0){
      delay(serial_delay);      // Wait for data to finish coming in
      if (gps.encode(gps_serial.read())){
        if (gps.location.isValid()) {
          value::gps.lat = gps.location.lat();
          value::gps.lng = gps.location.lng();
        }
        if (gps.altitude.isValid()) {
          value::gps.alt = gps.altitude.meters();
        }
        if (gps.course.isValid()){
          value::gps.deg = gps.course.deg();
        }
        if(gps.speed.isValid()){
          value::gps.spd = gps.speed.kmph();
        }
        if (gps.satellites.isValid()){
          value::gps.fix = gps.satellites.value();
        }
      } else {
        error::gps = 3;       // Failed to read data
      }
    }
    // If data not available, nothing to read - add something to keep track of how long it has been since successful read
  }

  void read_ir(){
    if (ir.decode()) {
      value::ir = ir.decodedIRData.command;
      ir.resume();
    } else {
      value::ir = 0;   // no data recieved
    }
  }
};

Sensor::Sensor()
  : ultrasonic(Pin::HCSR04[0], new int[number_of_ultrasonic]{Pin::HCSR04[1], Pin::HCSR04[2], Pin::HCSR04[3], Pin::HCSR04[4], Pin::HCSR04[5], Pin::HCSR04[6]}, number_of_ultrasonic),
    steer_position(Pin::steer_position, 1023, 0, 0.75, 512),
    gps_serial(Pin::TX, Pin::RX) {}

#endif