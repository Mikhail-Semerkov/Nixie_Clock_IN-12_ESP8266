
#include "button_control.h"
#include "ws2812.h"
#include "settings.h"
#include "config.h"
#include "nixie_lamp.h"

#define BTN_PIN_1 0
#define BTN_PIN_2 2

GButton BTN_LEFT(BTN_PIN_1);
GButton BTN_RIGHT(BTN_PIN_2);

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

void start_effects()
{
    static unsigned long timer;
    static bool start_eff;
}

void one_click_button()
{
    static unsigned long timer;
    static bool start_eff;

    if (BTN_LEFT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t < 50)
        {
            Serial.println("effect_t++");
            settings.object.ws2812_s.effect_t++;
        }
        else
        {
            Serial.println("effect_t max count");
        }

        save_config();
    }

    if (BTN_RIGHT.isClick())
    {
        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t > 0)
        {
            Serial.println("effect_t--");
            settings.object.ws2812_s.effect_t--;
        }
        else
        {
            Serial.println("effect_t mix count");
        }

        save_config();
    }

    if (start_eff)
    {
        settings.object.nixie_s.mode = CURRENT_EFFECT;

        if (millis() - timer > 5000)
        {
            timer = millis();
            settings.object.nixie_s.mode = NORMAL;
            start_eff = false;
        }
    }
}

void hold_click_button()
{
    static unsigned long timer;
    static bool start_eff;


    if (BTN_LEFT.isHolded())
    {
        Serial.println("LEFT CLICK HOLD");

        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t < 50)
        {
            Serial.println("effect_t++");
            settings.object.ws2812_s.effect_t++;
        }
        else
        {
            Serial.println("effect_t max count");
        }

        //save_config();
    }

    if (BTN_RIGHT.isHolded())
    {
        Serial.println("RIGHT CLICK HOLD");

        start_eff = true;
        timer = millis();

        if (settings.object.ws2812_s.effect_t > 0)
        {
            Serial.println("effect_t--");
            settings.object.ws2812_s.effect_t--;
        }
        else
        {
            Serial.println("effect_t mix count");
        }

        //save_config();
    }

    if (start_eff)
    {
        settings.object.nixie_s.mode = CURRENT_EFFECT;

        if (millis() - timer > 5000)
        {
            timer = millis();
            settings.object.nixie_s.mode = NORMAL;
            start_eff = false;
        }
    }
}

void task_button(void)
{
    // one_click_button();
    hold_click_button();
}