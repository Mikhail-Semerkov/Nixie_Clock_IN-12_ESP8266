

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
    if (TimerEffects.isReady())
    {

        count_animation_start++;

        Serial.println(count_animation_start);
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

        char char_buf[] = {};
        char blank = ' ';
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

        char char_buf[] = {};
        char blank = ' ';
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
