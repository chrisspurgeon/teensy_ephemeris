/*
  Teensy_Ephemeris.h - Library for doing astronomical calculations.

  REQUIRES Teensy or other Arduino-compatable microprocessor with true "double" datatype.
  Created by Chris Spurgeon
  https://github.com/chrisspurgeon/teensy_ephemeris

*/

#ifndef Teensy_Ephemeris_H
#define Teensy_Ephemeris_H

    #include "Arduino.h"

    struct foo {
        int var1;
        int var2;
    };

    class Teensy_Ephemeris {

        public:
            Teensy_Ephemeris();
            foo fooholder;
            double getDayNumber(int year, int month, int day, double hours);
            double getJulianDate(int year, int month, int day, int hours, int miutes, int seconds);
            double getLocalSiderialTime(int year, int month, int day, double hours,double longitude);
            int foocheck();
        private:
            // int _pin;
    };

#endif
