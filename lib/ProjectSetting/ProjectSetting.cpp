//
//  ProjectSetting.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ProjectSetting.hpp"

// MARK: - Public Methods

void ProjectSetting::loadHeader() {

    Serial.println();
    _makeLine(66);
    _centerText(PROJECT_NAME, 70);
    _centerText((String)"Version " + PROJECT_VERSION, 70);
    _centerText((String)"Created by " + PROJECT_OWNER, 70);
    _centerText("Copyright © 2020 Ricki Bin Yamin. All rights reserved", 66);
    _makeLine(66);
    Serial.println();
}

void ProjectSetting::checkIfFactoryResetTriggered() {
    pinMode(15, INPUT_PULLUP);
    delay(100);

    unsigned char checkCount = 8;

    while (!digitalRead(15)) {
        if (checkCount == 0) {
            _resetToFactorySetting();
            break;
        }

        delay(1000);
        Serial.println("Factory Reset Triggered");
        Serial.print("Check count: ");
        Serial.println(checkCount);
        checkCount--;
    }
     
}

// MARK: - Private Methods

void ProjectSetting::_makeLine(char length) {
    char i = length;
    while (i) {
        Serial.print("=");
        i--;
    }
    Serial.println();
}

void ProjectSetting::_centerText(String text, char containerLength) {
    unsigned char spaces = (containerLength - text.length()) / 2;
    while (spaces) {
        Serial.print(" ");
        spaces--;
    }
    Serial.println(text);
}

void ProjectSetting::_resetToFactorySetting() {
    WifiCache::shared()->cacheWifi("FACTORY_SETTING", "FACTORY_SETTING");
    Serial.println("Done Resetting to Factory Setting");
    Serial.println();
}