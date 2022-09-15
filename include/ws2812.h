#include <WS2812FX.h>


#define LED_COUNT 16
#define LED_PIN 12

typedef enum
{
    MODE_ERROR = 0,
    MODE_OK,
    MODE_NORMAL,
    MODE_OFF
} mode_ws2812_t;



void select_effects(uint8_t effect, uint32_t color, uint8_t brightness, uint16_t speed);
void set_collor(uint32_t color);

void init_ws2812(void);
void task_ws2812(void);

void mode_ws2812(mode_ws2812_t mode);
