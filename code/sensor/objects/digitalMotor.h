void start_steering(){
    pinMode(Pin::steer_position, INPUT);    // No way to perform initial check, maybe with gyro / compass later?
}

void read_steering () {
    value::steer_position = steer_position.get_degrees();
}