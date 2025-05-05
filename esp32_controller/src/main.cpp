#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_array_control.h"
#include "web_server.h"
#include "rtc_i2c.h"
#include "lm92_i2c.h"
#include "lcd_i2c.h"

/*
 * @file main.cpp
 * @breif Origins of the primary setup and primary running loop.alignas
 * 
 * This file sets up the secondary running task loop for the 
 * Led Array Control (LAC), sets up the wifi hotspot & server,
 * as well as is where the rtc devices are read and wrote from.
*/

static const char *TAG_MAIN = "Main";
void IRAM_ATTR onTimer();

hw_timer_t * timer = NULL;
volatile int Heartbeat_state = 0;
volatile int ISR_counter = 0;

void setup() {
  Serial.begin(115200);
  ESP_LOGI(TAG_MAIN, "Setting up LAC task...");
  LAC_init();
  ESP_LOGI(TAG_MAIN, "Finished!]\nStarting main event loop.");
  web_server_setup();
  rtc_init();
  lcd_init();

  // initialize onboard Blue LED for heartbeat
  pinMode(2, OUTPUT);

  timer = timerBegin(0, 80, true);           	// timer 0, prescalar: 80, UP counting
  timerAttachInterrupt(timer, &onTimer, true); 	// Attach interrupt
  timerAlarmWrite(timer, 100000, true);  		// Match value= 1000000 for 1 sec. delay.
  timerAlarmEnable(timer);           			// Enable Timer with interrupt (Alarm Enable)

}

void loop() {
  ESP_LOGI(TAG_MAIN, "Running...");
  web_server_loop();
  byte data[] = "12:45:00        ";
  rtc_get_time_bytes(data, 0);
  LAC_update_string(convert_to_string(data, 8), 8, 2);
  lm92_temp_btes(data, 0);
  LAC_update_string(convert_to_string(data, 5), 5, 3);

  for(int i = 0; i<16; i++){
    data[i] = ' ';
  }
  rtc_get_time_bytes(data);
  lm92_temp_btes(data);
  lcd_writeBottom(data);
}

void IRAM_ATTR onTimer(){
  // ----- Hearbeat -----
  if(ISR_counter % 10 == 0){
    Heartbeat_state ^= 1;
    digitalWrite(2, Heartbeat_state);
  }
  ISR_counter++;

}