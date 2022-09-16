#include "trace.h"

#ifndef __XC32

void __serial_init(int badrate)
{
    Serial.begin(badrate);
}

void __serial_trace(const char *fmt, ...)
{
    char buf[1024] = {};
    va_list li;

    va_start(li, fmt);
    vsprintf(buf, fmt, li);
    va_end(li);
    Serial.write((uint8_t *)buf, strlen(buf));
}
#endif