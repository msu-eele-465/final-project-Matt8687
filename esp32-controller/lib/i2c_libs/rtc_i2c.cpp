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

int rtc_get_time(){
    DS3231 rtc;
    bool h12Flag, pmFlag;
    return rtc.getHour(h12Flag, pmFlag)*10000 + rtc.getMinute()*100 + rtc.getSecond();
}

void rtc_get_time_bytes(byte store[], int offset){
    int time = rtc_get_time();
    char temp;

    temp = ((String)(int)(time/100000))[0];
    store[0+offset] = temp;
    time -= 100000 * (int)(time/100000);
    // ---
    temp = ((String)(int)(time/10000))[0];
    store[1+offset] = temp;
    time -= 10000 * (int)(time/10000);
    // ---
    store[2+offset] = ':';
    // ---
    temp = ((String)(int)(time/1000))[0];
    store[3+offset] = temp;
    time -= 1000 * (int)(time/1000);
    // ---
    temp = ((String)(int)(time/100))[0];
    store[4+offset] = temp;
    time -= 100 * (int)(time/100);
    // ---
    store[5+offset] = ':';
    // ---
    temp = ((String)(int)(time/10))[0];
    store[6+offset] = temp;
    time -= 10 * (int)(time/10);
    // ---
    temp = ((String)(int)(time))[0];
    store[7+offset] = temp;
}

void rtc_set_time(int hour, int minute, int second){
    DS3231 rtc;
    bool h12Flag, pmFlag;
    rtc.setHour(hour);
    rtc.setMinute(minute);
    rtc.setSecond(second);

}