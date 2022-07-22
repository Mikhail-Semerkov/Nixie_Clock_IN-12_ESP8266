#include "main.h"

void setup()
{
  Serial.begin(115200);
  setup_config();
  wifi_connect();
  setup_ws2812();
  setup_server();
}


void loop()
{
  nixie_lamp_task();
  loop_server();
  loop_ws2812();
  udp_synch_time();
}
