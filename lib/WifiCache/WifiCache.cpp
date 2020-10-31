//
//  WifiCache.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 30/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "WifiCache.hpp"

// MARK: - Singleton

WifiCache* WifiCache::_instance = 0;

WifiCache* WifiCache::shared() {
    if (_instance == 0) {
        _instance = new WifiCache();
    }

    return _instance;
}

// MARK: - Life Cycles

WifiCache::WifiCache() {
    _ssid = new EEPROMClass("eeprom0", 16);
    _pass = new EEPROMClass("eeprom1", 16);

    if (!_ssid->begin(_ssid->length())) {
        Serial.println("Failed to initialise _ssid for cache");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }

    if (!_pass->begin(_pass->length())) {
        Serial.println("Failed to initialise _pass for cache");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
}

WifiCache::~WifiCache() {
}

// MARK: - Public Methods

void WifiCache::cacheWifi(char* SSID, char* PASS) {
    _ssid->put(0, SSID);
    _ssid->put(0, PASS);
}

char* WifiCache::getCacheSSID() {
    char* result;
    _ssid->get(0, result);

    return result;
}

char* WifiCache::getCachePASS() {
    char* result;
    _pass->get(0, result);

    return result;
}

void WifiCache::clearCache() {

}