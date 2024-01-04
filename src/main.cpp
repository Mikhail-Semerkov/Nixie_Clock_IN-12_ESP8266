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
  serial_trace("\r\n------------------------------------\r\n");
  serial_trace("Start APP\r\n");

  init_config();
  init_ota();

  serial_trace("TEST EFFECTS = %d\r\n", settings.object.ws2812_s.effect_t);

  init_ws2812();
  init_button();

  print_file();

  tcp_server_init();

  settings.object.ws2812_s.auto_brightness_t = true;
}

void loop()
{
  task_ota();
  nixie_lamp_task((NIXIE_MODE)settings.object.nixie_s.mode);
  task_ws2812();
  udp_synch_time();
  task_button();

  loop_tcp_server();

  TEST_TASK();
}

void TEST_TASK(void)
{
  static unsigned long timer;
  if (millis() - timer > 1000)
  {
    timer = millis();

    //tcp_trace("ADC = %d\r\n", get_adc());
    //serial_trace("ADC = %d\r\n", get_adc());

    // serial_trace("EFFECT = %d\r\n", settings.object.ws2812_s.effect_t);
    // serial_trace("WIFI_MODE = %d\r\n", settings.object.wifi_s.mode_wifi);
    // serial_trace("WS2812_MODE = %d\r\n", settings.object.ws2812_s.mode_ws2812);
    //  settings.config._hostname = "AAAAA WORK!!!!";
    // serial_trace("NIXIE_MODE = %d\r\n", settings.object.nixie_s.mode);

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