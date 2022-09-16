#include <Arduino.h>
#include "settings.h"
#include "config.h"
#include "ota_wifi.h"
#include "nixie_lamp.h"
#include "rtc_module.h"
#include "ws2812.h"
#include "udp_synch.h"
#include "button_control.h"
#include "fotorez.h"
#include "tcp_server.h"
#include "trace.h"



/////TEST_TASK////////
void TEST_TASK(void);
///////////////////////

void setup()
{
  serial_init(115200);
  serial_trace("\r\n");
  serial_trace("Start APP\r\n");

  init_config();
  init_ota();
  Serial.printf("TEST EFFECTS = %d\r\n", settings.object.ws2812_s.effect_t);
  init_ws2812();
  init_button();

  print_file();

  tcp_server_init();
}



void loop()
{
  task_ota();
  nixie_lamp_task((NIXIE_MODE)settings.object.nixie_s.mode);
  task_ws2812();
  udp_synch_time();
  task_button();

  task_adc();

  loop_tcp_server();

  TEST_TASK();
}



void TEST_TASK(void)
{
  static unsigned long timer;
  if (millis() - timer > 1000)
  {
    timer = millis();

    tcp_trace("DATA = %d\r\n", timer);

    //Serial.printf("EFFECT = %d\r\n", settings.object.ws2812_s.effect_t);
    //Serial.printf("WIFI_MODE = %d\r\n", settings.object.wifi_s.mode_wifi);
    //Serial.printf("WS2812_MODE = %d\r\n", settings.object.ws2812_s.mode_ws2812);
    // settings.config._hostname = "AAAAA WORK!!!!";
    //Serial.printf("NIXIE_MODE = %d\r\n", settings.object.nixie_s.mode);

    // if (settings.object.ws2812_s.effect_t == 15)
    // {
    //   settings.object.ws2812_s.brightness_t = 20;
    //   settings.object.ws2812_s.speed_t = 3000;
    //   settings.object.ws2812_s.color_t = RED;

    //   //func_default_settings();
    //   save_config();
    // }
  }
}