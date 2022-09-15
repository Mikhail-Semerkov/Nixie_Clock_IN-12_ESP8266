#include "ws2812.h"
#include "settings.h"

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);

void select_effects(uint8_t effect, uint32_t color, uint8_t brightness, uint16_t speed)
{
    if (ws2812fx.getMode() != effect || ws2812fx.getColor() != color || ws2812fx.getBrightness() != brightness || ws2812fx.getSpeed() != speed)
    {
        ws2812fx.setMode(effect);
        ws2812fx.setColor(color);
        ws2812fx.setBrightness(brightness);
        ws2812fx.setSpeed(speed);

        if (settings.object.ws2812_s.mode_ws2812 == MODE_NORMAL)
        {
            settings.object.ws2812_s.effect_t = effect;
            settings.object.ws2812_s.color_t = color;
            settings.object.ws2812_s.brightness_t = brightness;
            settings.object.ws2812_s.speed_t = speed;
        }

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
    // select_effects(settings.object.ws2812_s.effect_t, settings.object.ws2812_s.color_t, settings.object.ws2812_s.brightness_t, settings.object.ws2812_s.speed_t);
    ws2812fx.start();
}

void mode_ws2812(mode_ws2812_t mode)
{

    switch (mode)
    {
    case MODE_ERROR | 0:
        select_effects(FX_MODE_STROBE, RED, settings.object.ws2812_s.brightness_t, 200);
        break;

    case MODE_OK | 1:
        break;

    case MODE_NORMAL | 2:
        select_effects(settings.object.ws2812_s.effect_t, settings.object.ws2812_s.color_t, settings.object.ws2812_s.brightness_t, settings.object.ws2812_s.speed_t);
        break;

    case MODE_OFF | 3:
        break;

    default:
        break;
    }
}

void task_ws2812(void)
{
    ws2812fx.service();
    mode_ws2812((mode_ws2812_t)settings.object.ws2812_s.mode_ws2812);
}