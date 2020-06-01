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


double Teensy_Ephemeris::determineJulianDate(int year, int month, int day, int hours, int minutes, int seconds) {
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


void Teensy_Ephemeris::setTime(int year, int month, int day, int hours, int minutes, int seconds) {
  time.year = year;
  time.month = month;
  time.day = day;
  time.hours = hours;
  time.minutes = minutes;
  time.seconds = seconds;
}

void Teensy_Ephemeris::setJulianDate() {
  time.JulianDate = determineJulianDate(time.year, time.month, time.day, time.hours, time.minutes, time.seconds);
}

double Teensy_Ephemeris::getJulianDate() {
  return time.JulianDate;
}
int Teensy_Ephemeris::getYear() {
  return time.year;
}

int Teensy_Ephemeris::getMonth() {
  return time.month;
}

int Teensy_Ephemeris::getDay() {
  return time.day;
}

int Teensy_Ephemeris::getHours() {
  return time.hours;
}

int Teensy_Ephemeris::getMinutes() {
  return time.minutes;
}

int Teensy_Ephemeris::getSeconds() {
  return time.seconds;
}

void Teensy_Ephemeris::setName(String planetName) {
  body.name = String(planetName);
}

String Teensy_Ephemeris::getName() {
  return body.name;
}

double Teensy_Ephemeris::calculateMoonPosition() {
  setJulianDate();
  double T = 0.000L;
  double T2 = 0.000L;
  double T3 = 0.000L;
  double T4 = 0.000L;
  double Tshifted = 0.000L;
  double T2shifted = 0.00L;
  double T3shifted = 0.00L;
  double T4shifted = 0.00L;
  Tshifted = (getJulianDate() - 2451545.0) / 365.250; // increase by 100 to stop rounding errors.
  T = Tshifted / 100.00;
  T2shifted = Tshifted * Tshifted;
  T2 = T2shifted / 10000.00;
  T3shifted = Tshifted * Tshifted * Tshifted;
  T3 = T3shifted / 1000000.00;
  T4shifted = Tshifted * Tshifted * Tshifted * Tshifted;
  T4 = T4shifted / 100000000.00;

  // Moons mean longitude L'
  double LP = 218.3164477 + 481267.88123421 * T -0.0015786 * T2 + T3 / 538841.0 - T4 / 65194000.0;

  // Moons mean elongation Meeus second edition
  double D = 297.8501921 + 445267.1114034 * T - 0.0018819 * T2 + T3 / 545868.0 - T4 / 113065000.0;

  // Moons mean anomaly M' Meeus second edition
  double MP = 134.9633964 + 477198.8675055 * T + 0.0087414 * T2 + T3 / 69699.0 - T4 / 14712000.0;

  // Moons argument of latitude
  double F = 93.2720950 + 483202.0175233 * T - 0.0036539 * T2 - T3 / 3526000.0 + T4 / 863310000.0;

  // Suns mean anomaly
  double M = 357.5291092 + 35999.0502909 * T - 0.0001536 * T2 + T3 / 24490000.0;

  double A1 = 119.75 + 131.849 * T;
  double A2 = 53.09 + 479264.290 * T;
  double A3 = 313.45 + 481266.484 * T;
  double E = 1.0 - 0.002516 * T - 0.0000074 * T2;
  double E2 = E * E;

  return E2;

}