#include <ShiftRegister74HC595.h>
#include <GyverTimer.h>



uint8 Key_Lamp[5] = {Nixie_Dots, Nixie_Lamp_1, Nixie_Lamp_2, Nixie_Lamp_3, Nixie_Lamp_4};
ShiftRegister74HC595<2> sr(Data_Pin, Clock_Pin, Latch_Pin);

GTimer Timer_Brightness_Lamp(US);

int Brightness_Lamp = 3;
int Count_Dots;

int Perebor;

bool Antiotravlenie_Lamp;
unsigned long Time_Anti_Otravlenie;
unsigned long Count_Time_Anti_Otravlenie;

void setup_in_12_lamp()
{
    Timer_Brightness_Lamp.setInterval(3300);
    Time_Anti_Otravlenie = 60;
}

void Nixie_Time(String Time, int Brightness) // int Count_Lamp_1, int Count_Lamp_2, int Count_Lamp_3, int Count_Lamp_4
{
    Time.replace(":", "");
    int Count_Lamp_1 = String(Time.substring(0, 1)).toInt();
    int Count_Lamp_2 = String(Time.substring(1, 2)).toInt();
    int Count_Lamp_3 = String(Time.substring(2, 3)).toInt();
    int Count_Lamp_4 = String(Time.substring(3, 4)).toInt();

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
                    for (int j = 0; j < Brightness; j++)
                    {
                        sr.set(Key_Lamp[i], HIGH);
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

            sr.setAllLow();
        }
    }
}
