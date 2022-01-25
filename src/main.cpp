#include <Arduino.h>
#include <Global.h>
#include <in_12_lamp.h>
#include <synch_clock_udp.h>

void setup()
{
  Serial.begin(115200);
  setup_synch_clock_udp();
  setup_in_12_lamp();
}

void loop()
{
  SYNCH_CLOCK();
}
