/*!
 * @file Teensy_Ephemeris.cpp
 *
 * @mainpage Ephemeris calculations for Teensy 4.x microcontrollers
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Teensy_Ephemeris, a library for calculating
 * positions of the sun, moon, and planets. It is designed to work
 * with the Teensy microcontrollers (https://www.pjrc.com/teensy), starting with version 4.0.
 * While this code will compile and run on standard Arduino boards, such as the Arduino UNO, 
 * those boards do not have the necessary aritmetic precision for the required calculations.
 * Because of that, results obtained on boards such as the UNO may be inaccurate.
 *
 * @section dependencies Dependencies
 *
 * This library requires a Teensy board, version 4.0 or later. IT WILL NOT WORK PROPERLY
 * ON A STANDARD ARDUINO BOARD!
 *
 * @section author Author
 *
 * Written by Chris Spurgeon (chris@spurgeonworld.com)
 *
 * @section license License
 *
 * GNU General Public License (GPL) version 3. License details at https://www.gnu.org/licenses/gpl-3.0.html
 *
 */


#include "Arduino.h"
#include "Teensy_Ephemeris.h"
#include <math.h>

Teensy_Ephemeris::Teensy_Ephemeris() {
  debug = false;
}

void Teensy_Ephemeris::setDebugging(bool _debug) {
  debug = _debug;
  getDebugging();
}

