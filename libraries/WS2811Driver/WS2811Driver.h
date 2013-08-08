/**
 * WS2811Driver.h- driver class declaration for the ws2811 rgb led controller IC.
 *
 *   Copyright (C) 2012  Rick Kimball rick@kimballsoftware.com
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 11-15-2012: Initial Version 0.1
 */

#ifndef WS2811DRIVER_H_
#define WS2811DRIVER_H_
#include <msp430.h>
#include <stdint.h>
#include "ws2811.h"

extern "C" void write_ws2811_hs(const uint8_t *data, uint16_t length, uint8_t pinmask);

#define WS2811_DEFAULT_LEDS 4

class WS2811Driver {
private:
    uint16_t _led_cnt; // how many leds in the strip
    uint8_t _pin_mask; // bitmask for example, PORT P1.7 would be BIT7

public:
    WS2811Driver();

    void begin();
    void end();
    void setPinMask(uint8_t mask) { _pin_mask = mask; }
    void setLEDCount(uint16_t cnt) { _led_cnt = cnt; }
    void write(const uint8_t *data,uint16_t datalen);
    void write(const uint8_t *data);
};

#endif /* WS2811DRIVER_H_ */
