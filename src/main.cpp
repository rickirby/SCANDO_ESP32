#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <ProjectHeader.hpp>
#include <WifiManager.hpp>

void commonSetting() {
    Serial.begin(115200);
    ProjectHeader::loadHeader();
}

void wifiSetting() {
    WifiManager wifiManager((char*)"ESP32", (char*)"12345678");
    wifiManager.begin();
}

void setup() {
    commonSetting();
    wifiSetting();
}

void loop() {

}
