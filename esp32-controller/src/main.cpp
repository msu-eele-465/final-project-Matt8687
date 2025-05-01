#include <Arduino.h>
#include <Wire.h>
#include "lcd_i2c.h"
#include "rtc_i2c.h"


void setup() {
  Serial.begin(115200);
  // while(!Serial){}
  Serial.println("Serial Started.");

  lcd_init();
  rtc_set_date(6, 5, 25);
  rtc_set_time(9, 25, 00);

}
 
void loop() {
  Serial.print(rtc_get_date());
  Serial.print(" | ");
  Serial.println(rtc_get_time());

  lcd_clear();

  byte top[] = "How is you Matt?";
  lcd_writeTop(top);
  
  byte bottom[] = "I hope good...  ";
  lcd_writeBottom(bottom);
  sleep(3);
}