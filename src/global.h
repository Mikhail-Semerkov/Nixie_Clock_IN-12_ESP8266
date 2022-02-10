#include <Arduino.h>
#include <GyverTimer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <microDS3231.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ShiftRegister74HC595.h>
#include <WS2812FX.h>
#include <ArduinoJson.h>
#include <FS.h>

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////       NIXIE LAMP                ////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

// NIXIE TUBE LAMP
#define Nixie_Dots 10
#define Nixie_Lamp_1 11
#define Nixie_Lamp_2 12
#define Nixie_Lamp_3 13
#define Nixie_Lamp_4 14
// 74HC595 PIN
#define Data_Pin 13
#define Clock_Pin 14
#define Latch_Pin 15

uint8 Key_Lamp[5] = {Nixie_Dots, Nixie_Lamp_1, Nixie_Lamp_2, Nixie_Lamp_3, Nixie_Lamp_4};
ShiftRegister74HC595<2> sr(Data_Pin, Clock_Pin, Latch_Pin);

GTimer Timer_Brightness_Lamp(US);
GTimer TimerSecond(MS);
GTimer TimerEffects(MS);

int Brightness_Lamp = 20;
int Brighness_SK = 7000;
int Count_Dots;
bool Dots_Enabled = true;
int effects_load = 2;

int Perebor;

bool Antiotravlenie_Lamp;
unsigned long Time_Anti_Otravlenie;
unsigned long Count_Time_Anti_Otravlenie;

int count_animation_start, count_animation_end, count_attenuation_start, count_attenuation_end;
bool flag_animation_start, flag_animation_end, flag_attenuation_start, flag_attenuation_end, flag_time, flag_date;

void animation_start(String value, int brightnes, bool dots);
void animation_end(String value, int brightnes, bool dots);
void timer_effects();

int count_effects;
int mode_clock;

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////       SERVER ESP                ////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

String SSID = "indconf2002";
String PASS = "07031968200703196820123456";
// String SSID = "IT BRN 2g";
// String PASS = "123456780";
String HostName = "Clock_IN_12";

ESP8266WebServer server(80);

ESP8266HTTPUpdateServer httpUpdater;
///////////////////////////////////////

// Time UDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;
int timeZone = 3;
bool Synch_UDP;
bool UDP_Error;

// RTC Time
MicroDS3231 RTC_Clock;

String Lamp_Time_Current;

String Time_str, Data_str;

GTimer Timer_Load_Sost_wifi(MS);

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////          WS2812                 ////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

void select_effects(uint8_t mode, uint32_t color, uint8_t brightness, uint16_t speed);
#include <WS2812FX.h>
int Seconds_Start_MK;

#define LED_COUNT 16
#define LED_PIN 12

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);

struct Config
{
    String _mode_wifi, _ip_addr, _mask_addr, _gataway_addr, _wifi_ssid, _wifi_pass, _wifi_ssid_ap, _wifi_pass_ap, _port_tcp, _dhcp, _static_ip, _static_mask, _static_gataway;
};

Config config;
