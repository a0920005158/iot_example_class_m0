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

const int http_port_ip = 8080;
char serverName_ip[]="192.168.58.1";
char sendData_write_ip[]="GET /data/?data=";
char receiveData[20] = "T25H60";
char sendEnd[]=" HTTP/1.1\r\n";
char sendData_1_host[] = "Host:192.168.58.1 \r\n";
char sendData_final[80];

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

  sprintf(sendData_final,"%s%s%s",sendData_write_ip,receiveData,sendEnd);
  Serial.println(sendData_final);
  
  if(client.connect(serverName_ip,http_port_ip)){
    Serial.println("connect to ip");
    client.print(sendData_final);
    delay(100);
    client.print(sendData_1_host);
    delay(100);
    client.println();
  }

  check_link();
  
}

void loop() {

}

void check_link(){
  int count = 0;
  delay(3000);
  count=client.available();
  if(count>0){
    for(int i=0;i<count;i++){
      char c = client.read();
      Serial.print(c);  
    }  
  }

  if(!client.connected())
    client.stop();
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
