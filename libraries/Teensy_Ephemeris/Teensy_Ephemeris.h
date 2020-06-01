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

    struct planetbody {
        String name;
        long    RA;
        long    dec;
        long    altitude;
        long    azimuth;
    };

    struct planettime {
        int year;
        int month;
        int day;
        int hours;
        int minutes;
        int seconds;
        double JulianDate;
        double localSiderialTime;
    };

    class Teensy_Ephemeris {

        public:
            Teensy_Ephemeris();
            foo fooholder;
            planetbody body;
            planettime time;
            bool debug = false;
            void setDebugging(bool _debug);
            void getDebugging();
            double rev(double angle);
            double sind(double angle);
            double cosd(double angle);
            double tand(double angle);
            double asind(double c);
            double acosd(double c);
            double atan2d(double y, double x);
            double getDayNumber(int year, int month, int day, double hours);
            double determineJulianDate(int year, int month, int day, int hours, int minutes, int seconds);
            double getLocalSiderialTime(int year, int month, int day, double hours,double longitude);
            int foocheck();
            void setTime(int year, int month, int day, int hours, int minutes, int seconds);
            void setJulianDate();
            double getJulianDate();
            int getYear();
            int getMonth();
            int getDay();
            int getHours();
            int getMinutes();
            int getSeconds();
            double calculateMoonPosition();
            void setName(String);
            String getName();
        private:
            // int _pin;
    };

#endif
