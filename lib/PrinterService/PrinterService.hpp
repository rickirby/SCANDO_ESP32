//
//  PrinterService.hpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 06/01/21.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef PrinterService_hpp
#define PrinterService_hpp

#include <WiFi.h>

class PrinterService {

public:

// MARK: - Life Cycles

PrinterService(int strobe, int D7, int D6, int D5, int D4, int D3, int D2, int D1, int D0);
~PrinterService();

};

#endif /* PrinterService_hpp */