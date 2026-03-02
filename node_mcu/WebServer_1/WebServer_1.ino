#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "home.h"
#include "switch_6.h"

const char* ssid = "thmrb305";
const char* password = "thmrbthmrbthmrb";

ESP8266WebServer server(80);

#define LED1 2
#define LED2 14
#define LED3 12
#define LED4 13
#define LED5 15

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);

  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);

  pinMode(LED4, OUTPUT);
  digitalWrite(LED4, LOW);

  pinMode(LED5, OUTPUT);
  digitalWrite(LED5, LOW);

  WiFi.begin(ssid, password);
  Serial.println("");
  while(WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to :");
  Serial.println(ssid);
  Serial.print("IP address :");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.on("/on",handleLedOn);
  server.on("/off",handleLedOff);
  server.on("/switch",handleSwitch);
  server.on("/home",handleHome);
  server.on("/home/led",handleHomeLed);

  server.begin();
  Serial.println("Http server start");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleHome(void){
  String data = "Home control link ok";
  server.send(200,"text/html",data);
}

void handleHomeLed(void){
  Serial.println("Led control");
  if(server.method() == HTTP_POST){
    if(server.hasArg("led")){
      String ledNum = server.arg("led");
      String ledStatus = server.arg("state");
      controlLED(ledNum,ledStatus);
      server.send(200,"text/html","LED OK: "+ledNum+" - "+ledStatus);
    }
  }else {
    server.send(200,"text/html", "Start Led switch");
  }
}

void controlLED(String ledNum, String ledStatus) {
  int ledNo = ledNum.toInt();

  switch(ledNo) {
    case 1:
      if(ledStatus == "on")
        digitalWrite(LED1, LOW);
      else
        digitalWrite(LED1, HIGH);
      break;
    case 2:
      if(ledStatus == "on")
        digitalWrite(LED2, HIGH);
      else
        digitalWrite(LED2, LOW);
      break;
    case 3:
      if(ledStatus == "on")
        digitalWrite(LED3, HIGH);
      else
        digitalWrite(LED3, LOW);
      break;
    case 4:
      if(ledStatus == "on")
        digitalWrite(LED4, HIGH);
      else
        digitalWrite(LED4, LOW);
      break;
    case 5:
      if(ledStatus == "on")
        digitalWrite(LED5, HIGH);
      else
        digitalWrite(LED5, LOW);
      break;  
  }
}

void handleSwitch(){
  Serial.println("Switch control");
  if(server.method() == HTTP_POST){
    String ledNum = server.arg("led");
    String ledStatus = server.arg("state");
    controlLED(ledNum,ledStatus);
    server.send(200,"text/html","LED OK: "+ledNum+" - "+ledStatus);
  }else {
    Serial.println("show switch page");
    String data = Switch_page;
    server.send(200,"text/html",data);
  }
}

void handleLedOn(){
  Serial.println("Led on");
  digitalWrite(LED1, LOW);
  server.send(200,"text/html","LED 1 is on");  
}

void handleLedOff(){
  Serial.println("Led off");
  digitalWrite(LED1, HIGH);
  server.send(200,"text/html","LED 1 is off"); 
}

void handleRoot() {
  Serial.println("root call");
  String s = "Connect ok";
  String data = MainPage;
  server.send(200,"text/html",data);
}
