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

PrinterService(int busy, int strobe, int D7, int D6, int D5, int D4, int D3, int D2, int D1, int D0);
~PrinterService();

private:

// MARK: - Private Properties

int _busy;
int _strobe;
int _D7, _D6, _D5, _D4, _D3, _D2, _D1, _D0;

// MARK: - Private Method

void _parallelizeData(char data);
void _tickStrobe();
void _sendBufferData(char* data);

};

#endif /* PrinterService_hpp */