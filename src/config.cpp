#include "config.h"
#include "settings.h"

void loadConfiguration(const char *filename, settings_t &settings)
{

    while (!SPIFFS.begin())
    {
        Serial.println(F("Failed to initialize SD library"));
        delay(1000);
    }

    File configFile = SPIFFS.open(filename, "r");
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(configFile);

    if (!root.success())
        Serial.println(F("Failed to read file, using default configuration"));

    settings.object.ws2812_s.effect_t = (uint8_t)root["effect"];
    settings.object.ws2812_s.color_t = uint32_t(root["color"]);
    settings.object.ws2812_s.brightness_t = (uint8_t)(root["brightness"]);
    settings.object.ws2812_s.speed_t = (uint16_t)(root["speed"]);

    //Serial.printf("TEST EFFECTS LOAD = %d\r\n", settings.object.ws2812_s.effect_t);

    // settings.config._mode_wifi = root["mode_wifi"] | "WIFI_STA";
    // settings.config._wifi_ssid = root["wifi_ssid"] | "Padavan 2.4";
    // settings.config._wifi_pass = root["wifi_pass"] | "46684668";
    // settings.config._wifi_ssid_ap = root["wifi_ssid_ap"] | "Nixie Clock";
    // settings.config._wifi_pass_ap = root["wifi_pass_ap"] | "12345678";
    // settings.config._dhcp = root["dhcp"] | "0";
    // settings.config._static_ip = root["static_ip"] | "192.168.1.1";
    // settings.config._static_mask = root["static_mask"] | "255.255.252.0";
    // settings.config._static_gataway = root["static_gataway"] | "192.168.1.1";
    // settings.config._hostname = root["hostname"] | "Nixie_Clock";

    configFile.close();
}

bool saveConfiguration(const char *filename, const settings_t &settings)
{

    SPIFFS.remove(filename);

    File file = SPIFFS.open(filename, "a");
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return false;
    }

    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["effect"] = (String)(settings.object.ws2812_s.effect_t);
    root["color"] = (String)(settings.object.ws2812_s.color_t);
    root["brightness"] = (String)(settings.object.ws2812_s.brightness_t);
    root["speed"] = (String)(settings.object.ws2812_s.speed_t);

    // root["mode_wifi"] = settings.config._mode_wifi;
    // root["ip_addr"] = settings.config._ip_addr;
    // root["mask_addr"] = settings.config._mask_addr;
    // root["gataway_addr"] = settings.config._gataway_addr;
    // root["wifi_ssid"] = settings.config._wifi_ssid;
    // root["wifi_pass"] = settings.config._wifi_pass;
    // root["wifi_ssid_ap"] = settings.config._wifi_ssid_ap;
    // root["wifi_pass_ap"] = settings.config._wifi_pass_ap;
    // root["dhcp"] = settings.config._dhcp;
    // root["static_ip"] = settings.config._static_ip;
    // root["static_mask"] = settings.config._static_mask;
    // root["static_gataway"] = settings.config._static_gataway;
    // root["hostname"] = settings.config._hostname;

    if (root.printTo(file) == 0)
    {
        Serial.println(F("Failed to write to file"));
        return false;
    }

    file.close();
    return true;
}

void printFile(const char *filename)
{

    File file = SPIFFS.open(FILE_CONFIG, "r");
    if (!file)
    {
        Serial.println(F("Failed to read file"));
        return;
    }
    Serial.println();
    Serial.println("--------------------");
    while (file.available())
    {
        char data = (char)file.read();
        Serial.print(data);
        if (data == ','){
            Serial.println();
            Serial.println("--------------------");
        }
    }
    Serial.println();
    Serial.println("--------------------");
    file.close();
}

void func_default_settings()
{

    Serial.println("Reset ESP32");
    Serial.println("Read default config");
    SPIFFS.remove(FILE_CONFIG);
    ESP.restart();
}

void init_config(void)
{

    loadConfiguration(FILE_CONFIG, settings);
}


void save_config(void)
{
    while(!saveConfiguration(FILE_CONFIG, settings)){ }
    Serial.println("CONFIG SAVE");
}


void print_file(void)
{
    printFile(FILE_CONFIG);
}
