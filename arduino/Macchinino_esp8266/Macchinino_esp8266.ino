#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "myServo.h"
#include <WiFiUdp.h>

#define LOCALPORT 5000
#define ACC_PIN 13
#define DIR_PIN 12

#define ACC_MAX 150
#define ACC_MID 90
#define ACC_MIN 50
#define DIR_MAX 138
#define DIR_MID 98
#define DIR_MIN 58

int status = WL_IDLE_STATUS;
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

Servo accServo;
Servo dirServo;

WiFiUDP Udp;
char packetBuffer[255];

void setup() {
  delay(5000);
  Serial.begin(115200);
  delay(10);
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

  accServo.attach(ACC_PIN);
  accServo.write(ACC_MID);
  dirServo.attach(DIR_PIN);
  dirServo.write(DIR_MID);


  Udp.begin(LOCALPORT);
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

    if (packetBuffer[0] == 'A') {
      int num = (int)packetBuffer[1] - 48;
      num = map(num, 0, 9, ACC_MIN, ACC_MAX);
      accServo.write(num);
      delay(15);
    }

    if (packetBuffer[2] == 'D') {
      int num = (int)packetBuffer[3] - 48;
      num = map(num, 0, 9, DIR_MIN, DIR_MAX);
      dirServo.write(num);
      delay(15);
    }
  }
}