void Teensy_Ephemeris::getDebugging() {
  if (debug == 1) {
    Serial.println("DEBUG: debugging is ON");
  } else {
    Serial.println("DEBUG: debugging is OFF");
  }
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

double Teensy_Ephemeris::getLocalSiderialTime() {
  return time.localSiderialTime;
}


// Compute local siderial time in degrees
// year, month, day and hours are the Greenwich date and time
// longitude is the observers longitude
void Teensy_Ephemeris::setLocalSiderialTime(int year, int month, int day, double hours, double longitude) {
  double result = 0.0000;
  double d = 0.0;
  double lst = 0.0;

  d = getDayNumber(year, month, day, hours);
  lst = (98.9818 + 0.985647352 * d + hours * 15 + longitude);
  result = lst / 15.0;
  time.localSiderialTime = result;
  if (debug) {
    Serial.print("DEBUG: setLocalSiderialTime()\n       ");
    Serial.println(time.localSiderialTime, 12);
  }
}

void Teensy_Ephemeris::setLocalSiderialTime() {
  setLocalSiderialTime(time.year, time.month, time.day, time.hours, location.longitude);
}


void Teensy_Ephemeris::setTime(int year, int month, int day, int hours, int minutes, int seconds) {
  time.year = year;
  time.month = month;
  time.day = day;
  time.hours = hours;
  time.minutes = minutes;
  time.seconds = seconds;
  if (debug) {
    Serial.println("DEBUG: setTime()");
    Serial.print("       time.year is ");
    Serial.println(time.year);
    Serial.print("       time.month is ");
    Serial.println(time.month);
    Serial.print("       time.day is ");
    Serial.println(time.day);
    Serial.print("       time.hours is ");
    Serial.println(time.hours);
    Serial.print("       time.minutes is ");
    Serial.println(time.minutes);
    Serial.print("       time.seconds is ");
    Serial.println(time.seconds);
  }
}

void Teensy_Ephemeris::setJulianDate() {
  time.JulianDate = determineJulianDate(time.year, time.month, time.day, time.hours, time.minutes, time.seconds);
  if (debug) {
    Serial.print("DEBUG: setJulianDate()\n       ");
    Serial.println(time.JulianDate, 12);
  }
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
  if (debug) {
    Serial.print("DEBUG: setName()\n       body.name is ");
    Serial.println("'" + body.name + "'");
  }
}

String Teensy_Ephemeris::getName() {
  return body.name;
}

void Teensy_Ephemeris::setLocation(double _latitude, double _longitude) {
  if (_latitude < -90.00 || _latitude > 90.00) {
    location.latitude = 0.00;
    Serial.println("WARNING: Invalid latitude. Reset to 0.00.");
  } else {
    location.latitude = _latitude;
  }
  if (_longitude > 180.0 || _longitude < -180.00) {
    location.longitude = 0.00;
    Serial.println("WARNING: Invalid longitude. Reset to 0.00.");
  } else {
    location.longitude = _longitude;
  }
  if (debug) {
    Serial.println("DEBUG: setLocation()");
    Serial.print("       Latitude: ");
    Serial.println(location.latitude, 10);
    Serial.print("       Longitude: ");
    Serial.println(location.longitude, 10);
  }
}

void Teensy_Ephemeris::setLatitude(double _latitude) {
  location.latitude = _latitude;
  if (debug) {
    Serial.print("DEBUG: setLatitude()\n       ");
    Serial.println(location.latitude, 10);
  }
}

void Teensy_Ephemeris::setLongitude(double _longitude) {
  location.longitude = _longitude;
  if (debug) {
    Serial.print("DEBUG: setLongitude()\n       ");
    Serial.println(location.longitude, 10);
  }
}

double Teensy_Ephemeris::getLongitude() {
  return location.longitude;
}

double Teensy_Ephemeris::getLatitude() {
  return location.latitude;
}

double Teensy_Ephemeris::getRA() {
  return body.RA;
}

double Teensy_Ephemeris::getDec() {
  return body.dec;
}

double Teensy_Ephemeris::getAltitude() {
  return body.altitude;
}

double Teensy_Ephemeris::getAzimuth() {
  return body.azimuth;
}


// calculateAltitudeAndAzimuth converts ra and dec to altitude and azimuth
void Teensy_Ephemeris::calculateAltitudeAndAzimuth() {
  // First, update the local siderial time, and get the value
  setLocalSiderialTime();
  double lst = getLocalSiderialTime();
  double x = cosd(15.0 * (lst - getRA())) * cosd(getDec());
  double y = sind(15.0 * (lst - getRA())) * cosd(getDec());
  double z = sind(getDec());
  // rotate so z is the local zenith
  double xhor = x * sind(getLatitude()) - z * cosd(getLatitude());
  double yhor = y;
  double zhor = x * cosd(getLatitude()) + z * sind(getLatitude());
  double azimuth = rev(atan2d(yhor, xhor) + 180.0); // so 0 degrees is north
  double altitude = atan2d(zhor, sqrt(xhor * xhor + yhor * yhor));
  body.azimuth = azimuth;
  body.altitude = altitude;
  if (debug) {
    Serial.println("DEBUG: calculateAltitudeAndAzimuth()");
    Serial.print("       Azimuth: ");
    Serial.println(body.azimuth, 10);
    Serial.print("       Altitude: ");
    Serial.println(body.altitude, 10);
  }
}






void Teensy_Ephemeris::calculateMoonPosition() {

  unsigned char T45AD [60] = { 0, 2, 2, 0, 0, 0, 2, 2, 2, 2,
                               0, 1, 0, 2, 0, 0, 4, 0, 4, 2,
                               2, 1, 1, 2, 2, 4, 2, 0, 2, 2,
                               1, 2, 0, 0, 2, 2, 2, 4, 0, 3,
                               2, 4, 0, 2, 2, 2, 4, 0, 4, 1,
                               2, 0, 1, 3, 4, 2, 0, 1, 2, 2 };

  int T45AM [60] = {  0,  0,  0,  0,  1,  0,  0, -1,  0, -1,
                      1,  0,  1,  0,  0,  0,  0,  0,  0,  1,
                      1,  0,  1, -1,  0,  0,  0,  1,  0, -1,
                      0, -2,  1,  2, -2,  0,  0, -1,  0,  0,
                      1, -1,  2,  2,  1, -1,  0,  0, -1,  0,
                      1,  0,  1,  0,  0, -1,  2,  1,  0,  0 };

  int T45AMP [60] = { 1, -1,  0,  2,  0,  0, -2, -1,  1,  0,
                     -1,  0,  1,  0,  1,  1, -1,  3, -2, -1,
                      0, -1,  0,  1,  2,  0, -3, -2, -1, -2,
                      1,  0,  2,  0, -1,  1,  0, -1,  2, -1,
                      1, -2, -1, -1, -2,  0,  1,  4,  0, -2,
                      0,  2,  1, -2, -3,  2,  1, -1,  3, -1 };

  int T45AF [60] = {  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
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

  int T45BM [60] = { 0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
                    -1,  0,  0,  1, -1, -1, -1, 1,  0,  1,
                     0,  1,  0,  1,  1,  1,  0, 0,  0,  0,
                     0,  0,  0,  0, -1,  0,  0, 0,  0,  1,
                     1,  0, -1, -2,  0,  1,  1, 1,  1,  1,
                     0, -1,  1,  0, -1,  0,  0, 0, -1, -2 };

  int T45BMP [60] = { 0,  1, 1,  0, -1, -1,  0,  2,  1,  2,
                      0, -2, 1,  0, -1,  0, -1, -1, -1,  0,
                      0, -1, 0,  1,  1,  0,  0,  3,  0, -1,
                      1, -2, 0,  2,  1, -2,  3,  2, -3, -1,
                      0,  0, 1,  0,  1,  1,  0,  0, -2, -1,
                      1, -2, 2, -2, -1,  1,  1, -1,  0,  0 };

  int T45BF [60] = { 1,  1, -1, -1,  1, -1,  1,  1, -1, -1,
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

  if (debug) {
    Serial.println("DEBUG: calculateMoonPosition()");
  }
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

  if (debug) {
    Serial.print("       T:  ");
    Serial.println(T,12);
    Serial.print("       T2: ");
    Serial.println(T2,12);
    Serial.print("       T3: ");
    Serial.println(T3,12);
    Serial.print("       T4: ");
    Serial.println(T4,12);
    Serial.print("       LP: ");
    Serial.println(LP,12);
    Serial.print("       D:  ");
    Serial.println(D,12);
    Serial.print("       MP: ");
    Serial.println(MP,12);
    Serial.print("       F:  ");
    Serial.println(F,12);
    Serial.print("       M:  ");
    Serial.println(M,12);
    Serial.print("       A1: ");
    Serial.println(A1,12);
    Serial.print("       A2: ");
    Serial.println(A2,12);
    Serial.print("       A3: ");
    Serial.println(A3,12);
    Serial.print("       E:  ");
    Serial.println(E,12);
    Serial.print("       E2: ");
    Serial.println(E2,12);
  }

  // Sums of periodic terms from table 45.A and 45.B
  double Sl = 0.0;
  double Sr = 0.0;
  double Eterm = 0.0;
  int i;
  for (i = 0; i < 60; i++) {
    Eterm = 1.0;
    if (abs(T45AM[i]) == 1) {
      Eterm = E;
    }
    if (abs(T45AM[i]) == 2) {
      Eterm=E2;
    }
    Sl += T45AL[i] * Eterm * sind(rev(T45AD[i] * D + T45AM[i] * M + T45AMP[i] * MP + T45AF[i] * F));
    Sr += T45AR[i] * Eterm * cosd(rev(T45AD[i] * D + T45AM[i] * M + T45AMP[i] * MP + T45AF[i] * F));
  }

  double Sb = 0.0;
  for (i = 0; i < 60; i++) {
    Eterm = 1.00;
    if (abs(T45BM[i]) == 1) {
      Eterm = E;
    }
    if (abs(T45BM[i]) == 2) {
      Eterm = E2;
    }
    Sb += T45BL[i] * Eterm * sind(rev(T45BD[i] * D + T45BM[i] * M + T45BMP[i] * MP + T45BF[i] * F));
  }
  // Additional additive terms
  Sl = Sl + 3958 * sind(rev(A1)) + 1962 * sind(rev(LP - F)) + 318.0 * sind(rev(A2));
  Sb = Sb - 2235 * sind(rev(LP)) + 382 * sind(rev(A3)) + 175.0 * sind(rev(A1-F)) + 175.0 * sind(rev(A1 + F)) + 127.0 * sind(rev(LP - MP)) - 115.0 * sind(rev(LP + MP));

  if (debug) {
    Serial.print("       Sl: ");
    Serial.println(Sl,12);
    Serial.print("       Sr: ");
    Serial.println(Sr,12);
    Serial.print("       Sb: ");
    Serial.println(Sb,12);
  }

  // geocentric longitude, latitude and distance
  double mglong = rev(LP + Sl / 1000000.0);
  double mglat = rev(Sb / 1000000.0);
  if (mglat > 180.0) {
    mglat = mglat - 360.0;
  }
  double mr = round(385000.56 + Sr / 1000.0);

  // Obliquity of Ecliptic
  double obl = 23.4393 - 3.563E-7 * (time.JulianDate - 2451543.5);
  // RA and dec
  double ra = rev(atan2d(sind(mglong) * cosd(obl) - tand(mglat) * sind(obl), cosd(mglong))) / 15.0;
  double dec = rev(asind(sind(mglat) * cosd(obl) + cosd(mglat) * sind(obl) * sind(mglong)));
  if (dec > 180.0) {
    dec = dec - 360.0;
  }

  body.RA  = ra;
  body.dec = dec;

  if (debug) {
    Serial.print("       mglong: ");
    Serial.println(mglong,12);
    Serial.print("       mglat: ");
    Serial.println(mglat,12);
    Serial.print("       mr: ");
    Serial.println(mr,12);
    Serial.print("       obl: ");
    Serial.println(obl,12);
    Serial.print("       ra: ");
    Serial.println(ra,12);
    Serial.print("       dec: ");
    Serial.println(dec,12);
  }

  // phase angle
  double pa = 180.0 - D - 6.289 * sind(MP) + 2.1 * sind(M) - 1.274 * sind(2 * D - MP) - 0.658 * sind(2 * D) - 0.214 * sind(2 * MP) - 0.11 * sind(D);

  if (debug) {
    Serial.print("       pa: ");
    Serial.println(pa,12);
  }


  // // Altitude and azimuth
  // var altaz=radtoaa(ra,dec,obs);
  // return new Array(ra,dec,mr,altaz[0],altaz[1],rev(pa));

  calculateAltitudeAndAzimuth();
}
