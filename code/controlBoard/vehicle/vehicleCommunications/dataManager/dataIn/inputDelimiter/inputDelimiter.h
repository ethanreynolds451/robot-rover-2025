#ifndef INPUTDELIMITER_h
#define INPUTDELIMITER_h

namespace InputDelimiter {
    static constexpr char* start = "{";
    static constexpr char* end = "}";
    static constexpr char* v_start = "[";
    static constexpr char* v_end = "]";
    static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)

    // This shouldn't be here, figure out alternative approach
    const size_t string_limit = 256;            // Maximum length of input string including null terminator

    // Functions to verify delimiters in a data string

    bool verify(const char* input, const char* delimiter, size_t start){               // Returns true if delimiter is valid
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
        return verify(input, start, 0);
    }

    bool end_valid(const char* input){
        return verify(input, end, strlen(input) - strlen(end));
    }

    bool data_start_valid(const char* input, size_t current_index){
        return verify(input, v_start, current_index);
    }   
    
    bool data_end_valid(const char* input, size_t current_index){
        return verify(input, v_end, current_index);
    }



};

#endif