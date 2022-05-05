#ifndef FillSolid_h
#define FillSolid_h

#include <Arduino.h>
#include <FastLED.h>
#include <Pattern.h>

class FillSolid: public Pattern
{
    public:
        FillSolid(PatternParams* patternParams);
        void Start();
        bool NextStep();
        int colours[15];
        int brightness;
        int delayTime;
        int ledsCount;
        CRGB* leds;
};

#endif
