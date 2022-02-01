void Nixie_Time(String Time, int Brightness, bool Dots)
{
    Dots_Enabled = Dots;
    char char_buf[] = {};
    Time.replace(":", "");
    Time.replace(".", "");
    Time.toCharArray(char_buf, Time.length() + 1);
    String Full = String(char_buf[0]) + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]);

    if (Timer_Brightness_Lamp.isReady())
    {

        for (int i = 0; i < 5; i++)
        {

            if (i == 0)
            {
                if (Count_Dots == 0)
                {
                    for (int j = 0; j < Brightness; j++)
                    {
                        sr.set(Key_Lamp[i], LOW);
                    }
                }

                else
                {
                    if (Dots_Enabled == true)
                    {
                        for (int j = 0; j < Brightness; j++)
                        {
                            sr.set(Key_Lamp[i], HIGH);
                        }
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

            Time = "";
            sr.setAllLow();
        }
    }
}

void nixie_write_time()
{

    if (TimerSecond.isReady())
    {
        Time_str = RTC_Clock.getTimeString();
        Data_str = RTC_Clock.getDateString();

        Count_Dots++;
        Seconds_Start_MK++;

        if (Count_Dots == 2)
        {

            Count_Dots = 0;
        }
    }
}

void setup_nixie_lamp()
{
    mode_clock = 0;
    Timer_Brightness_Lamp.setInterval(Brighness_SK);
    TimerSecond.setInterval(1000);
    TimerEffects.setInterval(100);
}

void loop_nixie_lamp()
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
