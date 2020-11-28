#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <ProjectHeader.hpp>
#include <WifiManager.hpp>
#include <PROJECT_CONSTANT.h>

WifiManager* wifiManager;

void commonSetting() {
    Serial.begin(115200);
    ProjectHeader::loadHeader();
}

void wifiSetting() {
    String ssid = HARDWARE_PRODUCT_ID;
    String pass = (String)"pass" + (String)HARDWARE_PRODUCT_ID;
    wifiManager = new WifiManager((char*)ssid.c_str(), (char*)pass.c_str());
    wifiManager->begin();
}

void setup() {
    commonSetting();
    wifiSetting();
}

void loop() {
    wifiManager->checkWifiStatus();
}
