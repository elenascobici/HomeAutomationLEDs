#include "FillSolid.h"
#include <Pattern.h>

FillSolid::FillSolid(PatternParams* patternParams): Pattern() {
	brightness = patternParams->brightness;
	delayTime = patternParams->delayTime;
	memcpy(colours, patternParams->colours, sizeof(int)*15);
	ledsCount = patternParams->ledsCount;
	//pin = patternParams->pin;
	leds = patternParams->leds;
}

void FillSolid::Start() {
	FastLED.setBrightness(brightness);
	fill_solid(leds, ledsCount, CRGB(colours[0], colours[1], colours[2]));
	//fill_solid(leds, ledsCount, CRGB(255, 0, 0));
	FastLED.setBrightness(brightness);
	FastLED.show();
}

bool FillSolid::NextStep() {
	// None
	return true;
}