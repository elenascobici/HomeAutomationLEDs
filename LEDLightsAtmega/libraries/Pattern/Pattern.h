#ifndef Pattern_h
#define Pattern_h

#include <Arduino.h>
#include <FastLED.h>

struct PatternParams {
public:
    int patternNum;
    int brightness;
    int delayTime;
    int colours[15];
    int ledsCount;
    int pin;
    CRGB* leds;
};

class Pattern {
public:
    virtual void Start(void) = 0;
    virtual bool NextStep(void) = 0;
    PatternParams patternParams;
};

#endif