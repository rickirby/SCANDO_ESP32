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

// MARK: - Life Cycles

WifiCache();
~WifiCache();

// MARK: - Public Methods

void cacheWifi(char* SSID, char* PASS);
char* getCacheSSID();
char* getCachePASS();
void clearCache();

private:

// MARK: - Private Properties

EEPROMClass* _ssid;
EEPROMClass* _pass;

};

#endif /* WifiCache_hpp */