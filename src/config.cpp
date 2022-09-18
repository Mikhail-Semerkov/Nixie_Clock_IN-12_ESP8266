#include "config.h"
#include "settings.h"
#include "trace.h"

void loadConfiguration(const char *filename, settings_t &settings)
{

    while (!SPIFFS.begin())
    {
        serial_trace("Failed to initialize SD library\r\n");
        delay(1000);
    }

    File configFile = SPIFFS.open(filename, "r");
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(configFile);

    if (!root.success())
    {
        serial_trace("Failed to read file, using default configuration\r\n");
        settings.object.ws2812_s.effect_t = 0;
        settings.object.ws2812_s.color_t = 0;
        settings.object.ws2812_s.brightness_t = 20;
        settings.object.ws2812_s.speed_t = 3000;

        save_config();
    }
        

    settings.object.ws2812_s.effect_t = (uint8_t)root["effect"];
    settings.object.ws2812_s.color_t = uint32_t(root["color"]);
    settings.object.ws2812_s.brightness_t = (uint8_t)(root["brightness"]);
    settings.object.ws2812_s.speed_t = (uint16_t)(root["speed"]);

    configFile.close();
}

bool saveConfiguration(const char *filename, const settings_t &settings)
{

    SPIFFS.remove(filename);

    File file = SPIFFS.open(filename, "a");
    if (!file)
    {
        serial_trace("Failed to create file\r\n");
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
        serial_trace("Failed to write to file\r\n");
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
        serial_trace("Failed to read file\r\n");
        return;
    }
    serial_trace("\r\n--------------------\r\n");
    while (file.available())
    {
        char data = (char)file.read();

        serial_trace("%c", data);
        
        
        if (data == ',')
        {
            serial_trace("\r\n--------------------\r\n");
        }
    }
    serial_trace("\r\n--------------------\r\n\r\n");
    file.close();
}

void func_default_settings(void)
{

    serial_trace("Reset ESP32\r\n");
    serial_trace("Read default config\r\n");
    SPIFFS.remove(FILE_CONFIG);
    // ESP.restart();
}

void init_config(void)
{
    loadConfiguration(FILE_CONFIG, settings);
}

void save_config(void)
{
    while (!saveConfiguration(FILE_CONFIG, settings)){ }
    serial_trace("CONFIG SAVE");
}

void print_file(void)
{
    printFile(FILE_CONFIG);
}
