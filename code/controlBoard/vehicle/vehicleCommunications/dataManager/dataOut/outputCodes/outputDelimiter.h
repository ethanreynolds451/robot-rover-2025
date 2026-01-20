#ifndef OUTPUTDELIMITER_h
#define OUTPUTDELIMITER_h

// Communication parsing delimiters
namespace OutputDelimiter {
    static constexpr char* start = "{";
    static constexpr char* end = "}";
    static constexpr char* v_start = "[";
    static constexpr char* v_end = "]";
    static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)
};

#endif
