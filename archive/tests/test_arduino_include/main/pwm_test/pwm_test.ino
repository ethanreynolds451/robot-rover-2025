// This code increments the brightness of an LED and annother PWM to test the functionality of a PWM-controlled device

#define PWM_PIN 9
#define LED_PIN 10

int period = 3;     // Period of incrementaiton in seconds

void setup(){
    // Set PWM pin to output
    pinMode(PWM_PIN, OUTPUT);
    // Set on-board LED (pin 13) to output
    pinMode(LED_PIN, OUTPUT);
}

void loop(){
    // Increment the PWM for LED and on-board LED
    for(int duty_cycle = 0; duty_cycle <= 255; duty_cycle++){
        analogWrite(PWM_PIN, duty_cycle);
        analogWrite(LED_PIN, duty_cycle); // Turn on the on-board LED
        delay(period * 1000 / 256); // Delay to create a smooth transition
    }
    for(int duty_cycle = 255; duty_cycle >= 0; duty_cycle--){
        analogWrite(PWM_PIN, duty_cycle);
        analogWrite(LED_PIN, duty_cycle); // Turn off the on-board LED
        delay(period * 1000 / 256); // Delay to create a smooth transition
    }
}
