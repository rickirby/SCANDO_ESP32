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
  // Access Point Setup
  Serial.println();
  Serial.println("Configuring Access Point...");
  WiFi.softAP("SCANDO_hardware", "scandohardware");
  IPAddress hardwareIPAddress = WiFi.softAPIP();
  Serial.print("Hardware IP Address: ");
  Serial.println(hardwareIPAddress);
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
