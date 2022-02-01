void setup_ws2812()
{
    ws2812fx.init();
    ws2812fx.setBrightness(0);
    ws2812fx.start();
    Timer_Load_Sost_wifi.setInterval(1000);
}

void select_effects(uint8_t mode, uint32_t color, uint8_t brightness, uint16_t speed)
{
    while (ws2812fx.getMode() != mode || ws2812fx.getColor() != color || ws2812fx.getBrightness() != brightness || ws2812fx.getSpeed() != speed)
    {

        ws2812fx.setMode(mode);
        ws2812fx.setColor(color);
        ws2812fx.setBrightness(brightness);
        ws2812fx.setSpeed(speed);

        // Serial.println(String(ws2812fx.getMode()));
        // Serial.println(String(ws2812fx.getColor()));
        // Serial.println(String(ws2812fx.getBrightness()));
        // Serial.println(String(ws2812fx.getSpeed()));

        break;
    }
}

// RED 0xFF0000
// GREEN 0x00FF00
// BLUE 0x0000FF
// 0xFFFFFF, 0xFFFF00, 0x00FFFF, 0xFF00FF};
// WL_NO_SHIELD = 255,
// WL_IDLE_STATUS = 0,
// WL_NO_SSID_AVAIL = 1,
// WL_SCAN_COMPLETED = 2,
// WL_CONNECTED = 3,
// WL_CONNECT_FAILED = 4,
// WL_CONNECTION_LOST = 5,
// WL_WRONG_PASSWORD = 6,
// WL_DISCONNECTED = 7

void ws2812_effects_sost_wifi(wl_status_t event)
{

    switch (event)
    {
    case WL_CONNECTED:
        if (Seconds_Start_MK <= 10)
        {
            select_effects(15, 0xFF0000, 20, 1000);
        }
        else
        {
            select_effects(15, 0x00FFFF, 20, 5000);
        }

        break;
    case WL_DISCONNECTED:

        if (Seconds_Start_MK <= 10)
        {
            select_effects(15, 0x00FF00, 20, 1000);
        }
        else
        {
            select_effects(15, 0x00FFFF, 20, 5000);
        }
        break;
    case WL_NO_SSID_AVAIL:
        select_effects(1, 0x00FF00, 20, 300);
        break;
    case WL_WRONG_PASSWORD:
        select_effects(1, 0x00FF00, 20, 300);
        break;

    default:
        break;
    }
}

void loop_ws2812()
{
    if (Timer_Load_Sost_wifi.isReady())
    {
        ws2812_effects_sost_wifi(WiFi.status());
    }

    ws2812fx.service();
}
