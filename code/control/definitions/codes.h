#ifndef CODES_h
#define CODES_h

namespace code {
    static const uint8_t number_of_commands = 7;     // Number of valid commands
    static const uint8_t number_of_data = 3;        // Number of data points
    struct code_struct {                 // Structure for code mapping
      uint8_t index;
      char code[4];
    };
    // Create an array of commands with their corresponding codes
    const code_struct commands[number_of_commands] = {    
        {0, "br"},		// brake
        {1, "rv"},		// reverse
        {2, "srv"},		// steer reverse
        {3, "su"},		// shift up
        {4, "sp"},		// speed
        {5, "ssp"},		// steer speed
        {6, "fan"}    // fan speed
    };
    const code_struct data[number_of_codes] = {
        {0, "tmp"},    // internal temperature
        {1, "vlt"},    // battery voltage
        {2, "pct"}     // battery percentage
    };
};

#endif