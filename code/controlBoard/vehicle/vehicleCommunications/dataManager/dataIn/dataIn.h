// Successfully compiled 2026-01-18

#ifndef DATAIN_h
#define DATAIN_h

// Class functions: 
// Read and parse input string, return error code (0 for success)
// Validate data values and transfer if successful by calling inputData validation function
// Return the latest values for each command

#include "inputDelimiter/inputDelimiter.h"
#include "inputCode/inputCode.h"
#include "inputData/inputData.h"			

class dataIn {
  public:
    dataIn(size_t string_limit) : string_limit(string_limit){}

    enum extraction_errors {
        SUCCESS = 0,
        INVALID_START_DELIMITER = 1,
        INVALID_END_DELIMITER = 2,
        INVALID_DATA_START_DELIMITER = 3,
        INVALID_DATA_END_DELIMITER = 4,
        INVALID_COMMAND_CODE = 5,
        INVALID_DATA_VALUE = 6,
    };

    // Extract commands from input string and store in commands struct
    uint8_t extract(const char* input){
        // Returns the error code associated with it
        return extract_commands(input);
    }
    uint8_t extract(const char* input, size_t& index){
        // Returns the error code associated with it
        return extract_commands(input, index);
    }

    bool validate_and_set(){
        return data.set_from_input();
    }

    // Override invalid commands and directly transfer to current output
    void set_commands(){
        data.commit_buffer();
    }

    char* get_string(){
        // {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}
        char buffer[string_limit];
        sprintf(buffer, "br: %d rv: %d rv: %d srv: %d su: %d sp: %d ssp: %d fan: %d",
                get_brake(), get_reverse(), get_s_reverse(), get_shift_up(),
                get_speed(), get_s_speed(), get_f_speed());
        return buffer;
    }

	bool is_command(const char* input_string){
		if (!input_string) return false;		// Check for null pointer
		const size_t start_length = strlen(InputDelimiter::start);
		const size_t end_length = strlen(InputDelimiter::end);
		const size_t input_length = strlen(input_string);
		return ((input_length >= start_length + end_length) && 
				(strncmp(input_string, InputDelimiter::start, start_length) == 0) &&
				(strncmp(input_string + input_length - end_length, InputDelimiter::end, end_length) == 0)
				);
	}

    // Setter pass-through functions
    void set(uint8_t index, bool value){
        data.set_input(index, value);
    }
    void set(uint8_t index, uint8_t value){
        data.set_input(index, value);
    }
    void set(const char* code_str, const char* value_str){
        // This MUST BE FIXED if other data types are added
        data.set_input(InputCode::code_to_index(code_str), value_str);
    }

    // Setter pass-through functions for specific commands
    void set_brake(bool value){
        data.set_input(inputData::Index::BRAKE, value);
    }
    void set_reverse(bool value){
        data.set_input(inputData::Index::REVERSE, value);
    }
    void set_s_reverse(bool value){
        data.set_input(inputData::Index::S_REVERSE, value);
    }
    void set_shift_up(bool value){
        data.set_input(inputData::Index::SHIFT_UP, value);
    }
    void set_speed(uint8_t value){
        data.set_input(inputData::Index::SPEED, value);
    }
    void set_s_speed(uint8_t value){
        data.set_input(inputData::Index::S_SPEED, value);
    }
    void set_f_speed(uint8_t value){
        data.set_input(inputData::Index::F_SPEED, value);
    }
    void reset_input(){
        data.reset_input(); 
    }
    void reset(){
        data.reset(); 
    }


