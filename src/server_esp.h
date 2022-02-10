void udp_synch()
{
  if (WiFi.status() == WL_CONNECTED && Synch_UDP == false)
  {
    Serial.println("WiFi Connect!");
    timeClient.begin();
    timeClient.setTimeOffset(3600 * timeZone);

    if (!timeClient.update())
    {
      Serial.println("UDP Error!");
      timeClient.forceUpdate();
      UDP_Error = true;
    }
    else
    {
      UDP_Error = false;
    }

    if (UDP_Error == false && UDP_Error == false)
    {

      formattedDate = timeClient.getFormattedDate();
      int splitT = formattedDate.indexOf("T");
      dayStamp = formattedDate.substring(0, splitT);
      Serial.print("UDP DATE: ");
      Serial.println(dayStamp);

      timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
      Serial.print("UDP TIME: ");
      Serial.println(timeStamp);

      RTC_Clock.setHMSDMY(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(), dayStamp.substring(8, 10).toInt(), dayStamp.substring(5, 7).toInt(), dayStamp.substring(0, 4).toInt());

      if (UDP_Error == false)
      {
        Synch_UDP = true;
      }
    }
  }
}

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
    ws2812fx.setColor(RED);
  }
  if (Buffer == "GREEN")
  {
    ws2812fx.setColor(GREEN);
  }
  if (Buffer == "BLUE")
  {
    ws2812fx.setColor(BLUE);
  }
  if (Buffer == "WHITE")
  {
    ws2812fx.setColor(WHITE);
  }
  if (Buffer == "BLACK")
  {
    ws2812fx.setColor(BLACK);
  }
  if (Buffer == "YELLOW")
  {
    ws2812fx.setColor(YELLOW);
  }
  if (Buffer == "CYAN")
  {
    ws2812fx.setColor(CYAN);
  }
  if (Buffer == "MAGENTA")
  {
    ws2812fx.setColor(MAGENTA);
  }
  if (Buffer == "PURPLE")
  {
    ws2812fx.setColor(PURPLE);
  }
  if (Buffer == "ORANGE")
  {
    ws2812fx.setColor(ORANGE);
  }
  if (Buffer == "PINK")
  {
    ws2812fx.setColor(PINK);
  }
  if (Buffer == "GRAY")
  {
    ws2812fx.setColor(GRAY);
  }
  if (Buffer == "ULTRAWHITE")
  {
    ws2812fx.setColor(ULTRAWHITE);
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
                  json += "\"nixie_time\":" + String("\"") + Time_str + String("\", \n");
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
  //udp_synch();
  server.handleClient();
}