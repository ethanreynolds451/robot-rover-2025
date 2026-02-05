// Debugging the serial module because it is outputting garbage

#include "vehicleSerial.h"

RobotSerial computer(115200, 64);

void setup(){
    computer.begin();
}

void loop(){
    computer.write("Hello World!\n");
    delay(1000);
}
