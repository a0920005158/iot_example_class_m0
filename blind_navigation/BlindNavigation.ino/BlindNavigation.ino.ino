#include <WiFi.h>

const char* ssid = "JoanPixel";
const char* password = "122105029";

WiFiServer server(8080);

// WiFi 連線函式
bool connectWiFi(unsigned long timeoutMs = 15000) {
  Serial.println();
  Serial.println("初始化 WiFi...");

  // 徹底重置 WiFi 狀態，避免 reset 後卡住
  WiFi.mode(WIFI_OFF);
  delay(500);

  WiFi.mode(WIFI_STA);
  delay(500);

  WiFi.disconnect(true, true);   // 斷線並清除舊設定
  delay(1000);

  Serial.printf("連線到 WiFi: %s\n", ssid);
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  Serial.print("連線中");

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeoutMs) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi 已連線");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("WiFi 連線失敗");
    Serial.print("目前 WiFi status: ");
    Serial.println(WiFi.status());
    return false;
  }
}

// 確保 WiFi 保持連線
void ensureWiFiConnected() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.println("WiFi 已斷線，準備重新連線...");
  connectWiFi();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ESP32 Socket Server 啟動中...");

  connectWiFi();

  server.begin();
  server.setNoDelay(true);  // 降低封包延遲
  Serial.println("Socket Server 已啟動，Port: 8080");
}

void loop() {
  ensureWiFiConnected();

  // 若 WiFi 還沒好，稍等再試
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    return;
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("有裝置連入");

    while (client.connected()) {
      ensureWiFiConnected();

      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi 中斷，關閉 client");
        break;
      }

      if (client.available()) {
        String msg = client.readStringUntil('\n');
        msg.trim();

        Serial.print("收到訊息: ");
        Serial.println(msg);

        int pos = msg.indexOf(':');
        String command = msg;

        if (pos != -1) {
          command = msg.substring(0, pos);
        }

        command.trim();

        Serial.print("command: ");
        Serial.println(command);

        String response = "";

        if (command == "START_TRAFFIC_LIGHT_CHECK") {
          response = "TRAFFIC_LIGHT:GREEN\n";
        } else {
          response = "COMMAND_ERROR\n";
        }

        client.print(response);

        Serial.print("回傳訊息: ");
        Serial.println(response);
      }

      delay(10);
    }

    client.stop();
    Serial.println("連線結束");
  }

  delay(10);
}
