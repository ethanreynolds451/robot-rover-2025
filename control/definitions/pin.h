#ifndef PIN_h
#define PIN_h

namespace Pin {
	//Digital
	static constexpr uint8_t brake = 2;
	static constexpr uint8_t reverse_1 = 4;
	static constexpr uint8_t reverse_2 = 12;
	static constexpr uint8_t s_reverse_1 = 7;
	static constexpr uint8_t s_reverse_2 = 8;
	static constexpr uint8_t shift_1 = 13;      // Would be 5 but needed for fan pwm
	static constexpr uint8_t shift_2 = 6;
	static constexpr uint8_t speed_ = 9;
	static constexpr uint8_t s_speed = 10;
	static constexpr uint8_t fan = 5;
	static constexpr uint8_t headlight = 11;
	//Analog
	static constexpr uint8_t SDA = A4;
	static constexpr uint8_t SCL = A5;
    static constexpr uint8_t thermistor = A0;
};

#endif