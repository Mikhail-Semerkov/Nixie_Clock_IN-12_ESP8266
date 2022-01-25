#include <Arduino.h>
#include <GyverTimer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <microDS3231.h>
///////////////////////////////////////

GTimer TimerSecond(MS);

// Time UDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;
int timeZone = 3;
bool Synch_UDP;
bool UDP_Error;


// RTC Time
MicroDS3231 RTC_Clock;

String Lamp_Time_Current;

String Time_str;

void setup_synch_clock_udp()
{
  Synch_UDP = false;
  UDP_Error = false;
  TimerSecond.setInterval(1000);
}

void SYNCH_CLOCK()
{
  if (TimerSecond.isReady())
  {
    Time_str = RTC_Clock.getTimeString();
    Count_Dots++;

    if (Count_Dots == 2)
    {
      Count_Dots = 0;
    }
  }
  Nixie_Time(Time_str, Brightness_Lamp);
}