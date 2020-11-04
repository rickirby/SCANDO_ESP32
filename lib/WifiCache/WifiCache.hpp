//
//  WifiCache.hpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 30/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef WifiCache_hpp
#define WifiCache_hpp

#include <WiFi.h>
#include <EEPROM.h>

class WifiCache {

public:

// Singleton Instance
static WifiCache* shared();

// MARK: - Public Methods

void cacheWifi(String SSID, String PASS);
String getCacheSSID();
String getCachePASS();

private:

// MARK: - Private Properties

static WifiCache* _instance;

// MARK: - Life Cycles, marked as private because it's singeton

WifiCache();
~WifiCache();

};

#endif /* WifiCache_hpp */