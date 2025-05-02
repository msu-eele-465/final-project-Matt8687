#ifndef RTC_I2C_H
#define RTC_I2C_H

#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>

String rtc_get_date();
void rtc_set_date(int day, int month, int year);
int rtc_get_time();
void rtc_get_time_bytes(byte store[], int offset = 8);
void rtc_set_time(int hour, int minute, int second);

#endif