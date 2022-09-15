#include "udp_synch.h"
#include "rtc_module.h"
#include "ota_wifi.h"
#include "ws2812.h"
#include "settings.h"


uint8_t timeout_connect = 5; // second

const char *host = "nixie-clock";
const char *update_path = "/ota";
const char *update_username = "admin";
const char *update_password = "admin";
const char *sta_ssid = "Padavan 2.4";
const char *sta_password = "46684668";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;


void init_ota(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(sta_ssid, sta_password);
    static uint8_t count_connect;


    while (WiFi.waitForConnectResult(timeout_connect * 1000) != WL_CONNECTED)
    {
        Serial.println("WiFi failed, retrying = " + String(count_connect + 1));
        WiFi.begin(sta_ssid, sta_password);
        if (count_connect++ >= 2)
        {
            settings.object.wifi_s.connected = false;
            Serial.println("Connected ERR");
            break;
        }
    }

    if (WiFi.status())
    {
        settings.object.wifi_s.connected = true;
        Serial.println("Start STA");
        settings.object.wifi_s.mode_wifi = WIFI_STA;
        if (!WiFi.getAutoReconnect())
        {
            WiFi.setAutoReconnect(true);
        }

        MDNS.begin(host);
        httpUpdater.setup(&httpServer, update_path, update_username, update_password);
        httpServer.begin();
        MDNS.addService("http", "tcp", 80);
        Serial.print("Local IP = ");
        Serial.println(WiFi.localIP());
        Serial.printf("Open http://%s.local%s username '%s' and password '%s'\n", host, update_path, update_username, update_password);

    }
    else
    {
        settings.object.wifi_s.connected = false;
        WiFi.mode(WIFI_AP);
        settings.object.wifi_s.mode_wifi = WIFI_AP;
        WiFi.softAP("NIXIE_CLOCK", "");
        Serial.println("Start AP");
        httpUpdater.setup(&httpServer, update_path, update_username, update_password);
        httpServer.begin();
        Serial.printf("Open http://192.168.4.1%s username '%s' and password '%s'\n", update_path, update_username, update_password);

    }
}

void check_wiwi(void)
{
    static wl_status_t connect;

    if (connect != WiFi.status())
    {
        switch (WiFi.status())
        {
        case WL_NO_SHIELD | 255:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_NO_SHIELD");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_IDLE_STATUS | 0:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_IDLE_STATUS");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_NO_SSID_AVAIL | 1:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_NO_SSID_AVAIL");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_SCAN_COMPLETED | 2:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_SCAN_COMPLETED");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_CONNECTED | 3:
            connect = WiFi.status();
            settings.object.wifi_s.connected = true;
            Serial.println("Connected WL_CONNECTED");
            settings.object.ws2812_s.mode_ws2812 = MODE_NORMAL;
            break;
        case WL_CONNECT_FAILED | 4:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_CONNECT_FAILED");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_CONNECTION_LOST | 5:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_CONNECTION_LOST");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_WRONG_PASSWORD | 6:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_WRONG_PASSWORD");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;
        case WL_DISCONNECTED | 7:
            connect = WiFi.status();
            settings.object.wifi_s.connected = false;
            Serial.println("Connected WL_DISCONNECTED");
            settings.object.ws2812_s.mode_ws2812 = MODE_ERROR;
            break;

        default:
            break;
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