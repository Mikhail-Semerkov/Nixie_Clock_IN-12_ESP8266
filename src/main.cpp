#include <global.h>
#include <wifi_esp.h>
#include <nixie_lamp.h>
#include <server_esp.h>
#include <ws2812.h>

void setup()
{
  setup_ws2812();
  wifi_connect();
  setup_server();
  setup_in_12_lamp();
}

void loop()
{
  ws2812_effects_sost_wifi(WiFi.status());
  loop_ws2812();
  udp_synch();
  loop_server();
  loop_nixie_lamp();
  
}
