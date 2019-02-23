#include <Arduino.h>
#include <AltSoftSerial.h>
#include <LiquidCrystal.h>
#include<Wire.h>

using namespace std;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
AltSoftSerial altSerial;
String UT_data ;
String distance;
String tempeture;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 3);
  
  altSerial.begin(9600);
  
}

void loop() {
  lcd.clear();
  if(Serial.available()>= 4){
    UT_data = Serial.read();
    lcd.setCursor(0,0);
    lcd.print("UTData: ");
    lcd.print(UT_data);
  }
  if (altSerial.available()) {
    distance = altSerial.readStringUntil('\n');
    lcd.setCursor(0,1);
    lcd.print("Distance: ");
    lcd.print(distance);
    tempeture = altSerial.readStringUntil('\n');
    lcd.setCursor(0,2);
    lcd.print("Tempeture: ");
    lcd.print(tempeture);
    
  }
  delay(80);
}