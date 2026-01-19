#ifndef DATAMANAGER_h
#define DATAMANAGER_h

#include "dataIn/dataIn.h"
#include "dataOut/dataOut.h"

// Only purpose of this is to merge the modular read and write classes for easier access

class dataManager {
  public:
    dataIn input;
    dataOut output;
    dataManager(size_t input_string_limit, size_t output_string_limit) 
      : input(input_string_limit), output(output_string_limit) {}
};

#endif