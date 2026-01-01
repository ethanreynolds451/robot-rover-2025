bool start_ultrasonic(){
    bool return_val = true;
    pinMode(Pin::HCSR04[0], OUTPUT);
    for(int i = 1; i < number_of_ultrasonic; i++){
        pinMode(Pin::HCSR04[i], INPUT);
        delay(10);
        if (ultrasonic.dist(i) == 0) {      // They are pulled down so will return 0 if not connected
        error::ultrasonic[i] = 4;   // address error for sensor not connected
        return_val = false;
        }
    }
    return return_val;
}

void read_ultrasonic(uint8_t index = 0) {
    if (index == 0){
        for (int i = 0; i < number_of_ultrasonic; i++) {
        value::ultrasonic[i] = ultrasonic.dist(i);
        }
    } else if (index <= number_of_ultrasonic) {
        value::ultrasonic[index - 1] = ultrasonic.dist(index - 1);
    }
}

HCSR04 ultrasonic;      // Library allows for direct definition of array, no need to use pointers