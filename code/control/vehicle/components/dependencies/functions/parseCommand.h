#ifndef PARSECOMMAND_h
#define PARSECOMMAND_h

#include <Arduino.h>

// Note: this depends on vars in codes.h, output.h, and input.h; any changes to these files will need to be updated

class commandParser {
  public:
    commandParser(size_t string_limit) : string_limit(string_limit) {}
    bool verify_delimiter(const char* input, const char* delimiter, uint16_t start){               // Returns true if delimiter is valid
        const size_t len = strlen(delimiter);       // Get length of delimiter
        size_t index = start;                       // Initialize string index to start position
        for(int i = 0; i < len; i++){               // Check each character in delimiter
            if(index > string_limit){               // Ensure no exceed string limit
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
    bool end_valid(){
        return verify_delimiter(input, Code::Delimiter::start, strlen(input) - strlen(Code::Delimiter::end));
    }
    bool data_start_valid(uint16_t current_index){
        return verify_delimiter(input, Code::Delimiter::v_start, current_index);
    }   
    bool data_end_valid(uint16_t current_index){
        return verify_delimiter(input, Code::Delimiter::v_end, current_index);
    }

    uint8_t get_command_index_from_string(cosnt char* code_str){
        for(int i = 0; i < Code::Command::number_of; i++){
            if(strcmp(Code::Command::str[i], code_str) == 0){
                return i;
            }
        }
        return -1;  // Return -1 if command not found
    }

    bool set_value_from_index(Values &commands, uint8_t index, const char* value_str){
        if index >= Code::Command::number_of {
            return 0;   // Return false if index out of bounds
        }
        OutputStates::set_by_index(&commands, index, value_str);
        return 1;  // Return true if value set successfully
    }

    bool set_value_from_string(Values &commands, const char* code_str, const char* value_str){
        index = get_command_index_from_string(code_str);
        return set_value_from_index(commands, index, value_str);
    }

    bool extract_commands(Values &commands, const char* input){     
        // Step 1: Verify start and end delimiter, exit if invalid
        if(!start_valid(input) || !end_valid(input)){
            return 0;
        } 

        // Step 2: Read commands and data between the delimiters
        // already verified that command string fills entire input from 0 to null terminator
       
        // Declare temporary buffers and indexes
        size_t current_index = strlen(Code::Delimiter::start) + 1;                    // Start after last char of start delimiter
        size_t end_index = strlen(input) - strlen(Code::Delimiter::end) - 1;          // End before first char of end delimiter 
        
        size_t tmp_code_len = Code::Command::max_length;
        char tmp_code[tmp_code_len];
        size_t code_index = 0;

        size_t tmp_data_len = OutputStates::max_length;
        char tmp_data[tmp_data_len];
        size_t data_index = 0;

        // Loop through delimiters and values until the end is reached 
        while(current_index <= end_index){	
            // A) get a command code
            memset(tmp_code, 0, tmp_code_len);      // Reset code buffer      
            code_index = 0;				            // Go to start of code buffer
            while(true){	                       
                if(isalpha(input[index]) &&         // Make sure it is a valid characther
                        input[index] != Code::Delimiter::v_start[0]) {     
                    tmp_code[code_index] = input[index];	// read designator into tmp buffer
                    code_index++;                           // advance to next buffer character
                    index++;                                // advance to next input character
                } else {                             // Break if it is not a valid character or 
                    tmp_code[code_index] = '\0';       
                    break;	// If bad nonalpha or end char encounter
                }
            }
            // This will leave off at the first character of the value delimiter

            // B) get the data 
        
                // Check the rest of the start delimiter (or just advance to the next char if single char delimiter)
                for(int i = 0; i < strlen(tmp_delimiter); i++){
                    if(input[index] == tmp_delimiter[i]){		
                        index++;	
                    } else {
                        return 0;					
                    }		
                }
                // This will advance index to the character after the value start delimiter

                // Reset buffers and prepare to read data
                memset(tmp_data 0, tmp_len);
                memset(tmp_delimiter, 0, tmp_len);
                strcpy(tmp_delimiter, Delimiter::v_end);

                // Read data until end delimiter
                data_index = 0;
                while(true){					  
                    if(input[index] != tmp_delimiter[0]){	
                        tmp_data[data_index] = input[index];
                        data_index++;               // advance to next buffer character 
                        index++;                    // advance to next input character
                    } else {
                        tmp_data[data_index] = '\0';
                        break;
                    }
                }
            }
                    // run command with data
                    uint8_t code_index = 0;
                    while(code_index <= command.number_of_commands){
                        if(strcmp(Code::commands[code_index].code, tmp_code) == 0){
                            execute_command_as_string(code_index, tmp_data;
                            break;
                        } else {
                            code_index++;
                        }
                    }
                index++;          // Advance to next charachter in input
            return 0;  // Return false if no end deimiter not read successfully
            
        }
        

    }
  private:
    size_t string_limit;    // Maximum length of input string, local constant
    char* read_code(size_t &index){ 
        size_t tmp_code_len = Code::Command::max_length;
        char tmp_code[tmp_code_len];
        size_t code_index = 0;
        while(true){	                       
            if(isalpha(input[index]) &&         // Make sure it is a valid characther
                    input[index] != Code::Delimiter::v_start[0]) {     
                tmp_code[code_index] = input[index];	// read designator into tmp buffer
                code_index++;                           // advance to next buffer character
                index++;                                // advance to next input character
            } else {                             // Break if it is not a valid character or 
                tmp_code[code_index] = '\0';       
                break;	// If bad nonalpha or end char encounter
            }
        }
    }
    char* read_data(){
        
    }

};




        bool run_input(char* input_string){                                               // Returns true if all commands read successfully
            char input[STRING_LIMIT];
            strcpy(input, input_string);
            static constexpr uint8_t tmp_len = 16;						// designate 16 bytes for read buffer
            char tmp_delimiter[tmp_len];
            char tmp_code[tmp_len];
            char tmp_data[tmp_len];
            uint8_t tmp_len = 0; 
            uint16_t end_index = strlen(input);
            uint16_t index = 0;
            uint8_t data_index = 0;
            uint8_t code_index = 0;
            using namespace Code;

            // Step 1: Verify start delimiter, exit if invalid
            memset(tmp_delimiter, 0, tmp_len);
            strcpy(tmp_delimiter, Delimiter::start);
            tmp_len = strlen(Delimiter::start);
            for(int i = 0; i < tmp_len; i++){
                if(input[index] == Delimiter::start[i]){		
                    index++;	
                } else {
                    return 0;					
                }		
            }
            // This will advance index to the character after the start delimiter

            // Step 2: Verify end delimiter, exit if invalid
            tmp_len = strlen(Delimiter::end);
            memset(tmp_delimiter, 0, tmp_len);
            strcpy(tmp_delimiter, Delimiter::start);
            unit8_t reverse_index = end_index;
            for(int i = strlen(tmp_delimiter); i > 0; i--){		// check from end to start
                if(input[reverse_index] == tmp_delimiter[i]){		
                    reverse_index--;	
                } else {
                    return 0;			
                }		
            }
            // This will advance reverse_index to the character before the end delimiter

            // The data to read can now be constrained between the start and end delimiters

            // Siep 3: Read commands and data between the delimiters
            while(index <= reverse_index){	

            // A) get command code
                memset(tmp_code, 0, tmp_len);
                memset(tmp_delimiter, 0, tmp_len);
                strcpy(tmp_delimiter, Delimiter::v_start);
                code_index = 0;				// go to start of data buffer
                while(true){				// until data encountered
                    if(isalpha(input[index]) && input[index] != tmp_delimiter[0]){
                        tmp_code[code_index] = input[index];	// read designator into tmp buffer
                        code_index++;                        // advance to next buffer character
                        index++;                             // advance to next input character
                    } else {
                        tmp_code[code_index] = '\0';       
                        break;	// If bad nonalpha or end char encounter
                    }
                }
                // This will leave off at the first character of the value delimiter

            // B) get the data 
        
                // Check the rest of the start delimiter (or just advance to the next char if single char delimiter)
                for(int i = 0; i < strlen(tmp_delimiter); i++){
                    if(input[index] == tmp_delimiter[i]){		
                        index++;	
                    } else {
                        return 0;					
                    }		
                }
                // This will advance index to the character after the value start delimiter

                // Reset buffers and prepare to read data
                memset(tmp_data 0, tmp_len);
                memset(tmp_delimiter, 0, tmp_len);
                strcpy(tmp_delimiter, Delimiter::v_end);

                // Read data until end delimiter
                data_index = 0;
                while(true){					  
                    if(input[index] != tmp_delimiter[0]){	
                        tmp_data[data_index] = input[index];
                        data_index++;               // advance to next buffer character 
                        index++;                    // advance to next input character
                    } else {
                        tmp_data[data_index] = '\0';
                        break;
                    }
                }
            }
                    // run command with data
                    uint8_t code_index = 0;
                    while(code_index <= command.number_of_commands){
                        if(strcmp(Code::commands[code_index].code, tmp_code) == 0){
                            execute_command_as_string(code_index, tmp_data;
                            break;
                        } else {
                            code_index++;
                        }
                    }
                index++;          // Advance to next charachter in input
            return 0;  // Return false if no end deimiter not read successfully
            
        }
}

#endif