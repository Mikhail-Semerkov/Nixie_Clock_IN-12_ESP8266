void wifi_connect()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);

    WiFi.begin("Padavan 2.4", "46684668");

    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     delay(500);
    //     Serial.print(".");
    // }

    Serial.println("");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}




