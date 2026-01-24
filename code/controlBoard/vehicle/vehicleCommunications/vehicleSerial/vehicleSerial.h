// Compiled successfully 2025-01-02

#ifndef VEHICLESERIAL_h
#define VEHICLESERIAL_h

class RobotSerial {
  public:
	RobotSerial(uint16_t baud_rate) : baud_rate(baud_rate) {
		this->input_buffer[0] = '\0';	// Initialize input string to empty
		this->output_buffer[0] = '\0'; // Initialize output string to empty
	}
	void begin(){
		Serial.begin(this->baud_rate);	// Start serial communication
		while (!Serial) { }  // only on USB-based boards, wait till serial is ready
		Serial.println("Serial started successfully"); 
	}
	char* read(){
		if (is_input()){
			read_input();		
		}
		return this->input_buffer;
	}
	void read_into(char* output_buffer, uint16_t length = STRING_LIMIT){
		if (is_input()){
			read_input();
			strncpy(output_buffer, this->input_buffer, length);
		}
	}
	char* get(){
		return this->input_buffer;
	}
	void get_into(char* output_buffer, uint16_t length = STRING_LIMIT){
		strncpy(output_buffer, this->input_buffer, length);
	}
	void write(const char* output){
		Serial.print(output);
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
  	static constexpr uint8_t serial_delay = 10;
  	uint16_t baud_rate;
	char input_buffer[STRING_LIMIT];
	char output_buffer[STRING_LIMIT];
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
			if(index == STRING_LIMIT - 1){
				break;
			}
			index++;
		}
		this->input_buffer[index] = '\0'; // Null-terminate the string
	}
};


#endif
