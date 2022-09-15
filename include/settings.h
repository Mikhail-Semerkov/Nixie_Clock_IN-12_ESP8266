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

struct nixie
{
    uint8_t mode;
    uint8_t object;
};


struct settings_t
{
    struct objects
    {
        struct wifi_ wifi_s;
        struct ws2812_ ws2812_s;
        struct nixie nixie_s;

    } object;

};

extern settings_t settings;