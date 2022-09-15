
#include "button_control.h"
#include "ws2812.h"

#define BTN_PIN_1 0
#define BTN_PIN_2 2

GButton BTN_LEFT(BTN_PIN_1);
GButton BTN_RIGHT(BTN_PIN_2);

void init_button_left()
{
    BTN_LEFT.setDebounce(90); // настройка антидребезга (по умолчанию 80 мс)
    BTN_LEFT.setTimeout(300); // настройка таймаута на удержание (по умолчанию 500 мс)
    // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (BTN_PIN --- КНОПКА --- GND)
    // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
    // по умолчанию стоит HIGH_PULL
    BTN_LEFT.setType(HIGH_PULL);
    // NORM_OPEN - нормально-разомкнутая кнопка
    // NORM_CLOSE - нормально-замкнутая кнопка
    // по умолчанию стоит NORM_OPEN
    BTN_LEFT.setDirection(NORM_OPEN);
    // MANUAL - нужно вызывать функцию tick() вручную
    // AUTO - tick() входит во все остальные функции и опрашивается сама!
    BTN_LEFT.setTickMode(AUTO);
}

void init_button_right()
{
    BTN_RIGHT.setDebounce(90); // настройка антидребезга (по умолчанию 80 мс)
    BTN_RIGHT.setTimeout(300); // настройка таймаута на удержание (по умолчанию 500 мс)
    // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (BTN_PIN --- КНОПКА --- GND)
    // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
    // по умолчанию стоит HIGH_PULL
    BTN_RIGHT.setType(HIGH_PULL);
    // NORM_OPEN - нормально-разомкнутая кнопка
    // NORM_CLOSE - нормально-замкнутая кнопка
    // по умолчанию стоит NORM_OPEN
    BTN_RIGHT.setDirection(NORM_OPEN);
    // MANUAL - нужно вызывать функцию tick() вручную
    // AUTO - tick() входит во все остальные функции и опрашивается сама!
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
    static uint8_t efects;
    BTN_LEFT.tick();
    BTN_RIGHT.tick();

    if (BTN_LEFT.isClick())
    {
        Serial.println("Click LEFT");
        Serial.printf("Color = %d\r\n", efects);
        efects++;
    }

    if (BTN_RIGHT.isClick())
    {
        Serial.println("Click RIGHT");
        Serial.printf("Color = %d\r\n", efects);
        efects--;
    }

    select_effects(efects, RED, 20, 3000);
}