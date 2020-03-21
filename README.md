# dsc-nus-2020: spark | TanHaus

## Pitch Deck & Videos

Google slides link: https://docs.google.com/presentation/d/1xdLZvk9dbZq9XlXSCC27bYtxi7I_jPIso7VwoPeOLsY/edit?usp=sharing

Areas covered:
- Problem Statement & Scope
- Motivation for Solution
- Circuit Diagram
- Signal Flow
- Code Review
- User Stories
- Impact & Novelty
- Further Developments

Videos:
- Promotional Video: https://youtu.be/5YZy3o9l7lA
- Demo Video: https://youtu.be/mlj6l9t8dcU

## Technical Aspects

ESP8266 12-E NodeMCU kit pinout diagram retrieved from ``https://arduino-esp8266.readthedocs.io/en/latest/reference.html#digital-io``
![ESP8266 12-E NodeMCU kit pinout diagram](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?w=817&ssl=1 "ESP8266 12-E NodeMCU kit pinout diagram")

**Our board type**: NodeMCU 1.0

Angle light magnet type
- Voltage: 1.5V (3 AAA batteries)
- Current draw: 180mA

Sparking egg
- Voltage: 4.5V (3 LR44 batteries)
- Current draw: 80mA

Some resources:
- Guide to ESP8266: https://tttapa.github.io/ESP8266/Chap04%20-%20Microcontroller.html
- https://www.make-it.ca/nodemcu-arduino/nodemcu-details-specifications/
- https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
- ESP8266 Arduino: https://github.com/esp8266/Arduino
- Use transistor as a digital switch: https://itp.nyu.edu/physcomp/labs/motors-and-transistors/using-a-transistor-to-control-high-current-loads-with-an-arduino/
- Capacitive sensing:
    - Arduino library (can be installed directly through Arduino IDE): https://playground.arduino.cc/Main/CapacitiveSensor/
    - Problems with ESP8266: https://forum.arduino.cc/index.php?topic=462160.0
- ESP8266 control from the internet: https://maker.pro/esp8266/tutorial/esp8266-tutorial-how-to-control-anything-from-the-internet

## Internet connection

Source: https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/

POST and GET requests

Libraries
```cpp
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
```

Main code
```cpp
HTTPClient http;

http.begin("http://jsonplaceholder.typicode.com/users/1");

int httpCode = http.GET();
String payload = http.getString();   //Get the request response payload 

http.end();   //Close connection
```

For POST request
```cpp
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
int httpCode = http.POST("content=Hello");    //Send POST request
```

## Circuit diagram

![circuit diagram](circuit&#32;diagram&#32;with&#32;bg.png)
