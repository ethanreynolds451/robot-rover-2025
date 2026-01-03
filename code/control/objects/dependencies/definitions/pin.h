// Compiled successfully 2025-01-02

#ifndef PIN_h
#define PIN_h

namespace Pin {
	//Digital
	// pins 0 and 1 are used for serial communication
	static constexpr uint8_t brake = 2;				// relay 1
	static constexpr uint8_t headlight = 3;			// power_module_1, pwm
	static constexpr uint8_t reverse_1 = 4;			// relay 2
	static constexpr uint8_t fan = 5;				// pwm
	static constexpr uint8_t shift_2 = 6;		  	// relay 6
	static constexpr uint8_t s_reverse_1 = 7;		// relay 5
	static constexpr uint8_t s_reverse_2 = 8;		// relay 4
	static constexpr uint8_t speed_ = 9;			// power_module_2, pwm
	static constexpr uint8_t s_speed = 10;			// power_module_3, pwm
	static constexpr uint8_t power_module_4 = 11;	// power_module_4, pwm
	static constexpr uint8_t reverse_2 = 12;		// relay 3
	static constexpr uint8_t shift_1 = 13;   		// relay 7
	//Analog
	static constexpr uint8_t digit_0 = A0;			// This digit is broken and can only display 1, can use for voltage (two horizontal segments burnt out)
	static constexpr uint8_t digit_1 = A1;
	static constexpr uint8_t digit_2 = A2;
	static constexpr uint8_t digit_3 = A3;
	static constexpr uint8_t SDA = A4;
	static constexpr uint8_t SCL = A5;
    static constexpr uint8_t thermistor = A6;
	static constexpr uint8_t battery_monitor = A7;
};

#endif