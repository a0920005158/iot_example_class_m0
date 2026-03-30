#include <WiFi.h>

const char* ssid = "JoanPixel";
const char* password = "122105029";

WiFiServer server(8080);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("連線中");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi 已連線");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Socket Server 已啟動，Port: 8080");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("有裝置連入");

    while (client.connected()) {
      if (client.available()) {
        String msg = client.readStringUntil('\n');
        msg.trim();

        Serial.print("收到訊息: ");
        Serial.println(msg);

        String response = "ESP32收到: " + msg + "\n";
        client.print(response);
      }
    }

    client.stop();
    Serial.println("連線結束");
}
