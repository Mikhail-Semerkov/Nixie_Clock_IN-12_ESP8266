#include "server_esp.h"
#include "ws2812.h"
#include "function.h"
#include "nixie_lamp.h"
#include "config.h"

ESP8266WebServer server(80);

ESP8266HTTPUpdateServer httpUpdater;

const char *htmlfile = "/index.htm";

bool loadFromSpiffs(String path)
{
  String dataType = "text/plain";
  if (path.endsWith("/"))
    path += "index.htm";
  if (path.endsWith(".src"))
    path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html"))
    dataType = "text/html";
  else if (path.endsWith(".htm"))
    dataType = "text/html";
  else if (path.endsWith(".css"))
    dataType = "text/css";
  else if (path.endsWith(".js"))
    dataType = "application/javascript";
  else if (path.endsWith(".png"))
    dataType = "image/png";
  else if (path.endsWith(".gif"))
    dataType = "image/gif";
  else if (path.endsWith(".jpg"))
    dataType = "image/jpeg";
  else if (path.endsWith(".ico"))
    dataType = "image/x-icon";
  else if (path.endsWith(".xml"))
    dataType = "text/xml";
  else if (path.endsWith(".pdf"))
    dataType = "application/pdf";
  else if (path.endsWith(".zip"))
    dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download"))
    dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size())
  {
  }
  dataFile.close();
  return true;
}

void handleWebRequests()
{
  if (loadFromSpiffs(server.uri()))
    return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

void handleRoot()
{
  server.sendHeader("Location", "/index.htm", true);
  server.send(302, "text/plane", "");
}

void set_color_ws2812()
{
  String Buffer = server.arg("color_ws2812");
  server.send(200, "text/plane", "OK");

  if (Buffer == "RED")
  {
    set_collor(RED);
  }
  if (Buffer == "GREEN")
  {
    set_collor(GREEN);
  }
  if (Buffer == "BLUE")
  {
    set_collor(BLUE);
  }
  if (Buffer == "WHITE")
  {
    set_collor(WHITE);
  }
  if (Buffer == "BLACK")
  {
    set_collor(BLACK);
  }
  if (Buffer == "YELLOW")
  {
    set_collor(YELLOW);
  }
  if (Buffer == "CYAN")
  {
    set_collor(CYAN);
  }
  if (Buffer == "MAGENTA")
  {
    set_collor(MAGENTA);
  }
  if (Buffer == "PURPLE")
  {
    set_collor(PURPLE);
  }
  if (Buffer == "ORANGE")
  {
    set_collor(ORANGE);
  }
  if (Buffer == "PINK")
  {
    set_collor(PINK);
  }
  if (Buffer == "GRAY")
  {
    set_collor(GRAY);
  }
  if (Buffer == "ULTRAWHITE")
  {
    set_collor(ULTRAWHITE);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void setup_server()
{

  server.on("/", handleRoot);
  server.onNotFound(handleWebRequests);

  httpUpdater.setup(&server, "/update");

  server.on("/json", HTTP_GET, []()
            {
                  String
                  json = "{\n";
                  json += "\"nixie_time\":" + String("\"") + return_time() + String("\", \n");
                  json += "\"mode_wifi\":" + String("\"") + config._mode_wifi + String("\", \n");
                  json += "\"free_heap\":" + String("\"") + formatBytes(ESP.getFreeHeap()) + String("\"");
                  json += "\n}";

                  server.send(200, "text/json", json);
                  json = String(); });

  server.on("/select_color_ws2812", set_color_ws2812);

  server.begin();
}

void loop_server()
{
  server.handleClient();
}