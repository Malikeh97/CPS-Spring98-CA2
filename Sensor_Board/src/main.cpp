#include <Arduino.h>
#include <LM35.h>
#include <hcsr04.h>

#define TRIG_PIN 6
#define ECHO_PIN 7

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
LM35 temp(A0);
void setup(){
    Serial.begin(9600);
}

void loop() {
//    Serial.print("Distance - "); 
    Serial.println(hcsr04.ToString());
//    Serial.print("Temp - ");  //Send a text to serial
//    Serial.print("#");
    Serial.println(temp.cel()); //It gets the temperature in celcius and send to serial
    
    delay(250);
}



