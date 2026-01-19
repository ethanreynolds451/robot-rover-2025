#ifndef DATAREAD_h
#define DATAREAD_h

#include "inputCodes/inputCodes.h"
#include "inputData/inputData"			

// Note: this depends on vars in codes.h, output.h, and input.h; any changes to these files will need to be updated

class commandParser {
  public:
    commandParser(size_t string_limit) : string_limit(string_limit) {}
    bool verify_delimiter(const char* input, const char* delimiter, uint16_t start){               // Returns true if delimiter is valid
        const size_t len = strlen(delimiter);       // Get length of delimiter
        size_t index = start;                       // Initialize string index to start position
        for(int i = 0; i < len; i++){               // Check each character in delimiter
            if(index >= string_limit){               // Ensure no exceed string limit
                return 0;                           // Return false if limit exceeded
            }
            if(input[index] == delimiter[i]){		// Compare input character to delimiter character
                index++;	                        // Advance string index
            } else {                                
                return 0;					        // If they don't match, return false (delimiter is invalid)
            }		
        }
        return 1;                                   // Return true if delimiter read successfully
    }
    bool start_valid(const char* input){                                               // Returns true if start delimiter is valid
        return verify_delimiter(input, Code::Delimiter::start, 0);
    }
    bool end_valid(const char* input){
        return verify_delimiter(input, Code::Delimiter::end, strlen(input) - strlen(Code::Delimiter::end));
    }
    bool data_start_valid(const char* input, uint16_t current_index){
        return verify_delimiter(input, Code::Delimiter::v_start, current_index);
    }   
    bool data_end_valid(const char* input, uint16_t current_index){
        return verify_delimiter(input, Code::Delimiter::v_end, current_index);
    }

    int8_t get_command_index_from_string(const char* code_str){
        for(int i = 0; i < Code::Command::number_of; i++){
            if(strcmp(Code::Command::str[i], code_str) == 0){
                return i;
            }
        }
        return -1;  // Return -1 if command not found
    }

    bool set_value_from_index(OutputStates::Values &commands, uint8_t index, const char* value_str){
        if (index >= Code::Command::number_of) {
            return 0;   // Return false if index out of bounds
        }
        OutputStates::set_by_index(&commands, index, value_str);
        return 1;  // Return true if value set successfully
    }

    bool set_value_from_string(OutputStates::Values &commands, const char* code_str, const char* value_str){
        size_t index = get_command_index_from_string(code_str);
        return set_value_from_index(commands, index, value_str);
    }

    enum extraction_errors {
        SUCCESS = 0,
        INVALID_START_DELIMITER = 1,
        INVALID_END_DELIMITER = 2,
        INVALID_DATA_START_DELIMITER = 3,
        INVALID_DATA_END_DELIMITER = 4,
        INVALID_COMMAND_CODE = 5,
        INVALID_DATA_VALUE = 6,
    };

    // Optional index parameter to know where parser left off if there is an error
    uint8_t extract_commands(OutputStates::Values &commands, const char* input, size_t& current_index){     
        OutputStates::reset_input();   // Clear input buffer before extracting new command

        // Step 1: Verify start and end delimiter, exit if invalid
        if(!start_valid(input)){
            return INVALID_START_DELIMITER;
        } else if(!end_valid(input)){
            return INVALID_END_DELIMITER;
        }

        // Step 2: Read commands and data between the delimiters
        // already verified that command string fills entire input from 0 to null terminator
       
        // Declare temporary buffers and indexes
        size_t end_index = strlen(input) - strlen(Code::Delimiter::end) - 1;          // End before first char of end delimiter 

        char current_code[Code::Command::max_length];
        char current_value[OutputStates::max_length];

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
    }

    uint8_t extract_commands(OutputStates::Values &commands, const char* input){   
        size_t tmp_index = 0; 
        return extract_commands(commands, input, tmp_index);
    }  

  private:
    size_t string_limit;    // Maximum length of input string, local constant
    
    bool read_code(char* input, char* output, size_t& index){ 
        // This will advance the index provided to the first character of the value delimiter
        size_t tmp_code_len = Code::Command::max_length;
        char tmp_code[tmp_code_len];
        size_t code_index = 0;
        while(index < string_limit){	                       
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == Code::Delimiter::v_start[0]) {    // Exit if the end found
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
        size_t tmp_data_len = OutputStates::max_length;
        char tmp_data[tmp_data_len];
        size_t data_index = 0;
        while(index < string_limit){					  
            if(!isalnum(input[index])){          // Make sure it is a valid characther
                return false; 
            } else if(input[index] == Code::Delimiter::v_end[0]){	
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

};

#endif