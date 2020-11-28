//
//  ProjectSetting.hpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 28/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef ProjectSetting_hpp
#define ProjectSetting_hpp

#include <WiFi.h>
#include <PROJECT_INFO.h>
#include <WifiCache.hpp>

class ProjectSetting {

public:

    // MARK: - Public Methods

    static void loadHeader();

private:

    // MARK: - Private Methods

    static void _makeLine(char length);
    static void _centerText(String text, char containerLength);
    static void _resetToFactorySetting();

};

#endif /* ProjectSetting_hpp */