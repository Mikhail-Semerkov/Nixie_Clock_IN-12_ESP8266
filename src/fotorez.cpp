#include "fotorez.h"

uint16_t adc_value;

void task_adc(void)
{
    static unsigned long timer;
    if(millis() - timer > 1000)
    {
        timer = millis();
        adc_value = analogRead(A0);
        adc_value = map(adc_value, 200, 1024, 0, 10);
        // long map(long x, long in_min, long in_max, long out_min, long out_max)

        Serial.printf("ADC VALUE = %d\r\n", adc_value);
    }
    
}