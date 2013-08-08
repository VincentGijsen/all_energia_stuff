//
//  utils.h
//
//
//  Created by Vincent Gijsen on 7/5/13.
//
//

#include "Energia.h"

#ifndef _utils_h_
#define _utils_h_

#define SAMPLES 3
#define BLINK_DELAY 5


class Utils  {

public:
	Utils();
    void initRed();
    void blinkRed(uint8_t);
    void blinkRed();
    uint32_t readTemperature();
    uint16_t readBattery();
#ifdef VERBOSE > 0
    void printDec(uint32_t);
    void dump_radio_status_to_serialport(uint8_t);
#endif

private:
    void blink();
    private:
    uint32_t _average;
    uint32_t _values[SAMPLES];



};

#endif _utils_h_
