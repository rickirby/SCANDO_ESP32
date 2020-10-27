#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const String PROJECT_VERSION = "0.0.0";

void setup() {
  commonSetting();
  loadVersion();
  wifiSetting();
}

void loop() {
  
}

void commonSetting() {
  Serial.begin(115200);
}

void wifiSetting() {
  // Set WiFi to both mode
  Serial.println("Configuring WiFi Mode...");
  WiFi.mode(WIFI_AP_STA);
  delay(100);
  
  // Access Point Setup
  Serial.println("Configuring Access Point...");
  WiFi.softAP("SCANDO_hardware", "scandohardware");
  IPAddress hardwareIPAddress = WiFi.softAPIP();
  Serial.println();
  Serial.print("Hardware IP Address: ");
  Serial.println(hardwareIPAddress);

  // WiFi Client Setup
  WiFi.begin("Ricki", "rickibinyamin");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("Ricki");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loadVersion() {
  // Printing header and version
  Serial.println();
  Serial.println("============================");
  Serial.println("     RB_QueenMaster_Esp");
  Serial.println("       Version  " + PROJECT_VERSION);
  Serial.println(" Created by Ricki Bin Yamin");
  Serial.println("============================");
  Serial.println();
}
