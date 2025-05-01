#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include "rtc_i2c.h"

String rtc_get_date(){
    DS3231 rtc;
    bool h12Flag, pmFlag, CenturyBit;
    String date = ((String)rtc.getDate()) + "/" + ((String)rtc.getMonth(CenturyBit)) + "/" + ((String)rtc.getYear());
    return date;
}

void rtc_set_date(int day, int month, int year){
    DS3231 rtc;
    bool h12Flag, pmFlag;
    rtc.setDate(day);
    rtc.setMonth(month);
    rtc.setYear(year);
}

String rtc_get_time(){
    DS3231 rtc;
    bool h12Flag, pmFlag;
    String time = ((String)rtc.getHour(h12Flag, pmFlag)) + ":" + ((String)rtc.getMinute()) + ":" + ((String)rtc.getSecond());
    return time;
}

void rtc_set_time(int hour, int minute, int second){
    DS3231 rtc;
    bool h12Flag, pmFlag;
    rtc.setHour(hour);
    rtc.setMinute(minute);
    rtc.setSecond(second);

}