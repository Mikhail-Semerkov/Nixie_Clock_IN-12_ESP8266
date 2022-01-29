#include <Arduino.h>
#include <Global.h>
#include <in_12_lamp.h>
#include <synch_clock_udp.h>

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Padavan 2.4", "46684668");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  setup_synch_clock_udp();
  setup_in_12_lamp();
}

void loop()
{

  UDP_SYNCH();
  SYNCH_CLOCK();
}
