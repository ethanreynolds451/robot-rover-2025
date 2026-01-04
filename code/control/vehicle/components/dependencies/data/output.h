#ifndef OUTPUT_h
#define OUTPUT_h

namespace OutputStates {
    bool brake = true;			//br
    bool reverse = false;		//rv
    bool s_reverse = false;		//srv
    bool shift_up = false;		//su
    uint8_t speed_ = 0;			//sp
    uint8_t s_speed = 0;		//ssp
    uint8_t f_speed = 0;        //fan
    namespace Default {
        static const bool brake = true;		
        static const bool reverse = false;		
        static const bool s_reverse = false;		
        static const bool shift_up = false;		
        static const uint8_t speed_ = 0;		
        static const uint8_t s_speed = 0;	
        static const uint8_t f_speed = 0;
    };
    void reset(){
        brake = brake;
        reverse = reverse;
        s_reverse = s_reverse;
        shift_up = shift_up;
        speed_ = speed_;
        s_speed = s_speed;
        f_speed = f_speed;
    }
}

#endif