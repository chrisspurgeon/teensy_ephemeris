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

void Teensy_Ephemeris::setOrbitalElements(String Theplanet) {

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




