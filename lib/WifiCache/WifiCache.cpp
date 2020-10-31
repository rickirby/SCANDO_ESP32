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
    EEPROM.begin(512);

    Serial.println("Success init WifiCache");
}

WifiCache::~WifiCache() {
}

// MARK: - Public Methods

void WifiCache::cacheWifi(String SSID, String PASS) {
    for (int i = 0; i < SSID.length(); i++) {
        EEPROM.write(i, SSID[i]);
    }

    for (int i = 0; i < PASS.length(); i++) {
        EEPROM.write(32 + i, PASS[i]);
    }

    EEPROM.commit();
}

String WifiCache::getCacheSSID() {
    String value;
    for (int i = 0; i < 32; i++) {
        value += char(EEPROM.read(i));
    }

    return value;
}

String WifiCache::getCachePASS() {
    String value;
    for (int i = 32; i < 96; i++) {
        value += char(EEPROM.read(i));
    }

    return value;
}

void WifiCache::clearCache() {

}