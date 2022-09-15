
#include "button_control.h"
#include "ws2812.h"
#include "settings.h"
#include "config.h"

#define BTN_PIN_1 0
#define BTN_PIN_2 2

GButton BTN_LEFT(BTN_PIN_1);
GButton BTN_RIGHT(BTN_PIN_2);

void init_button_left()
{
    BTN_LEFT.setDebounce(90);
    BTN_LEFT.setTimeout(300);
    BTN_LEFT.setType(HIGH_PULL);
    BTN_LEFT.setDirection(NORM_OPEN);
    BTN_LEFT.setTickMode(AUTO);
}

void init_button_right()
{
    BTN_RIGHT.setDebounce(90);
    BTN_RIGHT.setTimeout(300);
    BTN_RIGHT.setType(HIGH_PULL);
    BTN_RIGHT.setDirection(NORM_OPEN);
    BTN_RIGHT.setTickMode(AUTO);
}

void init_button(void)
{
    init_button_left();
    init_button_right();
}

// uint32_t color_ws2812(uint8_t color)
// {
//     uint32_t _color;
//     switch (color)
//     {
//     case RED | 1:
//         _color = RED;
//         break;
//     case GREEN | 2:
//         _color = GREEN;
//         break;
//     case BLUE | 3:
//         _color = BLUE;
//         break;
//     case WHITE | 4:
//         _color = WHITE;
//         break;
//     case YELLOW | 5:
//         _color = YELLOW;
//         break;
//     case CYAN | 6:
//         _color = CYAN;
//         break;
//     case MAGENTA | 7:
//         _color = MAGENTA;
//         break;
//     case PURPLE | 8:
//         _color = PURPLE;
//         break;
//     case ORANGE | 9:
//         _color = ORANGE;
//         break;
//     case PINK | 10:
//         _color = PINK;
//         break;
//     case GRAY | 11:
//         _color = GRAY;
//         break;
//     default:
//         break;
//     }

//     return _color;
// }

void task_button(void)
{

    if (BTN_LEFT.isClick())
    {
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
}