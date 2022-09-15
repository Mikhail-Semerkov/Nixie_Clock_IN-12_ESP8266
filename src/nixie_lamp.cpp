#include "nixie_lamp.h"
#include "rtc_module.h"
#include "settings.h"
#include "ws2812.h"

String Time_str, Data_str;

uint8 Key_Lamp[5] = {Nixie_Dots, Nixie_Lamp_1, Nixie_Lamp_2, Nixie_Lamp_3, Nixie_Lamp_4};
ShiftRegister74HC595<2> sr(Data_Pin, Clock_Pin, Latch_Pin);

int Brightness_Lamp = 20;
int Brighness_SK = 7200;
int Count_Dots;
bool Dots_Enabled;

int count_animation_start, count_animation_end, count_attenuation_start, count_attenuation_end;
bool flag_animation_start, flag_animation_end, flag_attenuation_start, flag_attenuation_end, flag_time, flag_date;
int mode_clock = 0;

String return_time()
{
    return Time_str;
}
String return_data()
{
    return Data_str;
}

void Nixie_Time(String Time, int Brightness, bool AutoDots)
{
    char char_buf[4];
    Time.replace(":", "");
    Time.replace(".", "");
    Time.toCharArray(char_buf, Time.length() + 1);
    static unsigned long timer;
    static bool dots;

    if (AutoDots)
    {
        static unsigned long timer;
        static uint8_t counter;
        if (millis() - timer > 1000)
        {
            timer = millis();
            counter++;
            if (counter == 1)
            {
                dots = true;
            }
            if (counter == 2)
            {
                dots = false;
                counter = 0;
            }
        }
    }
    else
    {
        dots = false;
    }

    if (micros() - timer > Brighness_SK)
    {
        timer = micros();

        for (int i = 0; i < 5; i++)
        {
            if (i == 0)
            {

                if (dots == true)
                {
                    for (int j = 0; j < Brightness; j++)
                    {
                        sr.set(Key_Lamp[i], HIGH);
                    }
                }
                else
                {
                    for (int j = 0; j < Brightness; j++)
                    {
                        sr.set(Key_Lamp[i], LOW);
                    }
                }
            }

            if (i == 1)
            {
                if (String(char_buf[0]) != " ")
                {
                    sr.set(Key_Lamp[i], HIGH);
                    for (int j = 0; j < Brightness; j++)
                    {

                        sr.set(String(char_buf[0]).toInt(), HIGH);
                    }
                }
                else
                {
                    sr.set(Key_Lamp[i], LOW);
                }
            }

            if (i == 2)
            {

                if (String(char_buf[1]) != " ")
                {
                    sr.set(Key_Lamp[i], HIGH);
                    for (int j = 0; j < Brightness; j++)
                    {

                        sr.set(String(char_buf[1]).toInt(), HIGH);
                    }
                }
                else
                {
                    sr.set(Key_Lamp[i], LOW);
                }
            }

            if (i == 3)
            {
                if (String(char_buf[2]) != " ")
                {
                    sr.set(Key_Lamp[i], HIGH);
                    for (int j = 0; j < Brightness; j++)
                    {

                        sr.set(String(char_buf[2]).toInt(), HIGH);
                    }
                }
                else
                {
                    sr.set(Key_Lamp[i], LOW);
                }
            }

            if (i == 4)
            {
                if (String(char_buf[3]) != " ")
                {
                    sr.set(Key_Lamp[i], HIGH);
                    for (int j = 0; j < Brightness; j++)
                    {

                        sr.set(String(char_buf[3]).toInt(), HIGH);
                    }
                }
                else
                {
                    sr.set(Key_Lamp[i], LOW);
                }
            }

            sr.setAllLow();
        }
    }
}

void attenuation_start(String value, int brightnes, bool dots)
{

    if (!dots)
    {
        Dots_Enabled = false;
    }

    if (brightnes != count_attenuation_start)
    {
        count_attenuation_start++;
    }
    else
    {
        flag_attenuation_start = true;
    }

    Nixie_Time(value, count_attenuation_start, Dots_Enabled);
}

