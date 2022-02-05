#include "Arduino.h"
#include "FastLED.h"
#include "FillSolid.h"

FillSolid::FillSolid(CRGB* _leds, int numleds, int pin, int brightness, int red, int green, int blue) {
	leds = _leds;
	ledsCount = numleds;
	FastLED.setBrightness(brightness);
	_red = red;
	_green = green;
	_blue = blue;
}

void FillSolid::FillSolidLoop() {
	fill_solid(leds, ledsCount, CRGB(_red, _green, _blue));
	FastLED.show();
}