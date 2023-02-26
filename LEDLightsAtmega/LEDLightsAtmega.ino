#include <Arduino.h>
#include <FastLED.h>
#include <Pattern.h>
#include <FillSolid.h>
#include <ColoursFade.h>

const int dataPin = 5;
const int commandPin = 2;
const int ledsCount = 495;
char goodReply[] = "Atmega Ok!";
char badReply[] = "Atmega Error";
const bool debugMode = false;

CRGB leds[ledsCount];

// Requests are in the form of [COLOR1][COLOR1 RGB VALUE][COLOR2][COLOR2 RGB VALUE]...[COLORn][COLORn RGB VALUE][PRESET NUMBER][DELAY VALUE][BRIGHTNESS VALUE]
// Notes: RGB value should be in dotted decimal format. Delay value should be specified in milliseconds. Brightness value should be in percentage format (1 ... 100%).
// Example: c1.255.255.0.c2.0.15.6.p31.d10.b50

char oneChar;
String packetString = "";
int patternDelayBrightness [3];
Pattern* currentPattern;
PatternParams* patternParams;

void setup() {
  Serial1.begin(9600);
  FastLED.addLeds<WS2812, dataPin, RGB>(leds, ledsCount);
  pinMode(commandPin, INPUT);
  pinMode(dataPin, OUTPUT);
}

void showMessage(String message){
  if (debugMode)
  {
    Serial1.print(message + "\n\r");
  }
}

void loop() {
  bool fullCommandReceived = false;
  showMessage("I'm in the loop");
  if (Serial1.available() > 0) {
    oneChar = Serial1.read();
    showMessage("I got: " + String(oneChar));
    if (oneChar != '<' && packetString == ""){
      showMessage(badReply);
    }
    else{
      packetString += oneChar;
    }
    if (oneChar == '>') {
      showMessage(String(goodReply) + " packets: " + String(packetString));
      packetString = packetString.substring(1, packetString.length() - 1);
      fullCommandReceived = true;
    }
  }
  showMessage("Command string: " + packetString);
  if (packetString != "" && fullCommandReceived){
    showMessage("Received command string: " + packetString);
    fullCommandReceived = false;
    if (patternParams != NULL) {
      delete patternParams;
    }
    patternParams = SetPatternAttributes(packetString);
    if (currentPattern != NULL) {
      delete currentPattern;
    }
    currentPattern = CreatePattern(patternParams);
    packetString = "";
    if (currentPattern != NULL) {
      currentPattern->Start();
    }
  } else if (currentPattern != NULL && digitalRead(commandPin) != LOW){
    currentPattern->NextStep();
  }
}

// Create and return a new Pattern instance based on the given preset name
Pattern* CreatePattern(PatternParams* patternParams){
  switch (patternParams->patternNum){
    case 0:{
      return new FillSolid(patternParams);   
    }
    case 1:{
      return new ColoursFade(patternParams);
    }
    default:{
      return NULL;
    }
  }
}

// Returns the packet string after cutting everything before and including the first period
String CutPeriod(String command){
  return command.substring(command.indexOf('.') + 1, command.length() - command.indexOf('.') + 3);
}

// Create an instance of the PatternParams structure, set the proper attributes and return it
PatternParams* SetPatternAttributes(String commandString){
  PatternParams* patternParams = new PatternParams();
  int i = 0;
  // While the first character of packetString is c, there are more colours to add
  while (commandString[0] == 'c') {
    for (int j = i; j < i+3; j++) {
      showMessage(commandString);
      // Cut the period, then read the number until the next period and add it to the list representing the RGB colour
      commandString = CutPeriod(commandString);
      patternParams->colours[j] = (commandString.substring(0, commandString.indexOf('.'))).toInt();
    }
    // Cut the period once more to get rid of the blue number
    commandString = CutPeriod(commandString);
    i+=3;
  }
  patternParams->patternNum = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);
  patternParams->delayTime = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);
  patternParams->brightness = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);
  patternParams->ledsCount = ledsCount;
  patternParams->leds = leds;

  return patternParams;
}
