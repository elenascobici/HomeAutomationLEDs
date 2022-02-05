#include "Arduino.h"
#include "FastLED.h"
#include "ColoursFade.h"

ColoursFade::ColoursFade(CRGB* _leds, int numleds, int pin, int brightness, int delayTime, float r1, float g1, float b1, float r2, float g2, float b2)
{
  leds = _leds;
  NUM_LEDS = numleds;
  FastLED.setBrightness(brightness);
  _delay = delayTime;
  red_1 = r1;
  green_1 = g1;
  blue_1 = b1;
  red_2 = r2;
  green_2 = g2;
  blue_2 = b2;
}

void ColoursFade::ColoursFadeLoop()
{
  float red_scale = (red_1 - red_2)/255.0;
  float green_scale = (green_1 - green_2)/255.0;
  float blue_scale = (blue_1 - blue_2)/255.0;
  float r = red_1;
  float g = green_1;
  float b = blue_1;

  for (int j = 0; j < 2; j++){
    for (int i = 0; i < 255; i++){
      fill_solid(leds, NUM_LEDS, CRGB(round(r), round(g), round(b)));
      FastLED.show();
      r = r - red_scale;
      g = g - green_scale;
      b = b - blue_scale;    
      delay(_delay);
   } 
  red_scale *= -1;
  green_scale *= -1;
  blue_scale *= -1;
  } 
}
