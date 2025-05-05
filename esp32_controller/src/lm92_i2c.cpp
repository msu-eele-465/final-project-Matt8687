#include "lm92_i2c.h"

/*
 * @file lm92_i2c.cpp
 * @brief module created to read and convert temp from the lm92 device
 * 
 * The primary purpose of this file is to mainly keep the main.cpp file
 * clear of cluttering funcitons, but is imperative to have. It reads
 * two bytes from the temperature sensor and converts it into a float.
 * It also has a fuction to write that float to a byte array for later
 * printing (to the lcd and led array(s)).
*/

float lm92_read_temperature(){
  float temperature;
  byte a, b;
  Wire.beginTransmission(0x48);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(0x48, 2);
  a = Wire.read();
  b = Wire.read();

  int upper = (a << 1) | (b >> 7);
  int lower = ((b >> 3) & 0x00000111b)*6.25;

  // Serial.print(upper, DEC);
  // Serial.print(".");
  // Serial.println(lower, DEC);
  temperature = (float)upper + ((float)lower/100);

  return temperature;
}

void lm92_temp_btes(byte store[], int offset){

  float temperature = lm92_read_temperature();
  char temp;

  // ---
  temp = ((String)(int)(temperature/10))[0];
  store[0+offset] = temp;
  temperature -= 10 * (int)(temperature/10);
  // ---
  temp = ((String)(int)(temperature))[0];
  store[1+offset] = temp;
  temperature *= 100;
  // ---
  store[2+offset] = '.';
  // ---
  temp = ((String)(int)(temperature/10))[0];
  store[3+offset] = temp;
  temperature -= 10 * (int)(temperature/10);
  // ---
  temp = ((String)(int)(temperature))[0];
  store[4+offset] = temp;
}