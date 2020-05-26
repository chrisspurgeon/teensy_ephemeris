/*
  Teensy_Ephemeris.h - Library for doing astronomical calculations.

  REQUIRES Teensy or other Arduino-compatable microprocessor with true "double" datatype.
  Created by Chris Spurgeon
  https://github.com/chrisspurgeon/teensy_ephemeris

*/

#ifndef Teensy_Ephemeris_H
#define Teensy_Ephemeris_H

    #include "Arduino.h"

    class Teensy_Ephemeris {
        public:
            Teensy_Ephemeris();
            double getJulianDate(int year, int month, int day, double hours);
            // void dot();
        private:
            // int _pin;
    };

#endif
