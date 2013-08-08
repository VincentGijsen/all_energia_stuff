/*
 sRTC.h - Library for adding simple RTC capabilities using MSP430 hardware
 By Yannick DEVOS (XV4Y) - 2012
 Any commercial use or inclusion in a kit is subject to author approval
 
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
#include <sRTC.h>
#include <legacymsp430.h>

// Constructor /////////////////////////////////////////////////////////////////

RealTimeClock::RealTimeClock(void)
{

};

// Methods /////////////////////////////////////////////////////////////////

void RealTimeClock::begin(void) {
	
	BCSCTL1 &= ~DIVA_3;		// ACLK without divider, set it to DIVA_0
	BCSCTL3 |= XCAP_3;		// Internal 12.5pF cap for 32KHz crystal
	
	TA1CCTL0 = CCIE;             //  CCR0 interupt activated
	TA1CCR0 = 128-1;             // 4096 ticks of 32KHz XTal = 1 second, so 4 slices are 1 second => CCR0 counts N+1
	TA1CTL = TASSEL_1 | ID_0 | MC_1;  // Clock for TIMER 1 = ACLK, No division, up mode

	P2SEL |= (BIT6 | BIT7); // This is to override default Energia settings that set P2_6 and P2_7 to GPIO instead of ACLK
	BCSCTL3 = LFXT1S_0;		// Override default Energia setting sourcing ACLK from VLO, now source from XTal
	
	RTC_chunk = 0;
	RTC_sec = 0;
	RTC_min = 0;
	RTC_hr = 0;	
	
};

RealTimeClock& RealTimeClock::operator++() {	// Overload ++ operator for writing convenience (Prefix Variant)
	Inc_chunk();	// This just call Inc_chunk
	return *this;
};

RealTimeClock& RealTimeClock::operator++(int) {	// PostFix variant
	RealTimeClock tmp(*this);
	++(*this);
	return tmp;
};

void RealTimeClock::Inc_chunk(void) {
	RTC_chunk = RTC_chunk + 1;		      // Update chuncks
	if (RTC_chunk == 256) {
		RTC_chunk=0;
		Inc_sec();
	};
};

void RealTimeClock::Inc_sec(void) {
	RTC_sec = RTC_sec + 1;		      // Update seconds
	if (RTC_sec == 60) {
		RTC_sec=0;
		Inc_min();
	};
};

void RealTimeClock::Inc_min(void) {
	RTC_min = RTC_min + 1;		      // Update minutes
	if (RTC_min == 60) {
		RTC_min=0;
		Inc_hr();
	};
};

void RealTimeClock::Inc_hr(void) {
	RTC_hr = RTC_hr + 1;		      // Update hours
	if (RTC_hr == 24) {
		RTC_hr=0;
	};
};

void RealTimeClock::Set_Time(char hrs=0, char mins=0, char secs=0) {
	if ((hrs>=0 && hrs <24) && (mins>=0 && mins<60) && (secs>=0 && secs<60)) {
		RTC_hr = hrs;	// Set time to values given in parameters
		RTC_min = mins;
		RTC_sec = secs;
		RTC_chunk = 0;
	};
};
