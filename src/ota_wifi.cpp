#include "udp_synch.h"
#include "rtc_module.h"
#include "ota_wifi.h"
#include "ws2812.h"
#include "settings.h"
#include "trace.h"

typedef struct wifi_data_t
{
    wl_status_t state;
    uint8_t mode;
    String ip_addr;
}wifi_data;


wifi_data wifiData;

uint8_t timeout_connect = 5; // second

const char *host = "nixie-clock";
const char *update_path = "/ota";
const char *update_username = "admin";
const char *update_password = "admin";
const char *sta_ssid = "Keenetic";
const char *sta_password = "46684668";
const char *hostname = "NIXIE_CLOCK";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

String IpAddress2String(const IPAddress &ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

void init_ota(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(sta_ssid, sta_password);

    if (WiFi.getHostname() != hostname)
    WiFi.setHostname(hostname);

    MDNS.begin(host);
    httpUpdater.setup(&httpServer, update_path, update_username, update_password);
    httpServer.begin();
    MDNS.addService("http", "tcp", 80);
}

void check_wiwi(void)
{
    const wl_status_t status = WiFi.status();

    if (wifiData.state != status)
    {
        wifiData.state = status;

        if(wifiData.state == WL_CONNECTED)
        {
            settings.object.wifi_s.connected = true;
            serial_trace("WIFI: WL_CONNECTED\r\n");
            settings.object.ws2812_s.mode_ws2812 = MODE_NORMAL;
        }
        else
        {
            settings.object.wifi_s.connected = false;
            serial_trace("WIFI: %d\r\n", wifiData.state);
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
        }
    }
}

void task_ota(void)
{
    check_wiwi();

    httpServer.handleClient();
    if (settings.object.wifi_s.connected)
    {
        MDNS.update();
    }
}