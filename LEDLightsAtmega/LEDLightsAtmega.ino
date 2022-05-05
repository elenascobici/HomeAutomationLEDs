#include <Arduino.h>
#include <FastLED.h>
#include <Pattern.h>
#include <FillSolid.h>
#include <ColoursFade.h>

const int pin = 5;
const int ledsCount = 60;
char goodReply[] = "Atmega Ok!";
char badReply[] = "Atmega Error";
const bool debugMode = true;

CRGB leds[ledsCount];

// Requests are in the form of c1.255.255.0.c2.0.15.6.p31.d10.b50

char oneByte;
String packetString = "";

int patternDelayBrightness [3];

String currentCommandString;
Pattern* currentPattern;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, pin, GRB>(leds, ledsCount);

  pinMode(pin, OUTPUT);
}

void showMessage(String message)
{
  if (debugMode)
  {
    Serial.print(message + "\n\r");
  }
}

void loop() {
  bool finished = false;
  //showMessage("I'm in the loop");
  if (Serial.available() > 0) {
    oneByte = Serial.read();
    //showMessage("I got: " + String(oneByte));
    if (oneByte != '<' && packetString == ""){
      //showMessage(badReply);
    }
    else{
      packetString += oneByte;
    }
    if (oneByte == '>') {
      //showMessage(String(goodReply) + " packets: " + String(packetString));
      packetString = packetString.substring(1, packetString.length() - 1);
      finished = true;
    }
  }
  String commandString = packetString;
  //showMessage("Command string: " + commandString);
  if (commandString != "" && finished){
    finished = false;
    //showMessage("Received command string: " + commandString);
    currentCommandString = commandString;
    packetString = "";
    currentPattern = CreatePattern(currentCommandString);
    currentPattern->Start();
//    FastLED.setBrightness(100);
//    fill_solid(leds, ledsCount, CRGB(255, 0, 0));
//    FastLED.show();
    //showMessage("Received new command");
  }
  else if (currentPattern != NULL){
    bool yeah = currentPattern->NextStep();
    showMessage(String(yeah));
    //showMessage("Command is same as previous");
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
      showMessage(String(patternParams->colours[j]));
    }
    // Cut the period once more to get rid of the blue number
    commandString = CutPeriod(commandString);
    i+=3;
  }
  showMessage("Right before pattern num: " + commandString);
  patternParams->patternNum = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);
  showMessage("Right before delay time: " + commandString);
  patternParams->delayTime = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);
  showMessage("Right before brightness: " + commandString);
  patternParams->brightness = (commandString.substring(1, commandString.indexOf('.')).toInt());
  commandString = CutPeriod(commandString);

  showMessage("Index 0 of colours: " + String(patternParams->colours[0]));
  showMessage("Index 1 of colours: " + String(patternParams->colours[1]));
  showMessage("Index 2 of colours: " + String(patternParams->colours[2]));
  showMessage("Index 3 of colours: " + String(patternParams->colours[3]));
  showMessage("Index 4 of colours: " + String(patternParams->colours[4]));
  showMessage("Index 5 of colours: " + String(patternParams->colours[5]));

  showMessage("Right before leds Count and leds: " + commandString);
  patternParams->ledsCount = ledsCount;
  patternParams->leds = leds;
  //patternParams->pin = pin;

  showMessage("Pattern Number: " + String(patternParams->patternNum));
  showMessage("Delay time: " + String(patternParams->delayTime));
  showMessage("Brightness: " + String(patternParams->brightness));
  showMessage("Leds Count: " + String(patternParams->ledsCount));
  //showMessage("Pin: " + patternParams->pin);

  return patternParams;
}

// Create and return a new Pattern instance based on the given preset name
Pattern* CreatePattern(String commandString){
  PatternParams* patternParams = SetPatternAttributes(commandString);
  switch (patternParams->patternNum){
    case 0:{
      showMessage("HELLO Index 0 of colours: " + String(patternParams->colours[0]));
      showMessage("HELLO Index 1 of colours: " + String(patternParams->colours[1]));
      showMessage("HELLO Index 2 of colours: " + String(patternParams->colours[2]));
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
