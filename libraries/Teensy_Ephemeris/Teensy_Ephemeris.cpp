/*
  Teensy_Ephemeris.cpp - Library for doing astronomical calculations.

  REQUIRES Teensy or other Arduino-compatable microprocessor with true "double" datatype.
  Created by Chris Spurgeon
  https://github.com/chrisspurgeon/teensy_ephemeris

*/

#include "Arduino.h"
#include "Teensy_Ephemeris.h"

Teensy_Ephemeris::Teensy_Ephemeris() {
}

double Teensy_Ephemeris::getJulianDate(int year, int month, int day, double hours) {

    // in JavaScript getJulianDate(1776,7,4,13) returns 2369914.0416666665

    double result = 0.0000000000;
    result = ((367.0 * year) 
           - floor(7.00 * (year + floor(( month + 9.00 ) / 12.00)) / 4.00)
           + floor((275.0 * month) / 9.00) 
           + day 
           - 730530.00 
           + (hours / 24.00))
           + 2451543.50;
    
    return result;

}
