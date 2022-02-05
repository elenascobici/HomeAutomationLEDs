#include <Arduino.h>
#include <FastLED.h>
#include <ColoursFade.h>
#include <FillSolid.h>

const int pin = 5;
const int ledsCount = 60;
char goodReply[] = "Atmega Ok!";
char badReply[] = "Atmega Error";

CRGB leds[ledsCount];

// Requests are in the form of c1.255.255.0.c2.0.15.6.p31.d10.b50

char oneByte;
String packetString = "";

int patternDelayBrightness [3];

int colours [15];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, pin, GRB>(leds, ledsCount);

  pinMode(13, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {
    oneByte = Serial.read();
    if (oneByte != '<' && packetString == ""){
      Serial.print(badReply);
      continue;
    }
    packetString += oneByte;
    if (oneByte == '>') {
      Serial.print(goodReply);
      packetString = packetString.substring(1, packetString.length() - 1);
      CreateColourList();
      Serial.println(packetString);
      CreateAttributesList();
      Serial.println(packetString);
      packetString = "";
      break;
    }
  }
  UseCorrectLibrary();
}

// Returns the packet string after cutting everything before and including the first period
String CutPeriod(){
  return packetString.substring(packetString.indexOf('.') + 1, packetString.length() - packetString.indexOf('.') + 3);
}

// Creates a list of red, green and blue colour values.
String CreateColourList(){
  int i = 0;
  // While the first character of packetString is c, there are more colours to add
  while (packetString[0] == 'c') {
    for (int j = i; j < i+3; j++) {
      // Cut the period, then read the number until the next period and add it to the list representing the RGB colour
      packetString = CutPeriod();
      colours[j] = (packetString.substring(0, packetString.indexOf('.'))).toInt();
    }
    // Cut the period once more to get rid of the blue number
    packetString = CutPeriod();
    i+=3;
  } 
  return packetString;
}

// Finds the pattern, delay and brightness and uses the appropriate library to create the pattern
void CreateAttributesList(){
  // An array of the pattern, delay and brightness
  for (int i = 0; i < 3; i++){
    // Each numerical value is index 1 (2nd character, 1st is tag name) and has a length of the period index - 1
    patternDelayBrightness[i] = (packetString.substring(1, packetString.indexOf('.')).toInt());
    packetString = CutPeriod();
  }  
}

void UseCorrectLibrary(){
  // Switch statement based on preset that uses appropriate library with appropriate parameters
  switch (patternDelayBrightness[0]){
    case 0:
    {
      FillSolid fillsolid(leds, ledsCount, pin, patternDelayBrightness[2], colours[0], colours[1], colours[2]);
      fillsolid.FillSolidLoop();
      break;
    }
    case 1:
    {
      ColoursFade coloursfade(leds, ledsCount, pin, patternDelayBrightness[2], patternDelayBrightness[1], colours[0], colours[1], colours[2], colours[3], colours[4], colours[5]);
      coloursfade.ColoursFadeLoop();
      break;
    }
    default:
      break;
  }
  
}
