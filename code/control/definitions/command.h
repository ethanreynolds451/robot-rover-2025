#ifndef COMMAND_h
#define COMMAND_h

namespace command {
    static const uint8_t number_of = 7;     // Number of valid commands
    struct command_struct {                 // Structure for command mapping
      uint8_t index;
      char code[4];
    };
    // Create an array of commands with their corresponding codes
    const command_struct commands[number_of] = {    
        {0, "br"},		// brake
        {1, "rv"},		// reverse
        {2, "srv"},		// steer reverse
        {3, "su"},		// shift up
        {4, "sp"},		// speed
        {5, "ssp"},		// steer speed
        {6, "fan"}    // fan speed
    };
};

#endif