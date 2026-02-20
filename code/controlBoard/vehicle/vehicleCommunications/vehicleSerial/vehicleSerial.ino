// Debugging the serial module because it is outputting garbage

#include "vehicleSerial.h"

RobotSerial computer(115200);

void setup(){
    computer.begin();
    computer.add("Hello ");
    computer.add("World!\n");
    computer.add("This is a really long string of text that will not fit in a single 64 byte packet. It is being added to test functionality of the packet management feature.\n");
    if(computer.add("This text will overflow the buffer. It is being added to verify that the safeguards to handle buffer overflow are in place and working properly. asfhqiluwehriluwahflkuahweslukfghawelsujgfluqweagfahjklfdasbhjsdfgbfdjklassdbfjklsdhajkflhewaskljdfghklweajsgflkjashdfeilqwhflukqjweghaqgfliueghsaklfjhweqailsuekfhwlqeiufgh")){
      Serial.println("This shouldn't be happening"); 
    } else {
      Serial.println("A packet wasn't added because it was too long"); 
    }
    delay(1000); 
}

void loop(){
    computer.update();
    delay(1000); 
}
