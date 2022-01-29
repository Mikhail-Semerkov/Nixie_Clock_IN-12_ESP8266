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

int Brightness_Lamp = 30;
int Count_Dots;

int Perebor;

bool Antiotravlenie_Lamp;
unsigned long Time_Anti_Otravlenie;
unsigned long Count_Time_Anti_Otravlenie;

void Nixie_Time(String Time, int Brightness);

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////       SERVER ESP                ////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////



ESP8266WebServer server(80);

ESP8266HTTPUpdateServer httpUpdater;
///////////////////////////////////////

int count_effects;

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

String Time_str;

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////          WS2812                 ////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

#include <WS2812FX.h>
int Seconds_Start_MK;

#define LED_COUNT 3
#define LED_PIN 12

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

