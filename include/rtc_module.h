#include <Arduino.h>
#include "microDS3231.h"
#include "GyverTimer.h"

String rtc_get_time();
String rtc_get_data();

void synch_rtc(DateTime dt);