//
//  ProjectHeader.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ProjectHeader.hpp"

void ProjectHeader::loadHeader(String ver) {
    Serial.println();
    Serial.println("====================================");
    Serial.println("         RB_QueenMaster_Esp");
    Serial.println("           Version  " + ver);
    Serial.println("     Created by Ricki Bin Yamin");
    Serial.println("====================================");
    Serial.println();
}