//
//  PrinterService.cpp
//  RBQueenMaster
//
//  Created by Ricki Bin Yamin on 06/01/21.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "PrinterService.hpp"

// MARK: - Life Cycles

PrinterService::PrinterService(int busy, int strobe, int D7, int D6, int D5, int D4, int D3, int D2, int D1, int D0) {
    
    _busy = busy;
    _strobe = strobe;
    _D7 = D7;
    _D6 = D6;
    _D5 = D5;
    _D4 = D4;
    _D3 = D3;
    _D2 = D2;
    _D1 = D1;
    _D0 = D0;

    pinMode(busy, INPUT_PULLUP);
    pinMode(strobe, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D0, OUTPUT);

    digitalWrite(strobe, HIGH);
}

PrinterService::~PrinterService() {
}

// MARK: - Private Method

void PrinterService::_parallelizeData(unsigned char data) {

}

void PrinterService::_tickStrobe() {

}