//
//  WifiManager.hpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef WifiManager_hpp
#define WifiManager_hpp

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

class WifiManager {
private:
    char* _APSSID;
    char* _APPASS;

    void _scanwifiHandler(AsyncWebServerRequest* request);
public:
    AsyncWebServer* server;

    WifiManager(char* APSSID, char* APPASS);
    ~WifiManager();

    void begin();
};

#endif /* WifiManager */