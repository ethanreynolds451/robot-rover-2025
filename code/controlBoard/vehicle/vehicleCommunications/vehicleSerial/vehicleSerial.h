// Compiled successfully 2025-01-02

#ifndef VEHICLESERIAL_h
#define VEHICLESERIAL_h

class RobotSerial {
  public:
	RobotSerial(uint32_t baud_rate, uint8_t string_limit) : baud_rate(baud_rate), input_string_limit((size_t)string_limit) {
		// Max length is 255, accepting a uint8_t and casting to size_t to hardcode limit
		this->input_buffer[0] = '\0';	// Initialize input string to empty
		this->output_buffer[0] = '\0'; // Initialize output string to empty
		this->serial_delay = 100;
	}
	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
		while (!Serial) { }  // only on USB-based boards, wait till serial is ready
	}
	char* read(){
		if (is_input()){
			read_input();		
		}
		return this->input_buffer;
	}
	void read_into(char* output_buffer, uint16_t length = MAX_LENGTH){
		if (is_input()){
			read_input();
			strncpy(output_buffer, this->input_buffer, length);
		}
	}
	char* get(){
		return this->input_buffer;
	}
	void get_into(char* output_buffer, uint16_t length = MAX_LENGTH){
		strncpy(output_buffer, this->input_buffer, length);
	}
	void write(const char* output){
		Serial.print(output);
	}
	void writeln(const char* output){
		Serial.println(output);
	}
	void add(const char* output){
		strcat(this->output_buffer, output);
	}
	void send(){
		Serial.print(this->output_buffer);
		this->output_buffer[0] = '\0'; // Clear output buffer after sending
	}
	void write_line(const char* output){
		Serial.println(output);
	}

  private:	
  	uint32_t baud_rate;
	size_t input_string_limit;
	uint8_t serial_delay;
	static constexpr size_t MAX_LENGTH = 255;
	char input_buffer[MAX_LENGTH];
	char output_buffer[MAX_LENGTH];
	uint8_t loop_counter = 0;     
	bool is_input(){
		if(Serial.available() > 0) {
			this->loop_counter++;
			return true;
		}
		return false;
	}
	void read_input(){
		delay(RobotSerial::serial_delay);
		uint16_t index = 0;
		while(Serial.available()){	
			int c = Serial.read();		// Returns int, -1 if no data available
			if (c < 0) break; // Safety to ensure invalid character isn't read
			this->input_buffer[index] = (char)c;	// Need to cast to char
			if(index == input_string_limit - 1){
				break;
			}
			index++;
		}
		this->input_buffer[index] = '\0'; // Null-terminate the string
	}
};


#endif
