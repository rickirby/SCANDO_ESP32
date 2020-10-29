//
//  WifiManager.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "WifiManager.hpp"

WifiManager::WifiManager(char* APSSID, char* APPASS) {
    _APSSID = APSSID;
    _APPASS = APPASS;

    server = new AsyncWebServer(80);
}

WifiManager::~WifiManager() {
}

void WifiManager::begin() {
    // Set WiFi to both mode
    Serial.println("Configuring WiFi Mode...");
    WiFi.mode(WIFI_AP_STA);
    delay(100);

    // Access Point Setup
    Serial.println("Configuring Access Point...");
    WiFi.softAP(_APSSID, _APPASS);
    IPAddress hardwareIPAddress = WiFi.softAPIP();
    Serial.println();
    Serial.println((String)"Access Point \"" + _APSSID + "\" has started.");
    Serial.print("Hardware IP Address: ");
    Serial.println(hardwareIPAddress);

    // Starting Server
    Serial.println("Starting Server...");
    server->on(
        "/scanwifi",
        HTTP_GET,
        [](AsyncWebServerRequest* request) {
            Serial.println("Wifi Scan Request");
            int n = WiFi.scanNetworks();
            Serial.println("scan done");
            if (n == 0) {
                Serial.println("no networks found");
                request->send(200, "text/plain", "Gagal bro!!");
            } else {
                Serial.print(n);
                Serial.println(" networks found");

                AsyncJsonResponse * response = new AsyncJsonResponse();
                response->addHeader("Server","RBQueenMaster");
                JsonObject root = response->getRoot();
                JsonArray wifiList = root.createNestedArray("wifilist");

                for (int i = 0; i < n; ++i) {
                    // Print SSID and RSSI for each network found
                    Serial.print(i + 1);
                    Serial.print(": ");
                    Serial.print(WiFi.SSID(i));
                    Serial.print(" (");
                    Serial.print(WiFi.RSSI(i));
                    Serial.print(")");
                    Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

                    wifiList.add(WiFi.SSID(i));

                    delay(10);
                }

                response->setLength();
                request->send(response);
            }
        }
    );

    server->begin();
    Serial.println("Server Started!");
}