// Debugging the serial module because it is outputting garbage

#include "vehicleSerial.h"

RobotSerial computer(115200);

void setup(){
    computer.begin();
    computer.add("Hello ");
    delay(5000); 
    computer.add("World!\n");
    //computer.add("This is a really long string of text that will not fit in a single 64 byte packet. It is being added to test functionality of the packet management feature.\n");
}

void loop(){
    computer.update();
}
