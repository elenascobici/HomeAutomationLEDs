#ifndef ColoursFade_h
#define ColoursFade_h

#include <Arduino.h>
#include <FastLED.h>
#include <Pattern.h>

class ColoursFade : public Pattern
{
public:
    ColoursFade(PatternParams* patternParams);
    void Start();
    bool NextStep();
    int colours[15];
    int brightness;
    int delayTime;
    int ledsCount;
    CRGB* leds;
private:
    int currentStep;
    float red_scale;
    float green_scale;
    float blue_scale;
    unsigned long timePassed;
    float r;
    float g;
    float b;
};

#endif