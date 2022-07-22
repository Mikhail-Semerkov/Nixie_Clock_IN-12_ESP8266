#include <WS2812FX.h>

#define LED_COUNT 16
#define LED_PIN 12

void select_effects(uint8_t mode, uint32_t color, uint8_t brightness, uint16_t speed);
void set_collor(uint32_t color);

void setup_ws2812();
void loop_ws2812();
