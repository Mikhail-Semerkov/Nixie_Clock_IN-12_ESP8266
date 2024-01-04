
#include "button_control.h"
#include "ws2812.h"
#include "settings.h"
#include "config.h"
#include "nixie_lamp.h"
#include "trace.h"

#define BTN_PIN_1 0
#define BTN_PIN_2 2

GButton BTN_RIGHT(BTN_PIN_1);
GButton BTN_LEFT(BTN_PIN_2);

void init_button_left()
{
    BTN_LEFT.setDebounce(90);
    BTN_LEFT.setTimeout(500);
    BTN_LEFT.setType(HIGH_PULL);
    BTN_LEFT.setDirection(NORM_OPEN);
    BTN_LEFT.setTickMode(AUTO);
}

void init_button_right()
{
    BTN_RIGHT.setDebounce(90);
    BTN_RIGHT.setTimeout(500);
    BTN_RIGHT.setType(HIGH_PULL);
    BTN_RIGHT.setDirection(NORM_OPEN);
    BTN_RIGHT.setTickMode(AUTO);
}

void init_button(void)
{
    init_button_left();
    init_button_right();
}

void one_click_button()
{
    static unsigned long timer;
    static bool start_eff;
    static uint8_t index_color;

    if (settings.object.nixie_s.object == EFFECTS && BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t < 50)
        {
            serial_trace("effect_t++\rn");
            settings.object.ws2812_s.effect_t++;
        }
        else
        {
            serial_trace("effect_t max count\rn");
        }

        save_config();
    }

    if (settings.object.nixie_s.object == EFFECTS && BTN_RIGHT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t > 0)
        {
            serial_trace("effect_t--\r\n");
            settings.object.ws2812_s.effect_t--;
        }
        else
        {
            serial_trace("effect_t mix count\r\n");
        }
        save_config();
    }

    if (settings.object.nixie_s.object == COLOR && BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (index_color < 7)
        {
            serial_trace("color_t++\r\n");
            index_color++;
            settings.object.ws2812_s.color_t = color(index_color);
        }
        else
        {
            serial_trace("color_t max count\r\n");
        }

        save_config();
    }

    if (settings.object.nixie_s.object == COLOR && BTN_RIGHT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (index_color > 0)
        {
            serial_trace("color_t--\r\n");
            index_color--;
            settings.object.ws2812_s.color_t = color(index_color);
        }
        else
        {
            serial_trace("color_t mix count\r\n");
        }
        save_config();
    }

    if (settings.object.nixie_s.object == COLOR && BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.color_t < 50)
        {
            serial_trace("color_t++\r\n");
            settings.object.ws2812_s.color_t++;
        }
        else
        {
            serial_trace("color_t max count\r\n");
        }

        save_config();
    }

    if (settings.object.nixie_s.object == BRIGHTNESS && BTN_RIGHT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.brightness_t > 0)
        {
            serial_trace("brightness_t--\r\n");
            settings.object.ws2812_s.brightness_t = settings.object.ws2812_s.brightness_t - 10;
        }
        else
        {
            serial_trace("brightness_t mix count\r\n");
        }
        save_config();
    }

    if (settings.object.nixie_s.object == BRIGHTNESS && BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.brightness_t < 250)
        {
            serial_trace("brightness_t++\r\n");
            settings.object.ws2812_s.brightness_t = settings.object.ws2812_s.brightness_t + 10;
        }
        else
        {
            serial_trace("brightness_t max count\r\n");
        }

        save_config();
    }

    if (settings.object.nixie_s.object == SPEED && BTN_RIGHT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.speed_t > 100)
        {
            serial_trace("speed_t--\r\n");
            settings.object.ws2812_s.speed_t = settings.object.ws2812_s.speed_t - 100;
        }
        else
        {
            serial_trace("speed_t mix count\r\n");
        }
        save_config();
    }

    if (settings.object.nixie_s.object == SPEED && BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.speed_t < 9900)
        {
            serial_trace("speed_t++\r\n");
            settings.object.ws2812_s.speed_t = settings.object.ws2812_s.speed_t + 100;
        }
        else
        {
            serial_trace("brightness_t max count\r\n");
        }

        save_config();
    }

    ///////////////////////////HOLD////////////////////////////
    if (BTN_LEFT.isHolded())
    {
        start_eff = true;
        timer = millis();
        // settings.object.nixie_s.object++;
        if (settings.object.nixie_s.object++ >= 4)
        {
            settings.object.nixie_s.object = 4;
        }
    }

    if (BTN_RIGHT.isHolded())
    {
        start_eff = true;
        timer = millis();
        if (settings.object.nixie_s.object-- <= 1)
        {
            settings.object.nixie_s.object = 1;
        }
    }
    /////////////////////////////TIMER////////////////////////////////
    if (start_eff)
    {
        settings.object.nixie_s.mode = CURRENT_EFFECT;

        if (millis() - timer > 5000)
        {
            timer = millis();
            settings.object.nixie_s.mode = NORMAL;
            start_eff = false;
            settings.object.nixie_s.object = 0;
        }
    }
}

void task_button(void)
{

    if(BTN_LEFT.isHold() && BTN_RIGHT.isHold())
    {
        serial_trace("RESTART\r\n");
        ESP.restart();
    }

    one_click_button();
}