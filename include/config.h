#include <ArduinoJson.h>
#include <FS.h>

struct Config
{
    String _mode_wifi, _ip_addr, _mask_addr, _gataway_addr, _wifi_ssid, _wifi_pass, _wifi_ssid_ap, _wifi_pass_ap, _dhcp, _static_ip, _static_mask, _static_gataway, _hostname;
};
extern Config config;

void setup_config();
