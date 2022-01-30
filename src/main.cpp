#include <global.h>
#include <wifi_esp.h>
#include <nixie_lamp.h>
#include <server_esp.h>
#include <ws2812.h>

void setup()
{
  setup_wifi_esp();
  //setup_ws2812();
  setup_server();
  setup_nixie_lamp();
}

void loop()
{
  loop_server();
  //loop_ws2812();
  loop_nixie_lamp();
}
