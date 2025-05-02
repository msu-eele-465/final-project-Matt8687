#include "lcd_i2c.h"

void lcd_clear(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(50);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(50);
    }
    Wire.write('H');
    delay(50);
    Wire.write('G');
    delay(50);
    byte error = Wire.endTransmission();
}

void lcd_init() {
    Serial.begin(115200);
    Serial.println("Serial Started.");

    Serial.println("Starting I2C Wire...");
    Wire.begin();
    Wire.setClock(800000);
    lcd_clear();
    Serial.println("I2C Wire Started.");

}

void lcd_startWriteTop(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(50);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(50);
    }
    Wire.write('G');
    delay(50);
    byte error = Wire.endTransmission();
}

void lcd_startWriteBottom(){
    byte address = 0x40;
    Wire.beginTransmission(address);
    delay(50);
    for(int i = 0; i<16; i++){
        Wire.write('z');
        delay(50);
    }
    Wire.write('H');
    delay(50);
    byte error = Wire.endTransmission();
}

void lcd_writeTop(byte top[16]){
    lcd_startWriteTop();
    byte error = 1;
    byte address = 0x40;
    Serial.println("Sending LCD Data");
    Wire.beginTransmission(address);
    delay(50);
    Wire.write('T');
    for(int i = 0; i<16; i++){
        Wire.write(top[i]);
        delay(50);
    }
    error = Wire.endTransmission();
    if (error != 0) {
        Serial.println("Unable to write to 0x40");
    } else {
        Serial.println("Data sent successfully.");
    }
}

void lcd_writeBottom(byte bottom[16]){
    lcd_startWriteBottom();
    byte error = 1;
    byte address = 0x40;
    Serial.println("Sending LCD Data");
    Wire.beginTransmission(address);
    delay(50);
    Wire.write('B');
    for(int i = 0; i<16; i++){
        Wire.write(bottom[i]);
        delay(50);
    }
    error = Wire.endTransmission();
    if (error != 0) {
        Serial.println("Unable to write to 0x40");
    } else {
        Serial.println("Data sent successfully.");
    }
}