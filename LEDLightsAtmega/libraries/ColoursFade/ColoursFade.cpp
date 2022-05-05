#include "ColoursFade.h"
#include <Pattern.h>

ColoursFade::ColoursFade(PatternParams* patternParams): Pattern(){
    brightness = patternParams->brightness;
    delayTime = patternParams->delayTime;
    memcpy(colours, patternParams->colours, sizeof(int)*15);
    ledsCount = patternParams->ledsCount;
    //pin = patternParams->pin;
    leds = patternParams->leds;
    
    currentStep = 0;
    red_scale = (colours[0] - colours[3]) / 255.0;
    green_scale = (colours[1] - colours[4]) / 255.0;
    blue_scale = (colours[2] - colours[5]) / 255.0;
    timePassed = 0;
    r = colours[0] * 1.0;
    g = colours[1] * 1.0;
    b = colours[2] * 1.0;
}

void ColoursFade::Start()
{    
    fill_solid(leds, ledsCount, CRGB(round(r), round(g), round(b)));
    FastLED.show();
    timePassed = millis();
    FastLED.setBrightness(brightness);
}

bool ColoursFade::NextStep() {
    unsigned long newTimePassed = millis();
    if (newTimePassed >= timePassed + delayTime){
        r = r - red_scale;
        g = g - green_scale;
        b = b - blue_scale;

        fill_solid(leds, ledsCount, CRGB(round(r), round(g), round(b)));
        FastLED.show();

        if (++currentStep == 254) {
            currentStep = 0;
            red_scale *= -1;
            green_scale *= -1;
            blue_scale *= -1;
        }
        timePassed = newTimePassed;
        return true;
    }    
    return false;
}