void attenuation_end(String value, int brightnes, bool dots)
{

    if (!dots)
    {
        Dots_Enabled = false;
    }

    if (count_animation_end != 0)
    {
        count_animation_end--;
    }
    else
    {
        flag_attenuation_end = true;
    }

    Nixie_Time(value, count_animation_end, Dots_Enabled);
}

void timer_effects()
{
    static unsigned long timer;
    if (millis() - timer > 70)
    {
        timer = millis();
        count_animation_start++;
    }
}

void animation_start(String value, int brightnes, bool dots)
{
    if (Time_str != NULL && flag_animation_start != true)
    {

        if (!dots)
        {
            Dots_Enabled = false;
        }

        char blank = ' ';
        char char_buf[4];
        value.replace(":", "");
        value.replace(".", "");
        value.toCharArray(char_buf, value.length() + 1);

        String str_anim[] =
            {
                String(blank) + String(blank) + String(blank) + String(blank),                   // 1
                String(blank) + String(blank) + String(blank) + String(char_buf[0]),             // 2
                String(blank) + String(blank) + String(char_buf[0]) + String(blank),             // 3
                String(blank) + String(char_buf[0]) + String(blank) + String(blank),             // 4
                String(char_buf[0]) + String(blank) + String(blank) + String(blank),             // 5
                String(char_buf[0]) + String(blank) + String(blank) + String(char_buf[1]),       // 6
                String(char_buf[0]) + String(blank) + String(char_buf[1]) + String(blank),       // 7
                String(char_buf[0]) + String(char_buf[1]) + String(blank) + String(blank),       // 8
                String(char_buf[0]) + String(char_buf[1]) + String(blank) + String(char_buf[2]), // 9
                String(char_buf[0]) + String(char_buf[1]) + String(char_buf[2]) + String(blank)  // 10

            };

        Nixie_Time(str_anim[count_animation_start], Brightness_Lamp, Dots_Enabled);

        if (count_animation_start >= 10)
        {
            flag_animation_start = true;
            Dots_Enabled = true;
        }
    }
}

void animation_end(String value, int brightnes, bool dots)
{
    if (Time_str != NULL && flag_animation_end != true)
    {

        if (!dots)
        {
            Dots_Enabled = false;
        }

        char blank = ' ';
        char char_buf[4];
        value.replace(":", "");
        value.replace(".", "");
        value.toCharArray(char_buf, value.length() + 1);

        String str_anim[] =
            {
                String(char_buf[0]) + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]), // 0
                String(blank) + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]),       // 1
                String(char_buf[1]) + String(blank) + String(char_buf[2]) + String(char_buf[3]),       // 2
                String(blank) + String(blank) + String(char_buf[2]) + String(char_buf[3]),             // 3
                String(blank) + String(char_buf[2]) + String(blank) + String(char_buf[3]),             // 4
                String(char_buf[2]) + String(blank) + String(blank) + String(char_buf[3]),             // 5
                String(blank) + String(blank) + String(blank) + String(char_buf[3]),                   // 6
                String(blank) + String(blank) + String(char_buf[3]) + String(blank),                   // 7
                String(blank) + String(char_buf[3]) + String(blank) + String(blank),                   // 8
                String(char_buf[3]) + String(blank) + String(blank) + String(blank),                   // 9
                String(blank) + String(blank) + String(blank) + String(blank)};                        // 10

        Nixie_Time(str_anim[count_animation_start], Brightness_Lamp, Dots_Enabled);

        if (count_animation_start >= 10)
        {
            flag_animation_end = true;
            flag_animation_start = false;
            flag_time = false;
            count_animation_start = 0;
        }
    }
}

void nixie_write_time()
{

    static unsigned long timer;

    if (millis() - timer > 1000)
    {
        timer = millis();
        Time_str = rtc_get_time();
        Data_str = rtc_get_data();

        Count_Dots++;

        if (Count_Dots == 2)
        {

            Count_Dots = 0;
        }
    }
}

