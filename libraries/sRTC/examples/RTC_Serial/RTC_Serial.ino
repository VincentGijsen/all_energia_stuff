/*
 sRTC.h - Library for adding simple RTC capabilities using MSP430 hardware
 By Yannick DEVOS (XV4Y) - 2012-2013
 Any commercial use or inclusion in a kit is subject to author approval
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You can download a copy of the GNU General Public License at <http://www.gnu.org/licenses/>
 
============================================
This example only compiles on MSP430G2553
Compiling on other hardware should be possible but need to adapt the timer settings
 
 */

#include <sRTC.h>
#include <legacymsp430.h>

RealTimeClock myClock;

  int ledState = LOW;
  
void setup() {
  pinMode(RED_LED, OUTPUT);

  // This is to close the serial output so you are able to upload a new sketch to the LaunchPad
  // Push the button of the LaunchPad and Serial will be closed
  pinMode(P1_3, INPUT_PULLUP),
  attachInterrupt(P1_3,fin,LOW);

  Serial.begin(9600);

  myClock.begin();

};

// The LED1 will blink each exact second and the time will be printed to the serial port
void loop() {
  if ((myClock.RTC_sec % 2)==0 && ledState== HIGH) {
  ledState = LOW;
  Serial.print(myClock.RTC_min, DEC);
  Serial.print(":");
  Serial.println(myClock.RTC_sec, DEC);
  digitalWrite(RED_LED, ledState);
  };
  
  if ((myClock.RTC_sec % 2)==1 && ledState== LOW) {
  ledState = HIGH;
  Serial.print(myClock.RTC_min, DEC);
  Serial.print(":");
  Serial.println(myClock.RTC_sec, DEC);
  digitalWrite(RED_LED, ledState);
  };

};

void fin() {
  Serial.end();
};

interrupt(TIMER1_A0_VECTOR) Tic_Tac(void) {
	myClock++;		      // Update secondes
};	

