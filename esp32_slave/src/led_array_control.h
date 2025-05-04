#ifndef LAC_H
#define LAC_H


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_array_control.h"

void LAC_init();
void LAC_update(void *stuff);
void LAC_scroll(char* message,int delays);
void LAC_update_string(String change, int size, int posision = 1);
void LAC_update_mode(int mode);

#endif