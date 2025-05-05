#ifndef LM92_I2C_H
#define LM92_I2C_H

#include <Arduino.h>
#include <Wire.h>

float lm92_read_temperature();
void lm92_temp_btes(byte store[], int offset = 0);

#endif