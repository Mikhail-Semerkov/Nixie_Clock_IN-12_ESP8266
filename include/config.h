#include <ArduinoJson.h>
#include <FS.h>


#define FILE_CONFIG "/config.json"

void init_config(void);
void save_config(void);
void print_file(void);
void func_default_settings(void);
