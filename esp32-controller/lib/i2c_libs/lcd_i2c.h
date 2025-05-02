#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <Arduino.h>
#include <Wire.h>

void lcd_clear();
void lcd_init();
void lcd_startWriteTop();
void lcd_startWriteBottom();
void lcd_writeTop(byte top[16]);
void lcd_writeBottom(byte bottom[16]);

#endif