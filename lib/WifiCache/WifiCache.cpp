//
//  WifiCache.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 30/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "WifiCache.hpp"

WifiCache::WifiCache() {
    _ssid = new EEPROMClass("eeprom0", 64);
    _pass = new EEPROMClass("eeprom1", 64);

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