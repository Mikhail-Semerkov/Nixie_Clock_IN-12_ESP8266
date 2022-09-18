#include "fotorez.h"
#include "trace.h"

#define GAIN_ADC 2

uint16_t get_adc(void)
{
    static uint16_t timer_value = 1;
    static unsigned long timer;
    uint16_t adc_value;
    adc_value = analogRead(A0);
    adc_value = map(adc_value, 0, 1024, 1, 10);

    if (timer_value != adc_value)
    {
        if (millis() - timer > 3000)
        {
            timer = millis();
            timer_value = adc_value;
        }
    }
    else
    {
        timer = millis();
    }

    return timer_value;
}