
/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <Ticker.h>
#include "myServo.h"

#include <WiFiUdp.h>

#define servopin 12

int status = WL_IDLE_STATUS;
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

Servo servo;

//WiFiServer server(80);
WiFiUDP Udp;
unsigned int localPort = 5000;
char packetBuffer[255];

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(10);

  servo.attach(servopin);
  servo.write(90);

  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("done");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //server.begin();
  //Serial.println("HTTP server started");
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    
    
  }
}
