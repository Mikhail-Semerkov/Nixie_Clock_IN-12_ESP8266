#include "ws2812.h"

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);

void select_effects(uint8_t mode, uint32_t color, uint8_t brightness, uint16_t speed)
{
    while (ws2812fx.getMode() != mode || ws2812fx.getColor() != color || ws2812fx.getBrightness() != brightness || ws2812fx.getSpeed() != speed)
    {
        ws2812fx.setMode(mode);
        ws2812fx.setColor(color);
        ws2812fx.setBrightness(brightness);
        ws2812fx.setSpeed(speed);
        break;
    }
}

void set_collor(uint32_t color)
{
    ws2812fx.setColor(color);
}

void setup_ws2812()
{
    ws2812fx.init();
    ws2812fx.setBrightness(0);
    ws2812fx.start();
    select_effects(15, 0xFF0000, 20, 3000);
}

void loop_ws2812()
{
    ws2812fx.service();
}
