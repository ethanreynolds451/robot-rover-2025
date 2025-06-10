#include "libraries.h"
#include "definitions.h"
#include "functions.h"

// Data format
// {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]}

void setup(){
   setup_function(); 
}

void loop(){
  sensor.read_ultrasonic();
  for(int i = 0; i < number_of_HCSR04; i++){
    Serial.print(Pin::HCSR04[i + 1]); 
    Serial.print(": "); 
    Serial.print(sensor.value.ultrasonic[i]);    
    Serial.print(", "); 
  }
  Serial.println();  
  delay(500); 
//    if(loop_delay.passed()){
//        update_sensors(); 
//    }
//    if(send_delay.passed()){
//        send_data();
//    }
}
