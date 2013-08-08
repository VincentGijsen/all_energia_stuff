/**
 * WS2811Driver.cpp - driver class implementation for the ws2811 rgb led controller IC.
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
#include "Energia.h"
#include "WS2811Driver.h"

extern "C" void disableWatchDog();
extern "C" void enableWatchDog();

WS2811Driver::WS2811Driver() :
  _led_cnt(WS2811_DEFAULT_LEDS)
  ,_pin_mask(WS2811_BITMASK)
{
}

void WS2811Driver::begin()
{
    WS2811_PORTDIR |= _pin_mask;
}

void WS2811Driver::end()
{
    WS2811_PORTDIR &= ~_pin_mask;
}

void WS2811Driver::write(const uint8_t *data, uint16_t len) {
    disableWatchDog();
    write_ws2811_hs(data, len, _pin_mask);
    enableWatchDog();
}

void WS2811Driver::write(const uint8_t *data) {
    write(data,_led_cnt * 3);
}
