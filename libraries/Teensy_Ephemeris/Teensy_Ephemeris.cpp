/*
  Teensy_Ephemeris.cpp - Library for doing astronomical calculations.

  REQUIRES Teensy or other Arduino-compatable microprocessor with true "double" datatype.
  Created by Chris Spurgeon
  https://github.com/chrisspurgeon/teensy_ephemeris

*/

#include "Arduino.h"
#include "Teensy_Ephemeris.h"
#include <math.h>

Teensy_Ephemeris::Teensy_Ephemeris() {
}


int Teensy_Ephemeris::foocheck() {
  return fooholder.var1 + fooholder.var2;
}




double Teensy_Ephemeris::getDayNumber(int year, int month, int day, double hours) {

    double result = 0.0000000000;
    result = ((367.0 * year) 
           - floor(7.00 * (year + floor(( month + 9.00 ) / 12.00)) / 4.00)
           + floor((275.0 * month) / 9.00) 
           + day 
           - 730530.00 
           + (hours / 24.00));
    
    return result;

}


double Teensy_Ephemeris::getJulianDate(int year, int month, int day, int hours, int minutes, int seconds) {
  // julian date for "year":2020,"month":5,"day":29,"hours":14,"minutes":47,"seconds":54  should = 2458999.4082638887

  double result = 0.0000000000;

  // First, calculate the Julian day...
  int _year = year;
  int _month = month;
  if (_month < 3) {
    _month += 12;
    _year -= 1;
  }
  double a = floor(_year / 100.00);
  double b = 2 - a + floor(a / 4.00);
  result = floor( 365.25 * ( _year + 4716)) + floor(30.6001 * (_month + 1)) + day + b -1524.5;

  // Now deal with hours, minutes and seconds
    result += (hours + ((minutes) / 60.0) + (seconds / 3600.0)) / 24.0;
    return result;
}

// Compute local siderial time in degrees
// year, month, day and hours are the Greenwich date and time
// longitude is the observers longitude
double Teensy_Ephemeris::getLocalSiderialTime(int year, int month, int day, double hours, double longitude) {
    double result = 0.0000;
    double d = 0.0;
    double lst = 0.0;

    d = getDayNumber(year, month, day, hours);
    lst = (98.9818 + 0.985647352 * d + hours *15 + longitude);
    result = lst / 15.0;  //TODO rev function
    return result;
//  var d=dayno(year,month,day,hours);
//  var lst=(98.9818+0.985647352*d+hours*15+lon);
//  return rev(lst)/15;

}