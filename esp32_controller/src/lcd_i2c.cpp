#include "lcd_i2c.h"

/*
 * @file lcd_i2c.cpp
 * @brief module created in order to write over i2c with the lcd controller
 * 
 * Using I2C this file allows for the writing of bytes to the msp4302310
 * that controls the LCD pannel. The code for the controller is in 
 * /i2c_lcd/app of the main repository for this project.
*/

#define LCD_DELAY_TIME 5

void lcd_clear(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(LCD_DELAY_TIME);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(LCD_DELAY_TIME);
    }
    Wire.write('H');
    delay(LCD_DELAY_TIME);
    Wire.write('G');
    delay(LCD_DELAY_TIME);
    byte error = Wire.endTransmission();
}

void lcd_init() {
    Wire.begin();
    Wire.setClock(800000);
    lcd_clear();

}

void lcd_startWriteTop(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(LCD_DELAY_TIME);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(LCD_DELAY_TIME);
    }
    Wire.write('G');
    delay(LCD_DELAY_TIME);
    byte error = Wire.endTransmission();
}

void lcd_startWriteBottom(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(LCD_DELAY_TIME);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(LCD_DELAY_TIME);
    }
    Wire.write('H');
    delay(LCD_DELAY_TIME);
    byte error = Wire.endTransmission();
}

void lcd_writeTop(byte top[16]){
    lcd_startWriteTop();
    byte error = 1;
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(LCD_DELAY_TIME);
    Wire.write('T');
    for(int i = 0; i<16; i++){
        Wire.write(top[i]);
        delay(LCD_DELAY_TIME);
    }
    error = Wire.endTransmission();
}

void lcd_writeBottom(byte bottom[16]){
    lcd_startWriteBottom();
    byte error = 1;
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(LCD_DELAY_TIME);
    Wire.write('B');
    for(int i = 0; i<16; i++){
        Wire.write(bottom[i]);
        delay(LCD_DELAY_TIME);
    }
    error = Wire.endTransmission();
}