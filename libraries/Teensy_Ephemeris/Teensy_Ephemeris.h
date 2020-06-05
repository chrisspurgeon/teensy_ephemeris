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
        double    RA;
        double    dec;
        double    altitude;
        double    azimuth;
    };

    struct observertime {
        int year;
        int month;
        int day;
        int hours;
        int minutes;
        int seconds;
        double JulianDate;
        double localSiderialTime;
    };

    struct observerLocation {
        double latitude = 34.225;
        double longitude = -118.236944;
    };

    class Teensy_Ephemeris {

        public:
            Teensy_Ephemeris();
            foo fooholder;
            planetbody body;
            observertime time;
            observerLocation location;
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
            void setLocalSiderialTime(int year, int month, int day, double hours,double longitude);
            void setLocalSiderialTime();
            double getLocalSiderialTime();
            int foocheck();
            void setTime(int year, int month, int day, int hours, int minutes, int seconds);
            void setLocation(double latitude, double longitude);
            double getLatitude();
            double getLongitude();
            void setLatitude(double latitude);
            void setLongitude(double longitude);
            void setJulianDate();
            double getJulianDate();
            void setRA(double ra);
            void setDec(double dec);
            double getRA();
            double getDec();
            double getAltitude();
            double getAzimuth();
            int getYear();
            int getMonth();
            int getDay();
            int getHours();
            int getMinutes();
            int getSeconds();
            void calculateMoonPosition();
            void calculateAltitudeAndAzimuth();
            void setName(String);
            String getName();
        private:
            // int _pin;
    };

#endif
