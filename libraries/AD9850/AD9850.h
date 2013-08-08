/*
 AD9850.h - Library for adding simple AD9850/AD9851 control capabilities on MSP430 and various micro-controller
 
 Copyright 2012-2013 Yannick DEVOS under GPL 3.0 license
 Any commercial use or inclusion in a kit is subject to author approval

 ====
 Revision history :
 v1.00    2012-12-16
 First release
 v1.10    2013-01-30
 Added AD9851 support
 v1.20	  2013-03-13
 Added shift in 1/100 of Hz for better accuracy in WSPR-15 mode
 
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

 
 
 ///////////////////////////////// How to use the lib
 
 * In the AD9850.c file, change the #define parameters (chip version and Reference Clock)

 * Create an instance of the object with the pin for CLOCK, LOAD, DATA and RESET
 
 AD9850 myDDS (P1_5, P2_0, P2_1, P2_2,);	 Example for LaunchPad using an AD9850
 
 * Initialize the AD9850/9851 and do a reset
 
 myDDS.begin();
 myDDS.reset();
 
 */

// Core library
#if defined (__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) // Arduino specific
#include "WProgram.h" // #include "Arduino.h" for Arduino 1.0
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) // chipKIT specific 
#include "WProgram.h"
#elif defined(__AVR_ATmega644P__) // Wiring specific
#include "Wiring.h"
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
#include "Energia.h"
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
#include "WProgram.h"	
#endif

// ensure this library description is only included once
#ifndef AD9850_h
#define AD9850_h

// library interface description
class AD9850
{
	// user-accessible "public" interface
public:
	AD9850(uint8_t pinClock, uint8_t pinLoad, uint8_t pinData, uint8_t pinReset);
	void begin();
	void reset();
	void SetFrequency(unsigned long frequency, int shift, boolean powerdown);	// Set the frequency and PowerDown command if needed
	// A few private methods
private:
};

#endif