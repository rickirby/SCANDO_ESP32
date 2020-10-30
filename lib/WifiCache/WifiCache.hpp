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

// MARK: - Public Methods

static WifiCache* shared();

void cacheWifi(char* SSID, char* PASS);
char* getCacheSSID();
char* getCachePASS();
void clearCache();

private:

// MARK: - Private Properties

static WifiCache* _instance;
EEPROMClass* _ssid;
EEPROMClass* _pass;

// MARK: - Life Cycles, marked as private because it's singeton

WifiCache();
~WifiCache();

};

#endif /* WifiCache_hpp */