    bool get_brake(){
        return *(bool*)data.get_current(inputData::Index::BRAKE);
    }
    bool get_reverse(){
        return *(bool*)data.get_current(inputData::Index::REVERSE);
    }
    bool get_s_reverse(){
        return *(bool*)data.get_current(inputData::Index::S_REVERSE);
    }
    bool get_shift_up(){
        return *(bool*)data.get_current(inputData::Index::SHIFT_UP);
    }
    uint8_t get_speed(){
        return *(uint8_t*)data.get_current(inputData::Index::SPEED);
    }
    uint8_t get_s_speed(){
        return *(uint8_t*)data.get_current(inputData::Index::S_SPEED);
    }
    uint8_t get_f_speed(){
        return *(uint8_t*)data.get_current(inputData::Index::F_SPEED);
    }

    
  private:
    size_t string_limit;    // Maximum length of input string, local constant
    
    inputData data;    // Instance of input data manager
    
    // Optional index parameter to know where parser left off if there is an error
    uint8_t extract_commands(const char* input, size_t& current_index){     
        data.reset_input();   // Clear input buffer before extracting new command

        // Step 1: Verify start and end delimiter, exit if invalid
        if(!InputDelimiter::start_valid(input)){
            return INVALID_START_DELIMITER;
        } else if(!InputDelimiter::end_valid(input)){
            return INVALID_END_DELIMITER;
        }

        // Step 2: Read commands and data between the delimiters
        // already verified that command string fills entire input from 0 to null terminator
       
        // Declare temporary buffers and indexes
        size_t end_index = strlen(input) - strlen(InputDelimiter::end) - 1;          // End before first char of end delimiter 

        char current_code[InputDelimiter::max_length];
        char current_value[data.max_length];

        // Loop through delimiters and values until the end is reached 
        while(current_index <= end_index){	
            if(read_code(input, current_code, current_index)){
                if (!InputDelimiter::data_start_valid(input, current_index)){
                    return INVALID_DATA_START_DELIMITER;   // Invalid start delimiter
                }
                if(read_data(input, current_value, current_index)){
                    if (!InputDelimiter::data_end_valid(input, current_index)){
                        return INVALID_END_DELIMITER;   // Invalid end delimiter
                    }
                    // Set command value
                    set(InputCode::code_to_index(current_code), current_value);
                } else {
                    return INVALID_COMMAND_CODE;   // Invalid data while reading
                }
            } else {
                return INVALID_COMMAND_CODE;   // Invalid command code
            }
        }
        return 0; 
    };

    // Overload version that doesn't track index externally
    uint8_t extract_commands(const char* input){   
        size_t tmp_index = 0; 
        return extract_commands(input, tmp_index);
    };

    bool read_code(char* input, char* output, size_t& index){ 
        // This will advance the index provided to the first character of the value delimiter
        size_t tmp_code_len = InputDelimiter::max_length;
        char tmp_code[tmp_code_len];
        size_t code_index = 0;
        while(index < string_limit){	                       
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == InputDelimiter::v_start[0]) {    // Exit if the end found
                tmp_code[code_index] = '\0';   // Add null terminator
                strcpy(output, tmp_code);    
                return true;	             // For success    
            } else {                             // Otherwise keep going 
                tmp_code[code_index] = input[index];	// read designator into tmp buffer
                if (code_index >= tmp_code_len - 1) return false;  // Prevent buffer overflow
                code_index++;                           // advance to next buffer character
                index++;                                // advance to next input character
            }
        }
        return false;   // Return false if string limit exceeded without finding value start delimiter
    }

    // Expects input index to be first char of data
    bool read_data(char* input, char* output, size_t& index){
        size_t tmp_data_len = data.max_length;
        char tmp_data[tmp_data_len];
        size_t data_index = 0;
        while(index < string_limit){					  
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == InputDelimiter::v_end[0]){	
                tmp_data[data_index] = '\0';
                strcpy(output, tmp_data);
                return true;	             // For success
            } else {                             // Otherwise keep going 
                tmp_data[data_index] = input[index];    // read character into tmp buffer
                if (data_index >= tmp_data_len - 1) return false;  // Prevent buffer overflow                
                data_index++;               // advance to next buffer character 
                index++;                    // advance to next input character
            }
        }
        return false;   // Return false if string limit exceeded without finding value end delimiter
    };


};

#endif