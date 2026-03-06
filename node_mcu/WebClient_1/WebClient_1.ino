#include <AM2302-Sensor.h>

AM2302::AM2302_Sensor am2302(4);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


const char* ssid = "thmrb305";
const char* password = "thmrbthmrbthmrb";

#define LED1 2

int status = WL_IDLE_STATUS;
WiFiClient client;
const int http_port = 80;

char serverName_thingspeak[] = "api.thingspeak.com";
char sendData_write[] = "GET /update?api_key=26QSDSHKGWGWMXX4&field1=25&field2=65 HTTP/1.1\r\n";
char sendData_1[] = "Host:api.thingspeak.com \r\n";
char sendData_2[] = "Connection: close\r\n\r\n";

//#include <DHT.h>

#include <Ticker.h>

//#define DHTPin D2
//#define DHTType DHT11

//DHT dht(DHTPin, DHTType);

Ticker timer;
volatile bool readFlag = false;

void setFlag(){
  readFlag = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  
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

  client_send();
  timer.attach(5.0,setFlag);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(readFlag){
    readFlag = false;
//    float t = dht.readTemperature();
//    float h = dht.readHumidity();
    int status = am2302.read();
    if(status == 0){
      float t = am2302.get_Temperature();
      float h = am2302.get_Humidity();

      if(isnan(h) || isnan(t)){
        Serial.println("read failed");
        return; 
      }
      Serial.println(t);
      Serial.println(h);
      Serial.println(); 
    }
  }
}

void client_send(){
  Serial.println("Link to thingspeak");
  if(client.connect(serverName_thingspeak,http_port)){
    Serial.println("connected");
    client.print(sendData_write);
    delay(100);
    client.print(sendData_1);
    delay(100);
    client.print(sendData_2);
  }

  delay(1000);
  client.stop();
}
