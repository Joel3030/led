#include <Arduino.h>
#include "../lib/ws2812.h"

#define LED_PIN 2
#define LED_COUNT 80

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void ws2812_setup()
{
	ws2812fx.init();
	ws2812fx.setMode(FX_MODE_STATIC);
	ws2812fx.setColor(0xFF5900);
	ws2812fx.setSpeed(1000);
	ws2812fx.setBrightness(128);
	ws2812fx.start();
}