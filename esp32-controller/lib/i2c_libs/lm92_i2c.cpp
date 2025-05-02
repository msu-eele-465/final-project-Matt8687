#include "lm92_i2c.h"

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