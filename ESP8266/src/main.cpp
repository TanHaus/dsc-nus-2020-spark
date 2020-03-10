#include <Arduino.h>
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

#define LED 1
#define BUTTON 2

void retrieveState();
void updateState(int state);

const String name = "lamp1";
const String serverURL = "http://nameless-journey-44724.herokuapp.com/";

void setup() {
  // // put your setup code here, to run once:

  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("luca", "12345678");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }

  pinMode(LED, OUTPUT);    // LED pin as output.
  pinMode(BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED) {   //Check WiFi connection status
    int isPressed = digitalRead(BUTTON);
    // isPressed = 0;
    updateState(isPressed);
    retrieveState();
  
 } else {
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(100);  //Send a request every 30 seconds
}

void retrieveState() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String getURL = serverURL + "state?name=" + name;
  Serial.println(getURL);
  http.begin(getURL);      //Specify request destination
  
  int httpCode = http.GET();   //Send GET request
  String payload = http.getString();                  //Get the response payload
 
  Serial.print("return code: ");   //Print HTTP return code
  Serial.println(httpCode);
  Serial.println("payload: " + payload);    //Print request response payload
  
  int state = payload.toInt();
  digitalWrite(LED, !state);// turn the LED off.(Note that LOW is the voltage level but actually 
  
  http.end();  //Close connection
}

void updateState(int state) {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String postURL = serverURL + "state";
  Serial.println(postURL);
  http.begin(postURL);      //Specify request destination
  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
  int httpCode = http.POST("name=" + name + "&state=" + state);    //Send POST request
  String payload = http.getString();                  //Get the response payload
 
  Serial.print("return code: ");   //Print HTTP return code
  Serial.println(httpCode);
  Serial.println("payload: " + payload);    //Print request response payload

  http.end();  //Close connection
}

