#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <ProjectSetting.hpp>
#include <WifiManager.hpp>
#include <PROJECT_CONSTANT.h>
#include <PrinterService.hpp>

PrinterService* printerService;
WifiManager* wifiManager;

void commonSetting() {
    Serial.begin(115200);
    delay(1000);
    ProjectSetting::loadHeader();
    ProjectSetting::checkIfFactoryResetTriggered();
}

void configurePrinterService() {
    printerService = new PrinterService(35, 34, 13, 12, 14, 27, 26, 25, 33, 32);
}

void wifiSetting() {
    String ssid = (String)"BP" + (String)HARDWARE_PRODUCT_ID;
    String pass = (String)"pass" + (String)HARDWARE_PRODUCT_ID;
    wifiManager = new WifiManager((char*)ssid.c_str(), (char*)pass.c_str(), printerService);
    wifiManager->begin();
}

void setup() {
    commonSetting();
    configurePrinterService();
    wifiSetting();
}

void loop() {
    wifiManager->checkWifiStatus();
}
