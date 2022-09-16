#include "fotorez.h"
#include "trace.h"

#define GAIN_ADC 2

uint16_t get_adc(void)
{
    uint16_t adc_value;
    adc_value = analogRead(A0);
    adc_value = map(adc_value, 0, 1024, 0, 10);
    return adc_value = adc_value + GAIN_ADC;
}