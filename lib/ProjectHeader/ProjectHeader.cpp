//
//  ProjectHeader.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ProjectHeader.hpp"

// MARK: - Public Methods

void ProjectHeader::loadHeader() {

    Serial.println();
    _makeLine(66);
    _centerText(PROJECT_NAME, 70);
    _centerText((String)"Version " + PROJECT_VERSION, 70);
    _centerText((String)"Created by " + PROJECT_OWNER, 70);
    _centerText("Copyright © 2020 Ricki Bin Yamin. All rights reserved", 66);
    _makeLine(66);
    Serial.println();
}

// MARK: - Private Methods

void ProjectHeader::_makeLine(char length) {
    char i = length;
    while (i) {
        Serial.print("=");
        i--;
    }
    Serial.println();
}

void ProjectHeader::_centerText(String text, char containerLength) {
    unsigned char spaces = (containerLength - text.length()) / 2;
    while (spaces) {
        Serial.print(" ");
        spaces--;
    }
    Serial.println(text);
}