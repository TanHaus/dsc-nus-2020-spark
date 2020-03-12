#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <CapacitiveSensor.h>

#define LED 1
#define CapSEND 2
#define capRECEIVE 14
#define LED2 3

void retrieveState();
void updateState(int state);

const String name = "lamp1";
const String serverURL = "http://nameless-journey-44724.herokuapp.com/";

CapacitiveSensor capSensor = CapacitiveSensor(CapSEND,capRECEIVE);
int threshold = 1000; // change value here when calibrate sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);

  // Wifi setup
  WiFi.begin("luca", "12345678");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
    Serial.println(capSensor.capacitiveSensor(30));
    Serial.println(millis());
  }
  Serial.println("Success");

  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  delay(500);
}

bool isOn = true;
long startTime = 0;
double analogOutput = 1;

void loop() {
  // put your main code here, to run repeatedly:
  
  if(WiFi.status() == WL_CONNECTED) { 
    // retrieveState();
    int touch = capSensor.capacitiveSensor(30);
    if(touch > threshold) {
      // updateState(1);
      isOn = true;
      // digitalWrite(LED2, HIGH);
      startTime = millis();
    } else {
      // updateState(0);
      isOn = false;
      // digitalWrite(LED2, LOW);
    }

    // code for slowly turn on
    if(isOn) {
      long currentTime = millis();
      if(currentTime - startTime > 100) {
        analogWrite(LED2, (int)analogOutput-1);
        analogOutput = (analogOutput>=1023) ? 1023 : (analogOutput<255 | analogOutput > 764) ? analogOutput*1.2 : analogOutput* 1.4;
        startTime = millis();
      }
      
    } else {
      // digitalWrite(LED2, LOW);
      // analogOutput = 1;
    }
  } else {
      Serial.println("Error in WiFi connection");   
  }

  delay(50);
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