#ifndef LAC_H
#define LAC_H


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

void LAC_init();
void LAC_update(void *stuff);
void LAC_scroll(char* message,int delays);
void LAC_update_string(String change, int size);
void LAC_update_mode(int mode);

#endif