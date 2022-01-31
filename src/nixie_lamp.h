void Nixie_Time(String Time, int Brightness)
{
    Time.replace(":", "");
    char char_buf[] = {};
    Time.toCharArray(char_buf, Time.length() + 1);
    Serial.println(String(char_buf[0]) + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]));

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

            Time = "";
            sr.setAllLow();
        }
    }
}

void nixie_write()
{

    if (TimerSecond.isReady())
    {
        Time_str = RTC_Clock.getTimeString();

        Count_Dots++;
        Seconds_Start_MK++;
        Read_Sost = true;

        if (Count_Dots == 2)
        {
            Read_Sost = false;
            Count_Dots = 0;
        }
    }

    int effects_load = 2;

    if (Time_str != NULL && Time_str != "00:00:00")
    {
        if (effects_load == 1)
        {
            if (TimerEffects.isReady() && Brightness_Lamp != count_effects)
            {
                count_effects++;
            }

            Nixie_Time(Time_str, count_effects);
        }

        if (effects_load == 2)
        {

            Time_str.replace(":", "");
            char char_buf[] = {};
            Time_str.toCharArray(char_buf, Time_str.length() + 1);
            String Time_effects;

            if (TimerEffects.isReady())
            {
                count_effects++;
            }

            if (count_effects == 1)
            {
                String i = "   " + String(char_buf[0]);
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 2)
            {
                String i = "  " + String(char_buf[0]) + " ";
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 3)
            {
                String i = " " + String(char_buf[0]) + "  ";
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 4)
            {
                String i = String(char_buf[0]) + "   ";
                Nixie_Time(i, Brightness_Lamp);
            }

            //////////////////////////////////////////////////////////////////////////

            if (count_effects == 5)
            {
                String i = String(char_buf[0]) + "  " + String(char_buf[1]);
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 6)
            {
                String i = String(char_buf[0]) + " " + String(char_buf[1]) + " ";
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 7)
            {
                String i = String(char_buf[0]) + String(char_buf[1]) + "  ";
                Nixie_Time(i, Brightness_Lamp);
            }

            ///////////////////////////////////////////////////////////////////

            if (count_effects == 8)
            {
                String i = String(char_buf[0]) + String(char_buf[1]) + " " + String(char_buf[2]);
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 9)
            {
                String i = String(char_buf[0]) + String(char_buf[1]) + String(char_buf[2]) + " ";
                Nixie_Time(i, Brightness_Lamp);
            }

            ///////////////////////////////////////////////////////////////////

            if (count_effects >= 10)
            {
                Nixie_Time(Time_str, Brightness_Lamp);
            }
        }

        if (effects_load == 3)
        {

            Time_str.replace(":", "");
            char char_buf[] = {};
            Time_str.toCharArray(char_buf, Time_str.length() + 1);
            String Time_effects;

            if (TimerEffects.isReady())
            {
                count_effects++;
            }

            if (count_effects == 1)
            {
                String i = String(char_buf[3] + "   ");
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 2)
            {
                String i = " " + String(char_buf[3]) + "  ";
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 3)
            {
                String i = "  " + String(char_buf[3]) + " ";
                Nixie_Time(i, Brightness_Lamp);
            }

            else if (count_effects == 4)
            {
                String i = "   " + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            //////////////////////////////////////////////////////////////////////////

            if (count_effects == 5)
            {
                String i = String(char_buf[2]) + "  " + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 6)
            {
                String i = " " + String(char_buf[2]) + " " + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 7)
            {
                String i = "  " + String(char_buf[2]) + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            ///////////////////////////////////////////////////////////////////

            if (count_effects == 8)
            {
                String i = String(char_buf[1]) + " " + String(char_buf[2]) + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            if (count_effects == 9)
            {
                String i = " " + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]);
                Nixie_Time(i, Brightness_Lamp);
            }

            ///////////////////////////////////////////////////////////////////

            if (count_effects >= 10)
            {
                Nixie_Time(Time_str, Brightness_Lamp);
            }
        }
    }
}

void setup_nixie_lamp()
{
    Timer_Brightness_Lamp.setInterval(Brighness_SK);
    TimerSecond.setInterval(1000);
    TimerEffects.setInterval(100);
}

void loop_nixie_lamp()
{
    nixie_write();
}
