#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <CapacitiveSensor.h>

#define LED 1
#define LED2 3
#define CapSEND 2
#define capRECEIVE 14

int getState(int);
int updateOtherLampState(int);
void lightUp();

int thisLamp = ESP.getChipId();
int otherLamp = thisLamp == 2730997 ? 2730081 : 2730997;

int thisLampStateServer = 0;
int thisLampStateLocal = 0;
int otherLampStateServer = 0;
int otherLampStateSensor = 0;

void getStates();
void updateState(int state);

const String serverURL = "http://nameless-journey-44724.herokuapp.com/";

CapacitiveSensor capSensor = CapacitiveSensor(CapSEND,capRECEIVE);
int threshold = 800; // change value here when calibrate sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);

  // Wifi setup
  WiFi.begin("luca", "12345678");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
    Serial.println(capSensor.capacitiveSensorRaw(30));
  }
  Serial.println("Success");

  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  delay(500);
}

void loop() {
  // GET request to obtain current lamp states from server
  thisLampStateServer = getState(thisLamp);
  otherLampStateServer = getState(otherLamp);

  // check the state of this lamp and update accordingly
  if (thisLampStateLocal == 0 && thisLampStateServer == 1) {
    lightUp();
  } else if (thisLampStateLocal == 1 && thisLampStateServer == 0) {
    digitalWrite(LED, 0);
    digitalWrite(LED2, 0);
  }
  thisLampStateLocal = thisLampStateServer;

  // get the state of the other lamp from the sensor
  int touch = capSensor.capacitiveSensorRaw(30);
    if(touch > threshold) {
      otherLampStateSensor = 1;
    } else {
      otherLampStateSensor = 0;
    }

  // check the state of the other lamp with the server value. if different then send POST request to server to update.
  if (otherLampStateSensor != otherLampStateServer) {
    updateOtherLampState(otherLampStateSensor);
  }

  delay(200);

}

int getState(int lampID) {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String getURL = serverURL + "state?name=" + lampID;
  http.begin(getURL);      //Specify request destination
  
  int httpCode = http.GET();   //Send GET request
  String payload = http.getString();                  //Get the response payload
 
  http.end();  //Close connection
  
  return payload.toInt();  
}

int updateOtherLampState(int state) {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String postURL = serverURL + "state";
  Serial.println(postURL);
  http.begin(postURL);      //Specify request destination
  
  http.addHeader("Content-Type", "application/json");  //Specify content-type header
  int httpCode = http.POST("{\"name\":\"" + String(otherLamp) + "\",\"state\":\"" + String(state) + "\"}");    //Send POST request
  String payload = http.getString();                  //Get the response payload

  http.end();  //Close connection

  return payload.toInt();
}

void lightUp() {
  double i = 1; 
  while (i<1024) {
    analogWrite(LED, (int)i - 1);
    analogWrite(LED2, (int)i - 1);
    i = (i>=1023) ? 1023 : (i<255 || i > 764) ? i*1.2 : i* 1.4;
    delay(50);
  }
}