#include <ShiftRegister74HC595.h>


typedef enum
{
    NORMAL = 0,
    CURRENT_EFFECT,
    CURRENT_TIME,
    CURRENT_DATA,
} NIXIE_MODE;

typedef enum
{
    EFFECTS = 1,
    COLOR,
    SPEED
} NIXIE_MODE_WS2812;

typedef enum
{
    TIME = 1,
    SECOND,
} NIXIE_MODE_CURRENT_TIME;

// struct nixie_lamp
// {
//     NIXIE_MODE_WS2812 mode;
// };

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

void nixie_lamp_task(NIXIE_MODE mode);

String return_time();
String return_data();
