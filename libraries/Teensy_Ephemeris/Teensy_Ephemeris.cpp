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

//Math and geometry functions
double Teensy_Ephemeris::rev(double angle) {
  return angle - floor( angle / 360.0 ) * 360.0;
}

double Teensy_Ephemeris::sind(double angle) {
  return sin((angle * M_PI) / 180.0 );
}

double Teensy_Ephemeris::cosd(double angle) {
  return cos((angle * M_PI) / 180.0);
}

double Teensy_Ephemeris::tand(double angle) {
  return tan((angle * M_PI) / 180.0);
}

double Teensy_Ephemeris::asind(double c) {
  return (180.0 / M_PI) * asin(c);
}

double Teensy_Ephemeris::acosd(double c) {
  return (180.0 / M_PI) * acos(c);
}

double Teensy_Ephemeris::atan2d(double y, double x) {
  return (180.0 / M_PI) * atan( y / x ) -180.0 * ( x < 0);
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

  unsigned char T45AD [60] = { 0, 2, 2, 0, 0, 0, 2, 2, 2, 2,
                               0, 1, 0, 2, 0, 0, 4, 0, 4, 2,
                               2, 1, 1, 2, 2, 4, 2, 0, 2, 2,
                               1, 2, 0, 0, 2, 2, 2, 4, 0, 3,
                               2, 4, 0, 2, 2, 2, 4, 0, 4, 1,
                               2, 0, 1, 3, 4, 2, 0, 1, 2, 2 };

  unsigned char T45AM [60] = { 0,  0,  0,  0,  1,  0,  0, -1,  0, -1,
                               1,  0,  1,  0,  0,  0,  0,  0,  0,  1,
                               1,  0,  1, -1,  0,  0,  0,  1,  0, -1,
                               0, -2,  1,  2, -2,  0,  0, -1,  0,  0,
                               1, -1,  2,  2,  1, -1,  0,  0, -1,  0,
                               1,  0,  1,  0,  0, -1,  2,  1,  0,  0 };

  unsigned char T45AMP [60] = { 1, -1,  0,  2,  0,  0, -2, -1,  1,  0,
                               -1,  0,  1,  0,  1,  1, -1,  3, -2, -1,
                                0, -1,  0,  1,  2,  0, -3, -2, -1, -2,
                                1,  0,  2,  0, -1,  1,  0, -1,  2, -1,
                                1, -2, -1, -1, -2,  0,  1,  4,  0, -2,
                                0,  2,  1, -2, -3,  2,  1, -1,  3, -1 };

  unsigned char T45AF [60] = { 0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
                               0,  0,  0, -2,  2, -2,  0,  0,  0,  0,
                               0,  0,  0,  0,  0,  0,  0,  0,  2,  0,
                               0,  0,  0,  0,  0, -2,  2,  0,  2,  0,
                               0,  0,  0,  0,  0, -2,  0,  0,  0,  0,
                              -2, -2,  0,  0,  0,  0,  0,  0,  0, -2 };

  int T45AL [60] = { 6288774, 1274027, 658314, 213618, -185116,
                     -114332,   58793,  57066,  53322,   45758,
                      -40923,  -34720, -30383,  15327,  -12528,
                       10980,   10675,  10034,   8548,   -7888,
                       -6766,   -5163,   4987,   4036,    3994,
                        3861,    3665,  -2689,  -2602,    2390,
                       -2348,    2236,  -2120,  -2069,    2048,
                       -1773,   -1595,   1215,  -1110,    -892,
                        -810,     759,   -713,   -700,     691,
                         596,     549,    537,    520,    -487,
                        -399,    -381,    351,   -340,     330,
                         327,    -323,    299,    294,       0 };

  int T45AR [60] = { -20905355, -3699111, -2955968, -569925,   48888,
                         -3149,   246158,  -152138, -170733, -204586,
                       -129620,   108743,   104755,   10321,       0,
                         79661,   -34782,   -23210,  -21636,   24208,
                         30824,    -8379,   -16675,  -12831,  -10445,
                        -11650,    14403,    -7003,       0,   10056,
                          6322,    -9884,     5751,       0,   -4950,
                          4130,        0,    -3958,       0,    3258,
                          2616,    -1897,    -2117,    2354,       0,
                             0,    -1423,    -1117,   -1571,   -1739,
                             0,    -4421,        0,       0,       0,
                             0,     1165,        0,       0,    8752 };

  // Meeus table 45B latitude of the moon

  unsigned char T45BD [60] = { 0, 0, 0, 2, 2, 2, 2, 0, 2, 0,
                               2, 2, 2, 2, 2, 2, 2, 0, 4, 0,
                               0, 0, 1, 0, 0, 0, 1, 0, 4, 4,
                               0, 4, 2, 2, 2, 2, 0, 2, 2, 2,
                               2, 4, 2, 2, 0, 2, 1, 1, 0, 2,
                               1, 2, 0, 4, 4, 1, 4, 1, 4, 2 };

  unsigned char T45BM [60] = { 0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
                              -1,  0,  0,  1, -1, -1, -1, 1,  0,  1,
                               0,  1,  0,  1,  1,  1,  0, 0,  0,  0,
                               0,  0,  0,  0, -1,  0,  0, 0,  0,  1,
                               1,  0, -1, -2,  0,  1,  1, 1,  1,  1,
                               0, -1,  1,  0, -1,  0,  0, 0, -1, -2 };

  unsigned char T45BMP [60] = { 0,  1, 1,  0, -1, -1,  0,  2,  1,  2,
                                0, -2, 1,  0, -1,  0, -1, -1, -1,  0,
                                0, -1, 0,  1,  1,  0,  0,  3,  0, -1,
                                1, -2, 0,  2,  1, -2,  3,  2, -3, -1,
                                0,  0, 1,  0,  1,  1,  0,  0, -2, -1,
                                1, -2, 2, -2, -1,  1,  1, -1,  0,  0 };

  unsigned char T45BF [60] = { 1,  1, -1, -1,  1, -1,  1,  1, -1, -1,
                              -1, -1,  1, -1,  1,  1, -1, -1, -1,  1,
                               3,  1,  1,  1, -1, -1, -1,  1, -1,  1,
                              -3,  1, -3, -1, -1,  1, -1,  1, -1,  1,
                               1,  1,  1, -1,  3, -1, -1,  1, -1, -1,
                               1, -1,  1, -1, -1, -1, -1, -1, -1,  1 };

  int T45BL [60] = { 5128122, 280602, 277693, 173237, 55413,
                       46271,  32573,  17198,   9266,  8822,
                        8216,   4324,   4200,  -3359,  2463,
                        2211,   2065,  -1870,   1828, -1794,
                       -1749,  -1565,  -1491,  -1475, -1410,
                       -1344,  -1335,   1107,   1021,   833,
                         777,    671,    607,    596,   491,
                        -451,    439,    422,    421,  -366,
                        -351,    331,    315,    302,  -283,
                        -229,    223,    223,   -220,  -220,
                        -185,    181,   -177,    176,   166,
                        -164,    132,   -119,    115,   107 };



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