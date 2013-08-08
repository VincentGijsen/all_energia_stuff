/*
 AD9850.h - Library for adding simple AD9850/AD9851 control capabilities on MSP430 and various micro-controller
 
 Copyright 2012-2013 Yannick DEVOS under GPL 3.0 license
 Any commercial use or inclusion in a kit is subject to author approval
 
 Based on work by G7UVW
 
 ====
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You can download a copy of the GNU General Public License at <http://www.gnu.org/licenses/>
 
 
 */

// include this library's description file
#include <AD9850.h>


#define DDS_CLOCK 125000000		// This need to be adjusted sometime

//#define IS_AD9851				// This is for an AD981
//#define DDS_CLOCK 180000000		// With 30MHz canned oscillator multiplied by 6 by the chip


// Constructor /////////////////////////////////////////////////////////////////
uint8_t _DDSpinClock;
uint8_t _DDSpinLoad;
uint8_t _DDSpinData;
uint8_t _DDSpinReset;

AD9850::AD9850(uint8_t pinClock, uint8_t pinLoad, uint8_t pinData, uint8_t pinReset)
{
	_DDSpinClock = pinClock;
	_DDSpinLoad = pinLoad;
	_DDSpinData = pinData;
	_DDSpinReset = pinReset;
	
};

// Methods /////////////////////////////////////////////////////////////////


void AD9850::begin()
{
    pinMode (_DDSpinClock, OUTPUT); 
    pinMode (_DDSpinLoad,  OUTPUT); 
    pinMode (_DDSpinData,  OUTPUT); 
    pinMode (_DDSpinReset, OUTPUT);
	
	digitalWrite(_DDSpinReset, LOW);
	digitalWrite(_DDSpinClock, LOW);
	digitalWrite(_DDSpinLoad, LOW);
	digitalWrite(_DDSpinData, LOW);
	
}

void AD9850::reset()
{
	//reset sequence is:
	// CLOCK & LOAD = LOW
	//  Pulse RESET high for a few uS (use 5 uS here)
	//  Pulse CLOCK high for a few uS (use 5 uS here)
	//  Set DATA to ZERO and pulse LOAD for a few uS (use 5 uS here)
	
    digitalWrite(_DDSpinClock, LOW);
    digitalWrite(_DDSpinLoad, LOW);

#if defined(IS_AD9851)	// The AD9851 has a tendency to put himself in Factory Test mode, so we need to flush out the buffer...
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
	
	digitalWrite (_DDSpinLoad, HIGH); 
	delay(5);
	digitalWrite (_DDSpinLoad, LOW);
#endif
	
	digitalWrite(_DDSpinReset, LOW);
	delay(5);
	digitalWrite(_DDSpinReset, HIGH);  // Pulse RESET to Reset (clever it is)
	delay(5);
	digitalWrite(_DDSpinReset, LOW);
	delay(5);
	
	digitalWrite(_DDSpinClock, LOW);
	delay(5);
	digitalWrite(_DDSpinClock, HIGH);  // Pulse CLOCK to tell the chip I must read the data
	delay(5);
	digitalWrite(_DDSpinClock, LOW);
	delay(5);
	digitalWrite(_DDSpinData, LOW);    // Make sure DATA pin is LOW (this I don't know why but I keep it)
	
	digitalWrite(_DDSpinLoad, LOW);
	delay(5);
	digitalWrite(_DDSpinLoad, HIGH);   // Pulse LOAD to put the chip in Serial mode
	delay(5);
	digitalWrite(_DDSpinLoad, LOW);

	// Chip is RESET now (let's hope so)
}

void AD9850::SetFrequency(unsigned long frequency, int shift, boolean powerdown)
{
	unsigned long tuning_word = (((frequency * 4294967296) / DDS_CLOCK) + (((shift * 4294967296) / DDS_CLOCK) / 100));	// The shift is in 1/100 of Hertz
	
	digitalWrite (_DDSpinLoad, LOW); 
	
#if defined(IS_AD9851)	
	if (powerdown) {
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, B00000100);	// If powerdown is true then send PowerDown command
	} else {
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 8);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 16);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 24);
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, B00000001);	// We need the 6x clock multiplier
	};
#else
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 8);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 16);
	shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 24);

	if (powerdown)
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, B00000100);	// If powerdown is true then send PowerDown command
	else
		shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
#endif
	digitalWrite (_DDSpinLoad, HIGH);	// We tell the chip that we are done with sending the 40 bits word and it can be read
}
