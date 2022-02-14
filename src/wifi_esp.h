void wifi_connect()
{

    DHCP = bool(config._dhcp.toInt());

    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);

    if (WiFi.getHostname() != String(config._hostname).c_str())
    {
        WiFi.setHostname(String(config._hostname).c_str());
    }

    if (DHCP == true)
    {
        Serial.println();
        local_IP.fromString(config._static_ip);
        gateway.fromString(config._static_gataway);
        subnet.fromString(config._static_mask);

        Serial.println("Static Local Ok");
        WiFi.config(local_IP, gateway, subnet);
    }

    if (String(config._mode_wifi) == "WIFI_STA")
    {

        Serial.println();
        Serial.println("MODE STA");

        WiFi.mode(WIFI_STA);
        WiFi.begin(config._wifi_ssid.c_str(), config._wifi_pass.c_str());

        Serial.print("\nConnecting to: ");
        Serial.println(config._wifi_ssid);
        uint8_t i = 0;

        while (WiFi.status() != WL_CONNECTED && i++ < 20)
            delay(500);

        if (i == 21)
        {
            Serial.print("Could not connect to");
            Serial.println(config._wifi_ssid);
            // while (1)
            delay(500);
        }

        Serial.print("Ready! You are connected\n");
        Serial.print("IP: ");
        Serial.print(WiFi.localIP());
        Serial.println();
        Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
        Serial.println();
    }
    else if (String(config._mode_wifi) == "WIFI_AP")
    {

        Serial.println();
        Serial.println("MODE AP");

        WiFi.mode(WIFI_AP);
        WiFi.softAPConfig(local_IP_AP, gateway_AP, subnet_AP);
        WiFi.softAP(config._wifi_ssid_ap.c_str(), config._wifi_pass_ap.c_str());

        Serial.print("Ready! You are connected\n");
        Serial.print("IP: ");
        Serial.print(local_IP_AP);
        Serial.println();
    }
}

void setup_wifi_esp()
{
    wifi_connect();
}
