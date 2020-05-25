
/*
    The time scale used here is a "day number" from 2000 Jan 0.0 TDT, which is the same as 1999 Dec 31.0 TDT, i.e. precisely at midnight TDT at the start of the last day of this century.
    With the modest accuracy we strive for here, one can usually disregard the difference between TDT (formerly canned ET) and UT.

    We call our day number d. It can be computed from a JD (Julian Day Number) or MJD (Modified Julian Day Number) like this:

    d  =  JD - 2451543.5  =  MJD - 51543.0

    We can also compute d directly from the calendar date like this:

    d = 367*Y - (7*(Y + ((M+9)/12)))/4 + (275*M)/9 + D - 730530

    Y is the year (all 4 digits!), M the month (1-12) and D the date.
    In this formula all divisions should be INTEGER divisions. Use "div" instead of "/" in Pascal, and "\" instead of "/" in Microsoft Basic.
    In C/C++ and FORTRAN it's sufficient to ensure that both operands to "/" are integers.

    This formula yields d as an integer, which is valid at the start (at midnight), in UT or TDT, of that calendar date.
    If you want d for some other time, add UT/24.0 (here the division is a floating-point division!) to the d obtained above.

    Example: compute d for 19 april 1990, at 0:00 UT :
    We can look up, or compute the JD for this moment, and we'll get: JD = 2448000.5 which yields d = -3543.0

    Or we can compute d directly from the calendar date:

    d = 367*1990 - (7*(1990 + ((4+9)/12)))/4 + (275*4)/9 + 19 - 730530
    d = 730330 - (7*(1990 + (13/12)))/4 + 1100/9 + 19 - 730530
    d = 730330 - (7*(1990 + 1))/4 + 122 + 19 - 730530
    d = 730330 - (7*1991)/4 + 122 + 19 - 730530
    d = 730330 - 13937/4 + 122 + 19 - 730530
    d = 730330 - 3484 + 122 + 19 - 730530  =  -3543

    This moment, 1990 april 19, 0:00 UT/TDT, will be our test date for most numerical examples below.
    d is negative since our test date, 19 april 1990, is earlier than the "point of origin" of our day number, 31 dec 1999.

*/
#include "Planet.c"


int year = 1990;
int month = 4;
int day = 19;
int d;

Planet sun;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  Serial.print("day is ");
  d = dayNumber(year, month, day);
  Serial.println(d);

  sun.longitudeOfPerihelion = 282.9404 + 4.70935E-5 * d;
  sun.eccentricity = 0.016709 - 1.151E-9 * d;
  sun.meanAnomaly = 356.0470 + 0.9856002585 * d;
  sun.meanAnomaly = rev(sun.meanAnomaly);

  
}

double rev( double x ) {
  return  x - floor(x/360.0)*360.0;
}






void loop() {
  // put your main code here, to run repeatedly:

}

int dayNumber(int year, int month, int day) {
  int d;
  d = 367*year - (7*(year + ((month+9)/12)))/4 + (275*month)/9 + day - 730530;
  return d;
 }


