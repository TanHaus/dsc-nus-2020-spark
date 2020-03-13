#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <CapacitiveSensor.h>

#define LED 1
#define CapSEND 2
#define capRECEIVE 14

int thisLamp = ESP.getChipId();
int otherLamp = thisLamp == 2730997 ? 2730081 : 2730997;

int thisLampState = 0;
int otherLampState = 0;

void getStates();
void updateState(int state);

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
  }
  Serial.println("Success");

  pinMode(LED, OUTPUT);
  delay(500);
}

void loop() {
  int thisLampStateTemp = getState(thisLamp);
  otherLampState = getState(otherLamp);

  if (thisLampState == 0 && thisLampStateTemp == 1) {
    thisLampState = thisLampStateTemp;
    lightUp();
  } else if ()
  }

}

int getStates(int lampID) {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String getURL = serverURL + "state?name=" + lampID;
  http.begin(getURL);      //Specify request destination
  
  int httpCode = http.GET();   //Send GET request
  String payload = http.getString();                  //Get the response payload
 
  http.end();  //Close connection
  
  return payload.toInt();  
}

void lightUp() {

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