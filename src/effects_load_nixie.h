void effects_load_1()
{

    if (effects_load == 1 && Time_str != NULL)
    {
        if (TimerEffects.isReady() && Brightness_Lamp != count_effects)
        {
            count_effects++;
        }

        Nixie_Time(Time_str, count_effects);
    }
}


void animation_start()
{


}

void effects_load_2()
{

    if (effects_load == 2 && Time_str != NULL)
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

        if (count_effects >= 10 && count_effects <= 140)
        {

            Nixie_Time(Time_str, Brightness_Lamp);
        }

        if (count_effects == 141)
        {
            String i = " " + String(char_buf[1]) + String(char_buf[2]) + String(char_buf[3]);
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 142)
        {
            String i = String(char_buf[1]) + " " + String(char_buf[2]) + String(char_buf[3]);
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 143)
        {
            String i = " " + String(char_buf[2]) + " " + String(char_buf[3]);
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 144)
        {
            String i = String(char_buf[2]) + " " + " " + String(char_buf[3]);
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 145)
        {
            String i = "   " + String(char_buf[3]);
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 146)
        {
            String i = "  " + String(char_buf[3]) + " ";
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 147)
        {
            String i = " " + String(char_buf[3]) + "  ";
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 148)
        {
            String i = String(char_buf[3]) + "   ";
            Nixie_Time(i, Brightness_Lamp);
        }

        if (count_effects == 149)
        {
            String i = "    ";
            Nixie_Time(i, Brightness_Lamp);
        }

        else if (count_effects >= 150 && count_effects <= 200)
        {
            Count_Dots = 1;
            Nixie_Time(Data_str, Brightness_Lamp);
        }
        else if (count_effects > 200)
        {
            // MODE_NIXIE == 10;
            count_effects = 0;
        }
    }
}

void read_effects_load()
{

    switch (effects_load)
    {
    case 1:
        effects_load_1();
        break;
    case 2:
        effects_load_2();
        break;

    default:
        break;
    }
}