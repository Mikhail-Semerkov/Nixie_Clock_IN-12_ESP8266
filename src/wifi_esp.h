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
    if (WiFi.getHostname() != HostName.c_str())
    {
        WiFi.setHostname(HostName.c_str());
    }

    WiFi.begin(SSID.c_str(), PASS.c_str());
}

void setup_wifi_esp()
{
    wifi_connect();
}
