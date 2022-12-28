#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
#define ssid "NETWORK NAME"
#define password "PASSWORD"
#define udpPort 4210

WiFiUDP UDP;
char packet[255];
char goodReply[] = "Ok!";
char badReply[] = "Error";

const int commandPin = 2;

WiFiServer server(80);

void setup() {
  // Setup serial port
  Serial.begin(9600);
  //Serial.println();
   
  // Begin WiFi
  WiFi.begin(ssid, password);

  UDP.begin(udpPort);

  pinMode(commandPin, OUTPUT);
}

void loop() {
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    //Serial.print("Received packet of size ");
    //Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0){
      packet[len] = '\0';
    }

    String packetString = String(packet);
    int stringLength = packetString.length() - 2;
    packetString = packetString.substring(0, stringLength);
    
    if (stringLength > 20 && stringLength < 86 && packetString.substring(0, 1) == "<" && packetString.substring(stringLength - 1) == ">"){
      digitalWrite(commandPin, LOW);
      delay(100);
      Serial.println(packetString);
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      UDP.write(goodReply);
      UDP.endPacket();
      delay(50);
      digitalWrite(commandPin, HIGH);
    }
    else {
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      UDP.write(badReply);
      UDP.endPacket();
    }
  }
}
