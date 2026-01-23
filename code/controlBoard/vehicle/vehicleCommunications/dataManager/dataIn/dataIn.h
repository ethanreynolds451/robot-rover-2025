// Successfully compiled 2026-01-18

#ifndef DATAREADER_h
#define DATAREADER_h

#include "inputDelimiter/inputDelimiter.h"
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
    uint8_t extract_commands(InputData::Values &commands, const char* input){
        return extract_commands(commands, input);
    }

    // Getter pass-through functions
    bool get_brake(){
        return *(bool*)InputData::get(InputData::Index::BRAKE, &commands);
    }
    bool get_reverse(){
        return *(bool*)InputData::get(InputData::Index::REVERSE, &commands);
    }
    bool get_s_reverse(){
        return *(bool*)InputData::get(InputData::Index::S_REVERSE, &commands);
    }
    bool get_shift_up(){
        return *(bool*)InputData::get(InputData::Index::SHIFT_UP, &commands);
    }
    uint8_t get_speed(){
        return *(uint8_t*)InputData::get(InputData::Index::SPEED, &commands);
    }
    uint8_t get_s_speed(){
        return *(uint8_t*)InputData::get(InputData::Index::S_SPEED, &commands);
    }
    uint8_t get_f_speed(){
        return *(uint8_t*)InputData::get(InputData::Index::F_SPEED, &commands);
    }


  private:
    size_t string_limit;    // Maximum length of input string, local constant
    
    inputData data;    // Instance of input data manager

};

#endif



    int8_t get_command_index_from_string(const char* code_str){
        for(int i = 0; i < InputCode::Command::number_of; i++){
            if(strcmp(InputCode::Command::str[i], code_str) == 0){
                return i;
            }
        }
        return -1;  // Return -1 if command not found
    }

    bool set_value_from_index(InputData::Values &commands, uint8_t index, const char* value_str){
        if (index >= InputCode::Command::number_of) {
            return 0;   // Return false if index out of bounds
        }
        InputData::set_by_index(&commands, index, value_str);
        return 1;  // Return true if value set successfully
    }

    bool set_value_from_string(InputData::Values &commands, const char* code_str, const char* value_str){
        size_t index = get_command_index_from_string(code_str);
        return set_value_from_index(commands, index, value_str);
    }



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
                if (!data_start_valid(input, current_index)){
                    return INVALID_DATA_START_DELIMITER;   // Invalid start delimiter
                }
                if(read_data(input, current_value, current_index)){
                    if (!data_end_valid(input, current_index)){
                        return INVALID_END_DELIMITER;   // Invalid end delimiter
                    }
                    // Set command value
                    if(!set_value_from_string(commands, current_code, current_value)){
                        return INVALID_DATA_VALUE;   // Invalid data value
                    }
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
        size_t tmp_code_len = InputCode::Command::max_length;
        char tmp_code[tmp_code_len];
        size_t code_index = 0;
        while(index < string_limit){	                       
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == InputCode::Delimiter::v_start[0]) {    // Exit if the end found
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
        size_t tmp_data_len = InputData::max_length;
        char tmp_data[tmp_data_len];
        size_t data_index = 0;
        while(index < string_limit){					  
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == InputCode::Delimiter::v_end[0]){	
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
    }
