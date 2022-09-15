#include "Arduino.h"

struct wifi_
{
    bool connected;    // true coonected ok
    uint8_t mode_wifi; //
};

struct ws2812_
{
    uint8_t mode_ws2812;
    uint8_t effect_t;
    uint32_t color_t;
    uint8_t brightness_t;
    uint16_t speed_t;
};

struct settings_t
{
    struct objects
    {
        struct wifi_ wifi_s;
        struct ws2812_ ws2812_s;

    } object;

    struct config
    {
        // String _ws2812_effects;
        // String _ws2812_color;
        // String _ws2812_brightness;
        // String _ws2812_speed;

        // String _mode_wifi;
        // String _ip_addr;
        // String _mask_addr;
        // String _gataway_addr;
        // String _wifi_ssid;
        // String _wifi_pass;
        // String _wifi_ssid_ap;
        // String _wifi_pass_ap;
        // String _dhcp;
        // String _static_ip;
        // String _static_mask;
        // String _static_gataway;
        // String _hostname;
    } config;
};

extern settings_t settings;