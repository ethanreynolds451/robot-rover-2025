#ifndef DEFINITIONS_h
#define DEFINITIONS_h

// Program flow / functionality parameters
static const long baudrate = 115200;
static const uint32_t gps_baudrate = 4800;
static const uint16_t serial_delay = 10;
static const uint16_t loop_interval = 10;
static const uint16_t send_interval = 25;
static const uint8_t string_limit = 64;

// How many of each type of sensor
static const uint8_t number_of_ir = 1;

// How many times to retry sensor initializations before moving on
static const uint8_t sensor_retry = 3;


namespace Pin {
  static constexpr uint8_t IR = 4;
};


namespace sensor_code {
  const char* remote = "ir";
};

namespace value {                      // Storage for sensor values
  unsigned long ir;
};

namespace error {                    // Storage for sensor errors
  namespace {
    static const uint8_t number_of_errors = 6;
    struct error_packet {
      uint8_t index;
      char code[8];   // 8 byte max for codes
    };
  };
  const error_packet error_codes[number_of_errors] = {
      {0, "none"},    // no error
      {1, "addr"},    // address not found
      {2, "init"},    // failed to initialize
      {3, "read"},    // failed to read data
      {4, "nocom"},   // unable to communicate
      {5, "other"}    // any other failure
  };
};


// Composite class to access all sensors, includes all relevant sensor objects
class Sensor {
public:
  Sensor();

  void begin() {        // Calls to read will retrieve data from sensor(s) and store it in values array for further access / processing
    Serial.println("Starting sensor setup");
    start_ir(); 
    Serial.println("All sensors started successfully");
    delay(100);     // Make sure sensors have time before starting to read
  }

  void read(const String& sensor){    // Read an individual sensor, might add this later
    return;
  }

  void read_all(){                    // Read all the sensors
    read_ir();
  }

private:
  IRrecv ir;              // Create single IR remote sensor object

  void start_ir(){  
    ir.begin(Pin::IR);    // No hardware initialization, just wont get any data if its not connected right
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

Sensor::Sensor() {}     // Constructor for sensor class

Sensor sensor;          // Create instance of sensor class

class Data {
  private:
    char buffer[string_limit];
    char output[string_limit];
    char data_start = '[';
    char data_end = ']'; 
    char* get_ir(){                         // Return formatted value of IR
      memset(buffer, 0, string_limit);
      strcpy(buffer, sensor_code::remote); 
      strcpy(buffer, value::ir);
      strcpy(buffer, data_end); 
      return buffer; 
    }
  public:
    char* get(){
      memset(output, 0, string_limit);
      strcpy(output, get_ir());
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
