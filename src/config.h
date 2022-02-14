void loadConfiguration(const char *filename, Config &config)
{

    while (!SPIFFS.begin())
    {
        Serial.println(F("Failed to initialize SD library"));
        delay(1000);
    }
    File configFile = SPIFFS.open("/config.json", "r");
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(configFile);

    if (!root.success())
        Serial.println(F("Failed to read file, using default configuration"));

    config._mode_wifi = root["mode_wifi"] | "WIFI_AP";
    config._wifi_ssid = root["wifi_ssid"] | "";
    config._wifi_pass = root["wifi_pass"] | "";
    config._wifi_ssid_ap = root["wifi_ssid_ap"] | "Nixie Clock";
    config._wifi_pass_ap = root["wifi_pass_ap"] | "12345678";
    config._dhcp = root["dhcp"] | "0";
    config._static_ip = root["static_ip"] | "192.168.1.1";
    config._static_mask = root["static_mask"] | "255.255.252.0";
    config._static_gataway = root["static_gataway"] | "192.168.1.1";
    config._hostname = root["hostname"] | "Nixie_Clock";

    configFile.close();
}

void saveConfiguration(const char *filename, const Config &config)
{

    SPIFFS.remove(filename);

    File file = SPIFFS.open("/config.json", "a");
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return;
    }

    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["mode_wifi"] = config._mode_wifi;
    root["ip_addr"] = config._ip_addr;
    root["mask_addr"] = config._mask_addr;
    root["gataway_addr"] = config._gataway_addr;
    root["wifi_ssid"] = config._wifi_ssid;
    root["wifi_pass"] = config._wifi_pass;
    root["wifi_ssid_ap"] = config._wifi_ssid_ap;
    root["wifi_pass_ap"] = config._wifi_pass_ap;
    root["dhcp"] = config._dhcp;
    root["static_ip"] = config._static_ip;
    root["static_mask"] = config._static_mask;
    root["static_gataway"] = config._static_gataway;
    root["hostname"] = config._hostname;

    if (root.printTo(file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }

    file.close();
}

void printFile(const char *filename)
{

    File file = SPIFFS.open("/config.json", "r");
    if (!file)
    {
        Serial.println(F("Failed to read file"));
        return;
    }

    while (file.available())
    {
        Serial.print((char)file.read());
    }
    Serial.println();
    file.close();
}

void func_default_settings()
{

    Serial.println("Reset ESP32");
    Serial.println("Read default config");
    SPIFFS.remove("/config.json");
    ESP.restart();
}

void setup_config()
{

    loadConfiguration("/config.json", config);
}
