#include "udp_synch.h"
#include "rtc_module.h"
#include <wifi_esp.h>

// Time UDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;
int timeZone = 3;
bool Synch_UDP;
bool UDP_Error;

void udp_synch_time()
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

            DateTime data;

            data.hour = timeClient.getHours();
            data.minute = timeClient.getMinutes();
            data.second = timeClient.getSeconds();

            data.date = dayStamp.substring(8, 10).toInt();
            data.month = dayStamp.substring(5, 7).toInt();
            data.year = dayStamp.substring(0, 4).toInt();

            synch_rtc(data);

            if (UDP_Error == false)
            {
                Synch_UDP = true;
            }
        }
    }
}