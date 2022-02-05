#ifndef ColoursFade_h
#define ColoursFade_h

#include "Arduino.h"
#include "FastLED.h"

class ColoursFade
{
public:
    ColoursFade(CRGB* _leds, int numleds, int pin, int brightness, int delayTime, float r1, float g1, float b1, float r2, float g2, float b2);
    void ColoursFadeLoop();
private:
    int _delay;
    float red_1;
    float green_1;
    float blue_1;
    float red_2;
    float green_2;
    float blue_2;
    int NUM_LEDS;
    CRGB* leds;
};

#endif