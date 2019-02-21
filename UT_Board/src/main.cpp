#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>


union {
  float f;
  byte b[4];
} u_x, u_y;

int ADXLAddress = 0x6E; // Device address in which is also included the 8th bit for selecting the mode, read in this case.
#define X_Axis_Register_DATAX0 0xa // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX1 0xb // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX2 0xc // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX3 0xd // Hexadecima address for the DATAX0 internal register.

#define Y_Axis_Register_DATAY0 0x28 // Hexadecima address for the DATAX0 internal register.
#define Y_Axis_Register_DATAY1 0x29 // Hexadecima address for the DATAX0 internal register.
#define Y_Axis_Register_DATAY2 0x2a // Hexadecima address for the DATAX0 internal register.
#define Y_Axis_Register_DATAY3 0x2b // Hexadecima address for the DATAX1 internal register.

#define Power_Register 0x0 // Power Control Register

byte getData(int reg){
  byte data ;
  Wire.beginTransmission(ADXLAddress); // Begin transmission to the Sensor 
  //Ask the particular registers for data
  Wire.write(reg);
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  
  Wire.requestFrom(ADXLAddress,1); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=1) {  // 
    data = Wire.read(); // Reads the data from the register   
  }
  return data;
}

float calc_x_out() {
  u_x.b[0] = getData(X_Axis_Register_DATAX0);
  u_x.b[1] = getData(X_Axis_Register_DATAX1);
  u_x.b[2] = getData(X_Axis_Register_DATAX2);
  u_x.b[3] = getData(X_Axis_Register_DATAX3); 
  return u_x.f;
}

float calc_y_out() {
  u_y.b[0] = getData(Y_Axis_Register_DATAY0);
  u_y.b[1] = getData(Y_Axis_Register_DATAY1);
  u_y.b[2] = getData(Y_Axis_Register_DATAY2);
  u_y.b[3] = getData(Y_Axis_Register_DATAY3);
  return u_y.f;
}


void setup() {
  Wire.begin(); // Initiate the Wire 
  Serial.begin(9600);
  delay(100); 
  // Enable measurement
  Wire.beginTransmission(ADXLAddress);
  Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  Wire.write(1);  
  Wire.endTransmission();
}

void loop() {
  float x_out = calc_x_out();
  float y_out = calc_y_out();
  
  float total = y_out*y_out + x_out*x_out;
  Serial.print(total);
  delay(100);
}