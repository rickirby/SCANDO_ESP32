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
    Serial.println("=================================================================");
    Serial.println((String)"                       " + PROJECT_NAME);
    Serial.println((String)"                         Version  " + PROJECT_VERSION);
    Serial.println((String)"                   Created by " + PROJECT_OWNER);
    Serial.println("     Copyright © 2020 Ricki Bin Yamin. All rights reserved");
    Serial.println("=================================================================");
    Serial.println();
}