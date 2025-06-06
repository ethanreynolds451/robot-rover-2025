#include "/Users/ethanreynolds/Library/Mobile Documents/com~apple~CloudDocs/Temporary Local Files/Capstone/Coding/Components/HC-SR04/HCSR04_ultrasonic_sensor/src/HCSR04.h"

HCSR04 hc(5, 6); //initialisation class HCSR04 (trig pin , echo pin)

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(hc.dist()); // return curent distance in serial
    delay(60);                 // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}
