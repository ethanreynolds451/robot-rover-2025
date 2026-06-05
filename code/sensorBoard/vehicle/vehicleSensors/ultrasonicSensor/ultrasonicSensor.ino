#include "ultrasonicSensor.h"

#define TRIG 2
#define ECHO 3
#define POLL_INTERVAL 100

using ultrasonicSensor = ultrasonic_sensor::ultrasonic_object;
ultrasonicSensor testUltrasonic(TRIG, ECHO);

unsigned long timer = millis(); 

void setup(){
  testUltrasonic.initialize(); 
  Serial.begin(115200);
  Serial.println("Iniciando Sensor"); 
  testUltrasonic.begin();
  Serial.println("Sensor Iniciado");

  ultrasonic_sensor::ERROR error = testUltrasonic.get_error();
  if(error != ultrasonic_sensor::ERROR::NO_ERROR){
    Serial.print("Se produjo un error: ");
    Serial.println(static_cast<int>(error));
  } else {
    Serial.println("No error reported");
  }

  ultrasonic_sensor::STATE state = testUltrasonic.get_state();
  Serial.print("Estado del sensor: ");
  Serial.println(static_cast<int>(state));
}

void loop(){
  testUltrasonic.update();
  
  if((millis() - timer) > POLL_INTERVAL){
    //Serial.println("Polling sensor"); 
    testUltrasonic.poll();
    timer = millis(); 
  }
  
  ultrasonic_sensor::DATA data = testUltrasonic.peek();
  if(data.distance.is_new){
    Serial.println("New data available"); 
    testUltrasonic.get_distance();
    Serial.println(data.distance.value); 
  }
}
