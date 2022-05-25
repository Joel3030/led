#include <Arduino.h>
#include "../lib/wifi.h"

#define WIFI_SSID "CLAROH44CP"
#define WIFI_PASSWORD "@Pelon3030"

#define ESP_RESET ESP.reset()

unsigned long WIFI_TIMEOUT = 30000;

void wifi_setup()
{
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(WIFI_SSID);

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	unsigned long connect_start = millis();
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");

		if (millis() - connect_start > WIFI_TIMEOUT)
		{
			Serial.println();
			Serial.print("Tried ");
			Serial.print(WIFI_TIMEOUT);
			Serial.print("ms. Resetting ESP now.");
			ESP_RESET;
		}
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println();
}