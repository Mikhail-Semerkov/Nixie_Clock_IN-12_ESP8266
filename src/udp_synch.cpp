#include "udp_synch.h"
#include "rtc_module.h"
#include <ota_wifi.h>
#include "trace.h"

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
        serial_trace("WiFi Connect!\r\n");
        timeClient.begin();
        timeClient.setTimeOffset(3600 * timeZone);

        if (!timeClient.update())
        {
            serial_trace("UDP Error!\r\n");
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
            serial_trace("UDP DATE: %s\r\n", dayStamp);

            timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
            serial_trace("UDP TIME: %s\r\n", timeStamp);

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