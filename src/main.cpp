#include <global.h>
#include <function.h>
#include <config.h>
#include <wifi_esp.h>
#include <nixie_lamp.h>
#include <effects_load_nixie.h>
#include <server_esp.h>
#include <ws2812.h>

void setup()
{
  Serial.begin(115200);

  loadConfiguration("/config.json", config);
  setup_wifi_esp();
  setup_ws2812();
  setup_server();
  setup_nixie_lamp();

  Serial.println(config._static_ip);
}

void loop()
{

  loop_nixie_lamp();
  loop_server();
  loop_ws2812();
}
