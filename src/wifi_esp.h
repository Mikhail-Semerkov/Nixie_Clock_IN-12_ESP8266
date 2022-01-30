void wifi_connect()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (!WiFi.getAutoConnect())
    {
        WiFi.setAutoConnect(true);
    }
    if (!WiFi.getAutoReconnect())
    {
        WiFi.setAutoReconnect(true);
    }

    WiFi.begin("Padavan 2.4", "46684668");
}

void setup_wifi_esp()
{
    wifi_connect();
}