void mode_normal()
{
    nixie_write_time();

    if (Time_str != NULL)
    {
        timer_effects();
    }

    if (mode_clock == 0)
    {
        animation_start(Time_str, Brightness_Lamp, false);
    }
    else if (mode_clock == 1)
    {
        animation_start(Data_str, Brightness_Lamp, false);
    }

    if (flag_animation_start && !flag_time)
    {
        if (mode_clock == 0)
        {
            Nixie_Time(Time_str, Brightness_Lamp, true);
            if (count_animation_start > 200)
            {
                flag_time = true;
                flag_animation_end = false;
                count_animation_start = 0;
                mode_clock = 1;
            }
        }

        if (mode_clock == 1)
        {
            Nixie_Time(Data_str, Brightness_Lamp, false);
            if (count_animation_start > 50)
            {
                flag_time = true;
                flag_animation_end = false;
                count_animation_start = 0;
                mode_clock = 0;
            }
        }
    }

    if (flag_time)
    {
        if (mode_clock == 1)
        {
            animation_end(Time_str, Brightness_Lamp, false);
        }
        if (mode_clock == 0)
        {
            animation_end(Data_str, Brightness_Lamp, false);
        }
    }
}

void mode_count_effect(String mode, String count)
{
    if (mode == "1")
    {
        if (count.length() == 1)
            count = mode + "  " + count;
        else if (count.length() == 2)
            count = mode + " " + count;
        else if (count.length() == 3)
            count = mode + count;
    }

    if (mode == "2")
    {

        // RED, GREEN, BLUE, WHITE, YELLOW, CYAN, MAGENTA, PURPLE, ORANGE, PINK, GRAY
        if (count == String(RED))
        {
            count = "1";
        }
        else if (count == String(GREEN))
        {
            count = "2";
        }
        else if (count == String(BLUE))
        {
            count = "3";
        }
        else if (count == String(WHITE))
        {
            count = "4";
        }
        else if (count == String(YELLOW))
        {
            count = "5";
        }
        else if (count == String(CYAN))
        {
            count = "6";
        }
        else if (count == String(MAGENTA))
        {
            count = "7";
        }

        else if (count == String(ORANGE))
        {
            count = "8";
        }



            if (count.length() == 1)
                count = mode + "  " + count;
            else if (count.length() == 2)
                count = mode + " " + count;
            else if (count.length() == 3)
                count = mode + count;
    }

    if (mode == "3")
    {

        if (count.length() == 1)
            count = mode + "  " + count;
        else if (count.length() == 2)
            count = mode + "  " + count.substring(0);
        else if (count.length() == 3)
            count = mode + " " + count.substring(0) + count.substring(1);
    }

    if (mode == "4")
    {
        if (count.length() == 1)
            count = mode + "  " + count;
        else if (count.length() == 2)
            count = mode + "   " + count.substring(0);
        else if (count.length() == 3)
            count = mode + "  " + count.substring(0) + count.substring(1);
        else if (count.length() == 4)
            count = mode + " " + count.substring(0) + count.substring(1);
    }

    static unsigned long timer;
    static uint8_t cnt;
    if (millis() - timer > 200)
    {
        timer = millis();
        cnt++;
    }

    if (cnt == 1)
    {
        Nixie_Time(count, Brightness_Lamp, false);
    }
    else if (cnt == 2)
    {
        Nixie_Time("    ", Brightness_Lamp, false);
        cnt = 0;
    }
}

void nixie_lamp_task(NIXIE_MODE mode)
{
    switch (mode)
    {
    case NORMAL | 0:
        mode_normal();
        break;

    case CURRENT_EFFECT | 1:

        switch (settings.object.nixie_s.object)
        {
        case EFFECTS | 1:
            mode_count_effect(String(settings.object.nixie_s.object), String(settings.object.ws2812_s.effect_t));
            break;
        case COLOR | 2:
            mode_count_effect(String(settings.object.nixie_s.object), String(settings.object.ws2812_s.color_t));
            break;
        case BRIGHTNESS | 3:
            mode_count_effect(String(settings.object.nixie_s.object), String(settings.object.ws2812_s.brightness_t));
            break;
        case SPEED | 4:
            mode_count_effect(String(settings.object.nixie_s.object), String(settings.object.ws2812_s.speed_t));
            break;

        default:
            break;
        }

        break;

    default:
        break;
    }
}