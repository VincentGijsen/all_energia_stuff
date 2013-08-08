/*
 sRTCsec.h - Library for adding simple RTC capabilities using MSP430 hardware
 Reduced precision for less CPU usage
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
#include <sRTCsec.h>
#include <legacymsp430.h>

// Constructor /////////////////////////////////////////////////////////////////

RealTimeClockSec::RealTimeClockSec(void)
{
	
};

// Methods /////////////////////////////////////////////////////////////////

void RealTimeClockSec::begin(void) {
	
	DCOCTL = CALDCO_16MHZ;              // Set DCO for 16MHz using
	BCSCTL1 = CALBC1_16MHZ;             // calibration registers
	
	BCSCTL1 = DIVA_3;					// Clock = ACLK / 8
	BCSCTL3 |= (LFXT1S_0 | XCAP_3);     // Internal 12.5pF cap for 32KHz crystal
	
	TA1CCTL0 = CCIE;					//  CCR0 interupt activated
	TA1CCR0 = 4096-1;					// 4096 ticks of 32KHz XTal = 1 second => CCR0 counts N+1
	TA1CTL = TASSEL_1 | ID_3 | MC_1;	// Clock for TIMER 1 = ACLK, By 8 division, up front

	RTC_sec = 0;
	RTC_min = 0;
	RTC_hr = 0;
	
};

RealTimeClockSec& RealTimeClockSec::operator++() {	// Overload ++ operator for writing convenience (Prefix Variant)
	Inc_sec();	// This just call Inc_sec
	return *this;
};

RealTimeClockSec& RealTimeClockSec::operator++(int) {	// PostFix variant
	RealTimeClockSec tmp(*this);
	++(*this);
	return tmp;
};

void RealTimeClockSec::Inc_sec(void) {
	RTC_sec = RTC_sec + 1;		      // Update seconds
	if (RTC_sec == 60) {
		RTC_sec=0;
		Inc_min();
	};
};

void RealTimeClockSec::Inc_min(void) {
	RTC_min = RTC_min + 1;		      // Update minutes
	if (RTC_min == 60) {
		RTC_min=0;
		Inc_hr();
	};
};

void RealTimeClockSec::Inc_hr(void) {
	RTC_hr = RTC_hr + 1;		      // Update hours
	if (RTC_hr == 24) {
		RTC_hr=0;
	};
};

void RealTimeClockSec::Set_Time(char hrs=0, char mins=0, char secs=0) {
	if ((hrs>=0 && hrs <24) && (mins>=0 && mins<60) && (secs>=0 && secs<60)) {
		RTC_hr = hrs;	// Set time to values given in parameters
		RTC_min = mins;
		RTC_sec = secs;
	};
};
