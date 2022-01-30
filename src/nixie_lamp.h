void Nixie_Time(String Time, int Brightness)
{

    Time.replace(":", "");
    int Count_Lamp_1 = String(Time.substring(0, 1)).toInt();
    int Count_Lamp_2 = String(Time.substring(1, 2)).toInt();
    int Count_Lamp_3 = String(Time.substring(2, 3)).toInt();
    int Count_Lamp_4 = String(Time.substring(3, 4)).toInt();
    int Count_Lamp_5 = String(Time.substring(4, 5)).toInt();
    int Count_Lamp_6 = String(Time.substring(5, 6)).toInt();

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

                sr.set(Key_Lamp[i], HIGH);
                for (int j = 0; j < Brightness; j++)
                {
                    sr.set(Count_Lamp_1, HIGH);
                }
            }

            if (i == 2)
            {
                sr.set(Key_Lamp[i], HIGH);
                for (int j = 0; j < Brightness; j++)
                {
                    sr.set(Count_Lamp_2, HIGH);
                }
            }

            if (i == 3)
            {
                sr.set(Key_Lamp[i], HIGH);
                for (int j = 0; j < Brightness; j++)
                {
                    sr.set(Count_Lamp_3, HIGH);
                }
            }

            if (i == 4)
            {
                sr.set(Key_Lamp[i], HIGH);
                for (int j = 0; j < Brightness; j++)
                {
                    sr.set(Count_Lamp_4, HIGH);
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

    if (Time_str != NULL)
    {
        if (TimerEffects.isReady() && Brightness_Lamp != count_effects)
        {
            count_effects++;
        }

        Nixie_Time(Time_str, count_effects);
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
