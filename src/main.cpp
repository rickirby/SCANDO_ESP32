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
    wifiManager = new WifiManager((char*)HARDWARE_SSID, (char*)HARDWARE_PASS);
    wifiManager->begin();
}

void setup() {
    commonSetting();
    wifiSetting();
}

void loop() {
    wifiManager->checkWifiStatus();
}