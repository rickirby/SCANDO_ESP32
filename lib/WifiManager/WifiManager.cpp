//
//  WifiManager.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "WifiManager.hpp"

// MARK: - Life Cycles

WifiManager::WifiManager(char* APSSID, char* APPASS) {
    _APSSID = APSSID;
    _APPASS = APPASS;

    _isBusy = false;
    _indicatorCount = 0;

    server = new AsyncWebServer(80);
}

WifiManager::~WifiManager() {
}

// MARK: - Public Methods

void WifiManager::begin() {
    _isBusy = true;

    // Set WiFi to both mode
    _setupWifiMode();

    // Access Point Setup
    _setupAccessPoint();

    // Server Setup
    _setupServer();

    // Check Saved Wifi Setting
    _connectSavedWifi();

    // Set Build in LED as Output as connection status
    pinMode(LED_BUILTIN, OUTPUT);

    _isBusy = false;
}

void WifiManager::checkWifiStatus() {
    if ((WiFi.status() != WL_CONNECTED) && !_isBusy) {
        Serial.println("WiFi not connected");
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(200);
            digitalWrite(LED_BUILTIN, LOW);
            delay(200);
        }
        
        if (_indicatorCount > 3) {
            _connectSavedWifi();
            _indicatorCount = 0;
        }

        _indicatorCount++;
    }

    delay(5000);
}

// MARK: - Private Methods

void WifiManager::_setupWifiMode() {
    Serial.println("Configuring wifi mode...");
    WiFi.mode(WIFI_AP_STA);
    delay(100);
}

void WifiManager::_setupAccessPoint() {
    Serial.println("Configuring access point...");
    WiFi.softAP(_APSSID, _APPASS);
    IPAddress hardwareIPAddress = WiFi.softAPIP();
    Serial.println();
    Serial.println((String)"Access Point \"" + _APSSID + "\" has started.");
    Serial.print("Hardware IP Address: ");
    Serial.println(hardwareIPAddress);
}

void WifiManager::_setupServer() {
    // Starting Server
    Serial.println();
    Serial.println("Starting server...");

    // checkresponse server through GET request
    server->on(
        "/checkresponse",
        HTTP_GET,
        [this](AsyncWebServerRequest* request) {
            _checkresponseHandler(request);
        }
    );

    // scanwifi server through GET request
    server->on(
        "/scanwifi",
        HTTP_GET,
        [this](AsyncWebServerRequest* request) {
            _scanwifiHandler(request);
        }
    );

    // connectwifi server through POST request
    server->on(
        "/connectwifi",
        HTTP_POST,
        [](AsyncWebServerRequest* request) {},
        NULL,
        [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
            _connectwifiHandler(request, data, len, index, total);
        }
    );

    // not found handler
    server->onNotFound(
        [](AsyncWebServerRequest* request) {
            request->send(404);
        }
    );

    server->begin();
    Serial.println("Server Started!");
}

void WifiManager::_connectSavedWifi() {
    String savedSSID = WifiCache::shared()->getCacheSSID();
    String savedPASS = WifiCache::shared()->getCachePASS();

    String ipaddress = _connectToAccessPoint((char*)savedSSID.c_str(), (char*)savedPASS.c_str());
    if (ipaddress.isEmpty()) {
        return;
    }

    _setupDNS();
}

void WifiManager::_checkresponseHandler(AsyncWebServerRequest* request) {
    _isBusy = true;
    Serial.println();
    Serial.println("Got check response request..");
    
    _successResponse(request, "OK");
    _isBusy = false;
}

void WifiManager::_scanwifiHandler(AsyncWebServerRequest* request) {
    _isBusy = true;
    Serial.println();
    Serial.println("Got wifi scan request..");

    // Disconnect from previously wifi first
    WiFi.disconnect();
    delay(100);

    // Scan nearby wifi network
    Serial.println("Scanning...");
    int n = WiFi.scanNetworks();
    Serial.println();
    Serial.println("Scanning Done!");
    
    Serial.print(n);
    Serial.println(" networks found");

    // Prepare json encoder
    AsyncJsonResponse * response = new AsyncJsonResponse();
    response->addHeader("Server","RBQueenMaster");
    JsonObject root = response->getRoot();
    JsonArray wifiList = root.createNestedArray("wifilist");

    // Print scanned wifi network
    for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

        // Append json data
        wifiList.add(WiFi.SSID(i));

        delay(10);
    }

    // Send response
    response->setLength();
    request->send(response);
    _isBusy = false;
}

void WifiManager::_connectwifiHandler(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
    _isBusy = true;
    Serial.println();
    Serial.println("Got wifi connect request..");

    // Process json data
    String jsonData;
    for (size_t i = 0; i < len; i++) {
        jsonData += (char)data[i];
    }
    
    Serial.println("Raw JSON data:");
    Serial.println(jsonData);

    // Decode json data
    StaticJsonDocument<200> doc;
    deserializeJson(doc, jsonData);
    const char* ssid = doc["ssid"];
    const char* pass = doc["pass"];

    Serial.println((String)"SSID: " + ssid);
    Serial.println((String)"PASS: " + pass);
    Serial.println();

    // Connect to Access Point
    const String ipaddress = _connectToAccessPoint((char*)ssid, (char*)pass);
    if (ipaddress.isEmpty()) {
        _errorResponse(request, "Could not connect");
        _isBusy = false;
        return;
    }

    // Save Wifi Cache
    WifiCache::shared()->cacheWifi(ssid, pass);

    // Start local dns
    _setupDNS();

    // Send success response with ipaddress as message
    _successResponse(request, ipaddress);
    _isBusy = false;
}

void WifiManager::_senddataHandler(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
    _isBusy = true;
    Serial.println();
    Serial.println("Got send data request..");

    // Process json data
    String jsonData;
    for (size_t i = 0; i < len; i++) {
        jsonData += (char)data[i];
    }
    
    Serial.println("Raw JSON data:");
    Serial.println(jsonData);

    // Decode json data
    StaticJsonDocument<200> doc;
    deserializeJson(doc, jsonData);
    const char* textData = doc["data"];

    Serial.println();
    Serial.println(textData);
    Serial.println();

    _successResponse(request, "OK");
    _isBusy = false;
}

String WifiManager::_connectToAccessPoint(char* ssid, char* pass) {
    Serial.print((String)"Connecting to " + ssid);
    unsigned char countToTimeout = 0;
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
        if (countToTimeout > 30) {
            Serial.println();
            Serial.println((String)"Failed connecting to " + ssid);
            // _errorResponse(request, "Could not connect");
            return "";
        }
        countToTimeout++;
    }
    Serial.println();
    Serial.println((String)"Connected to " + ssid);
    Serial.print("IP address: ");
    const String ipaddress = WiFi.localIP().toString();
    Serial.println(ipaddress);

    return ipaddress;
}

void WifiManager::_setupDNS() {
    if (MDNS.begin(HARDWARE_LOCAL_DNS)) {
        Serial.println((String)"mDNS responder started with " + HARDWARE_LOCAL_DNS + ".local");
    } else {
        Serial.println("Error setting up MDNS responder!");
    }
}

void WifiManager::_errorResponse(AsyncWebServerRequest* request, String msg) {
    request->send(400, "application/json", "{\"msg\":\"" + msg + "\"}");
}

void WifiManager::_successResponse(AsyncWebServerRequest* request, String msg) {
    request->send(200, "application/json", "{\"msg\":\"" + msg + "\"}");
}