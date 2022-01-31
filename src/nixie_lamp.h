void Nixie_Time(String Time, int Brightness)
{
    Time.replace(":", "");
    Time.replace(".", "");
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
    Timer_Brightness_Lamp.setInterval(Brighness_SK);
    TimerSecond.setInterval(1000);
    TimerEffects.setInterval(100);
}

void loop_nixie_lamp()
{
    read_effects_load();
    nixie_write_time();
}
