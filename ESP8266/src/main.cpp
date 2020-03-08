#include <Arduino.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

void setup() {
  // put your setup code here, to run once:
  Serial.begin(96000);

  WiFiManager wifiManager;
  //first parameter is name of access point, second is the password
  wifiManager.autoConnect("NUS-DSC-2020", "12345678");

  Serial.println("connected...yeey :)");
}

void loop() {
  // put your main code here, to run repeatedly:
}