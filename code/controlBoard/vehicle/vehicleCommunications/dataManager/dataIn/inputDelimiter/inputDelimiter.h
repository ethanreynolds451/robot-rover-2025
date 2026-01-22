#ifndef INPUTDELIMITER_h
#define INPUTDELIMITER_h

namespace InputDelimiter {
    static constexpr char* start = "{";
    static constexpr char* end = "}";
    static constexpr char* v_start = "[";
    static constexpr char* v_end = "]";
    static constexpr uint8_t max_length = 1;    // Max length of delimiters including null terminator (2 characters)
};

#endif