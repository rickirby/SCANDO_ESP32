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
    
    // Constructor

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

    _printingData = "";
    _blinkLedCount = 0;

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
    // Destructor
}

// MARK: - Public Method

void PrinterService::braillePrint(const char* data) {
    _printingData = data;
}

void PrinterService::executePrint() {
    if (*_printingData) {
        _sendBufferData(_printingData);
        _endBuffer();
        _printingData = "";
        _blinkLedCount = 0;
    }
}

// MARK: - Private Method

void PrinterService::_parallelizeData(char data) {
    digitalWrite(_D7, (data & (1 << 7)) >> 7);
    digitalWrite(_D6, (data & (1 << 6)) >> 6);
    digitalWrite(_D5, (data & (1 << 5)) >> 5);
    digitalWrite(_D4, (data & (1 << 4)) >> 4);
    digitalWrite(_D3, (data & (1 << 3)) >> 3);
    digitalWrite(_D2, (data & (1 << 2)) >> 2);
    digitalWrite(_D1, (data & (1 << 1)) >> 1);
    digitalWrite(_D0, (data & (1 << 0)) >> 0);

    Serial.print(data);
    Serial.print("-");
    Serial.print((data & (1 << 7)) >> 7);
    Serial.print((data & (1 << 6)) >> 6);
    Serial.print((data & (1 << 5)) >> 5);
    Serial.print((data & (1 << 4)) >> 4);
    Serial.print((data & (1 << 3)) >> 3);
    Serial.print((data & (1 << 2)) >> 2);
    Serial.print((data & (1 << 1)) >> 1);
    Serial.print((data & (1 << 0)) >> 0);
    Serial.print(" ");
}

void PrinterService::_tickStrobe() {
    digitalWrite(_strobe, LOW);
    delay(1);
    digitalWrite(_strobe, HIGH);
    delay(1);

    if (_blinkLedCount == 20) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else if (_blinkLedCount > 40) {
        digitalWrite(LED_BUILTIN, LOW);
        _blinkLedCount = 0;
    }

    _blinkLedCount++;
}

void PrinterService::_sendBufferData(const char* data) {
    while (*data) {

        // Checking busy line

        // int timeout = 500;
        // while (digitalRead(_busy)) {
        //     delay(10);
        //     if (!timeout) {
        //         Serial.println("Got Timeout on checking busy line");
        //         break;
        //     }

        //     timeout--;
        // }

        _parallelizeData(*data);
        _tickStrobe();

        data++;
    }
}

void PrinterService::_endBuffer() {
    // Checking busy line

    // int timeout = 500;
    // while (digitalRead(_busy)) {
    //     delay(10);
    //     if (!timeout) {
    //         Serial.println("Got Timeout on checking busy line");
    //         break;
    //     }

    //     timeout--;
    // }

    _parallelizeData(0x0A);
    _parallelizeData(0x00);
    _tickStrobe();
    digitalWrite(LED_BUILTIN, LOW);
}