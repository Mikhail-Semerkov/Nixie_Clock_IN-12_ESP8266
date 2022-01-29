

void UDP_SYNCH()
{
  if (WiFi.status() == WL_CONNECTED && Synch_UDP == false)
  {
    Serial.println("WiFi Connect!");
    timeClient.begin();
    timeClient.setTimeOffset(3600 * timeZone);

    if (!timeClient.update())
    {
      Serial.println("UDP Error!");
      timeClient.forceUpdate();
      UDP_Error = true;
    }
    else
    {
      UDP_Error = false;
    }

    if (UDP_Error == false && UDP_Error == false)
    {

      formattedDate = timeClient.getFormattedDate();
      int splitT = formattedDate.indexOf("T");
      dayStamp = formattedDate.substring(0, splitT);
      Serial.print("UDP DATE: ");
      Serial.println(dayStamp);

      timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
      Serial.print("UDP TIME: ");
      Serial.println(timeStamp);

      RTC_Clock.setHMSDMY(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(), dayStamp.substring(8, 10).toInt(), dayStamp.substring(5, 7).toInt(), dayStamp.substring(0, 4).toInt());

      if (UDP_Error == false)
      {
        Synch_UDP = true;
      }
    }
  }
}

void setup_synch_clock_udp()
{
  Synch_UDP = false;
  UDP_Error = false;
  TimerSecond.setInterval(1000);
  TimerEffects.setInterval(100);

  httpUpdater.setup(&server, "/");

  server.begin();
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

  if (Time_str != "")
  {
    if (TimerEffects.isReady() && Brightness_Lamp != count_effects)
    {
      count_effects++;
    }
    Nixie_Time(Time_str, count_effects);
  }

  server.handleClient();
}