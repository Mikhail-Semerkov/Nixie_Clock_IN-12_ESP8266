#include "ws2812.h"

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);

ws2812_s ws2812_s_struct;

void select_effects(uint8_t effect, uint32_t color, uint8_t brightness, uint16_t speed)
{
    if (ws2812fx.getMode() != effect || ws2812fx.getColor() != color || ws2812fx.getBrightness() != brightness || ws2812fx.getSpeed() != speed)
    {
        ws2812fx.setMode(effect);
        ws2812fx.setColor(color);
        ws2812fx.setBrightness(brightness);
        ws2812fx.setSpeed(speed);
        Serial.printf("mode = %d, color = 0x%6X, bright = %d, speed = %d\r\n", effect, color, brightness, speed);
    }
}

void set_collor(uint32_t color)
{
    ws2812fx.setColor(color);
}

void init_ws2812(void)
{
    ws2812fx.init();
    ws2812fx.setBrightness(0);
    ws2812fx.start();
}

void task_ws2812(void)
{
    ws2812fx.service();
}

void mode_ws2812(mode_ws2812_t mode)
{
    static mode_ws2812_t status;

    if (mode != status)
    {
        switch (mode)
        {
        case MODE_ERROR | 0:
            status = MODE_ERROR;
            select_effects(15, RED, 20, 500);
            Serial.println("WS2812 MODE_ERROR");
            break;

        case MODE_OK | 1:
            break;

        case MODE_NORMAL | 2:
            status = MODE_NORMAL;
            select_effects(ws2812_s_struct.effect_t, ws2812_s_struct.color_t, ws2812_s_struct.brightness_t, ws2812_s_struct.speed_t);
            Serial.println("WS2812 MODE_NORMAL");
            break;

        case MODE_OFF | 3:
            break;

        default:
            break;
        }
    }
}