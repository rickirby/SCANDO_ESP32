//
//  ProjectHeader.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ProjectHeader.hpp"

void ProjectHeader::loadHeader() {

    Serial.println();
    makeLine(66);
    centerText(PROJECT_NAME, 70);
    centerText((String)"Version " + PROJECT_VERSION, 70);
    centerText((String)"Created by " + PROJECT_OWNER, 70);
    centerText("Copyright © 2020 Ricki Bin Yamin. All rights reserved", 66);
    makeLine(66);
    Serial.println();
}

void ProjectHeader::makeLine(char length) {
    char i = length;
    while (i) {
        Serial.print("=");
        i--;
    }
    Serial.println();
}

void ProjectHeader::centerText(String text, char containerLength) {
    unsigned char spaces = (containerLength - text.length()) / 2;
    while (spaces) {
        Serial.print(" ");
        spaces--;
    }
    Serial.println(text);
}