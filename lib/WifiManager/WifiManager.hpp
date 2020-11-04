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
#include <ESPmDNS.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <PROJECT_CONSTANT.h>
#include <WifiCache.hpp>

class WifiManager {

public:

    // MARK: - Public Properties

    AsyncWebServer* server;

    // MARK: - Life Cycles

    WifiManager(char* APSSID, char* APPASS);
    ~WifiManager();

    // MARK: - Public Methods

    void begin();
    void checkWifiStatus();

private:

    // MARK: - Private Properties

    char* _APSSID;
    char* _APPASS;

    bool _isBusy;
    char _indicatorCount;

    // MARK: - Private Methods

    void _setupWifiMode();
    void _setupAccessPoint();
    void _setupServer();
    void _connectSavedWifi();
    void _checkresponseHandler(AsyncWebServerRequest* request);
    void _scanwifiHandler(AsyncWebServerRequest* request);
    void _connectwifiHandler(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total);
    String _connectToAccessPoint(char* ssid, char* pass);
    void _setupDNS();
    void _errorResponse(AsyncWebServerRequest* request, String msg);
    void _successResponse(AsyncWebServerRequest* request, String msg);

};

#endif /* WifiManager_hpp */