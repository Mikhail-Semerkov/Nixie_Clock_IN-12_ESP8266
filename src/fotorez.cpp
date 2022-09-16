#include "fotorez.h"
#include "trace.h"

uint16_t get_adc(void)
{
    uint16_t adc_value;
    adc_value = analogRead(A0);
    adc_value = map(adc_value, 0, 1024, 0, 10);
    return adc_value;
}