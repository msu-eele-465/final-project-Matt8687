#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <vector>
#include "../lib/i2c_libs/lcd_i2c.h"
#include "../lib/i2c_libs/rtc_i2c.h"
#include "../lib/i2c_libs/lm92_i2c.h"
#include "led_array_control.h"

hw_timer_t * timer = NULL;
volatile int Heartbeat_state = 0;
volatile int ISR_counter = 0;
String time_read;
byte* top;
byte* bottom;

String convert_to_string(byte array[], int size);
void IRAM_ATTR onTimer();

void setup() {
  // Start serial output for debugging
  Serial.begin(115200);
  Serial.println("Serial Started.");
  // initialize onboard Blue LED for heartbeat
  pinMode(2, OUTPUT);

  // initialize i2c devices
  lcd_init();
  rtc_set_date(6, 5, 25);
  rtc_set_time(9, 25, 00);
  LAC_init();

  timer = timerBegin(0, 80, true);           	// timer 0, prescalar: 80, UP counting
  timerAttachInterrupt(timer, &onTimer, true); 	// Attach interrupt
  timerAlarmWrite(timer, 100000, true);  		// Match value= 1000000 for 1 sec. delay.
  timerAlarmEnable(timer);           			// Enable Timer with interrupt (Alarm Enable)
  
}
 
void loop() {

  lcd_clear();
  byte data[17] = "                ";
  rtc_get_time_bytes(data);
  lm92_temp_btes(data);
  bottom = data;
  lcd_writeBottom(bottom);

  Serial.println(convert_to_string(data, sizeof(data)-1));
  
  LAC_update();
  
}

String convert_to_string(byte array[], int size){
  String rtn;
  for(int i = 0; i<size; i++){
    rtn += (char)array[i];
  }
  return rtn;

}

void IRAM_ATTR onTimer(){
  // ----- Hearbeat -----
  if(ISR_counter % 10 == 0){
    Heartbeat_state ^= 1;
    digitalWrite(2, Heartbeat_state);
  }
  ISR_counter++;

}
