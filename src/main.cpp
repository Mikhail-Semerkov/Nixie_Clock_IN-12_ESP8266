#include <Arduino.h>
#include "config.h"
#include "ota_wifi.h"
#include "nixie_lamp.h"
#include "rtc_module.h"
#include "ws2812.h"
#include "udp_synch.h"
#include "button_control.h"

void setup()
{
  init_config();
  init_ota();
  init_ws2812();
  init_button();
}


void loop()
{
  task_ota();
  
  nixie_lamp_task();
  task_ws2812();
  udp_synch_time();
  task_button();
}
