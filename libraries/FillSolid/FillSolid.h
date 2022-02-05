#ifndef FillSolid_h
#define FillSolid_h

#include "Arduino.h"
#include "FastLED.h"

class FillSolid
{
public:
    FillSolid(CRGB* _leds, int numleds, int pin, int brightness, int red, int green, int blue);
    void FillSolidLoop();
private:
    float _red;
    float _green;
    float _blue;
    int ledsCount;
    CRGB* leds;
};

#endif
