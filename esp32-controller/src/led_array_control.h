#ifndef LAC_H
#define LAC_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

void LAC_init();
void LAC_update();
void LAC_scroll(char* message,int delays);

#endif