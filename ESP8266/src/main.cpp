#include <Arduino.h>
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

void setup() {
  // // put your setup code here, to run once:

  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("luca", "12345678");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
  HTTPClient http;    //Declare object of class HTTPClient
 
  http.begin("http://nameless-journey-44724.herokuapp.com/");      //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
 
  //  int httpCode = http.GET();   //Send GET request
   int httpCode = http.POST("content=Hello");    //Send POST request
   String payload = http.getString();                  //Get the response payload
 
   Serial.print("return code: ");   //Print HTTP return code
   Serial.println(httpCode);
   Serial.println("payload: " + payload);    //Print request response payload
 
   http.end();  //Close connection
 
 } else {
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(5000);  //Send a request every 30 seconds
}