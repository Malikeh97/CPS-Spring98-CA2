x#include <Arduino.h>
#include <LM35.h>
#include <hcsr04.h>
#include <Ultrasonic.h>

#define TRIG_PIN 7
#define ECHO_PIN 6

//HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

LM35 temp(A0);
void setup(){
    Serial.begin(9600, SERIAL_8E1);
    ultrasonic.setTimeout(40000UL);
}

void loop() {
//    Serial.print("Distance - "); 
   // Serial.println(hcsr04.ToString());
   Serial.println(ultrasonic.read());
//    Serial.print("Temp - ");  //Send a text to serial
//    Serial.print("#");
    Serial.println(temp.cel()); //It gets the temperature in celcius and send to serial
    
    delay(250);
}



