#include <Arduino.h>
#include <ArduinoOTA.h>

#include "../lib/ws2812.h"
#include "../lib/wifi.h"
#include "../lib/socketIO.h"

#include <Hash.h>

unsigned long last_wifi_check_time = 0;

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("\n\nStarting...");

  ArduinoOTA.onStart([]()
                     { Serial.println("OTA start"); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nOTA end"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
  ArduinoOTA.begin();

  ws2812_setup();
  wifi_setup();
  socketIO_setup();

  Serial.println("ready!");
}

void loop()
{
  unsigned long now = millis();

  ArduinoOTA.handle();
  ws2812fx.service();
  socketIO.loop();

  if (now - last_wifi_check_time > WIFI_TIMEOUT)
  {
    Serial.print("Checking WiFi... ");
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFi connection lost. Reconnecting...");
      wifi_setup();
    }
    else
    {
      Serial.println("OK");
    }
    last_wifi_check_time = now;
  }
}
