/*
 sRTCsec.h - Library for adding simple RTC capabilities using MSP430 hardware
				Reduced precision for less CPU usage
 By Yannick DEVOS (XV4Y) - 2012-2013
 Any commercial use or inclusion in a kit is subject to author approval
 
 ====
 Revision history :
 v1.00    2012-05-22
 First release
 v1.01    2012-12-17
 Minor cosmetic changes
 v1.02    2012-12-18
 Strucutral changes to improve code cleaness
 v1.03    2012-12-21
 Settings in constructor to override default Energia settings, work with Energia 009
 v1.04    2013-01-08
 Moved settings to begin(), corrected bug related to Energia 009 => Thanks Grahamf72 from 43oh forums
 
 
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
 
 * Create an instance of the object
 
 RealTimeClockSec myClock;
 
 * Do low-level Timer and Clock setup yourself or call begin();
 
 myClock.begin();
 
 * In order to have this RTC library working you should add this code to the end of your main program :
 
 interrupt(TIMER1_A0_VECTOR) Tic_Tac(void) {
 myClock++;		      // Update secondes
 };
 
 * Enjoy the clock reading the RTC_sec, RTC_min, RTC_hr variables
 
 */
// ensure this library description is only included once
#ifndef RTCsec_h
#define RTCsec_h

// library interface description
class RealTimeClockSec
{
	// user-accessible "public" interface
public:
	RealTimeClockSec(void);
	void begin(void);
	void Set_Time(char hr, char mins, char secs);
    char RTC_sec; // This how you read the time, by reading the vars
    char RTC_min;
    char RTC_hr;
	void Inc_sec(void); // This methode should be invoked by an Interrupt call (see top of the file comment)
	RealTimeClockSec& operator++();	// Overload ++ operator for writing convenience (Prefix Variant)
	RealTimeClockSec& operator++(int);	// PostFix variant
	// A few private methods
private:
	void Inc_min(void);
	void Inc_hr(void);	
};

#endif