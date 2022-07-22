#include "rtc_module.h"

MicroDS3231 RTC_Clock;


String rtc_get_time()
{
    if(RTC_Clock.begin())
    {
        return RTC_Clock.getTimeString();
    }

    return "";
}

String rtc_get_data()
{
    if (RTC_Clock.begin())
    {
        return RTC_Clock.getDateString();
    }

    return "";
}

void synch_rtc(DateTime dt)
{
    RTC_Clock.setTime(dt);
}
