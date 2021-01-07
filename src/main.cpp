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

TaskHandle_t Task1;
TaskHandle_t Task2;

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

void Task1code(void* pvParameters ){
    while(true) {
        wifiManager->checkWifiStatus();
    }
}

void Task2code(void* pvParameters ){
    while(true) {
        Serial.println("Task2");
        delay(300);
    }
}

void configureTask() {
    xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
    delay(500); 
    
    xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);          /* pin task to core 1 */
    delay(500); 
}

void setup() {
    commonSetting();
    configurePrinterService();
    wifiSetting();
    configureTask();
}

void loop() {
}