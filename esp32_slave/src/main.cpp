#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_array_control.h"
#include "web_server.h"

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
}

void IRAM_ATTR onTimer(){
  // ----- Hearbeat -----
  if(ISR_counter % 10 == 0){
    Heartbeat_state ^= 1;
    digitalWrite(2, Heartbeat_state);
  }
  ISR_counter++;

}