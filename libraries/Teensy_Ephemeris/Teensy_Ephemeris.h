/*
  Teensy_Ephemeris.h - Library for doing astronomical calculations.

  REQUIRES Teensy or other Arduino-compatable microprocessor with true "double" datatype.
  Created by Chris Spurgeon
  https://github.com/chrisspurgeon/teensy_ephemeris

*/

#ifndef Teensy_Ephemeris_H
#define Teensy_Ephemeris_H

    #include "Arduino.h"

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
            planetbody body;
            observertime time;
            observerLocation location;

            // Debugging functions. Turn debugging on and off, and get the debugging status.
            // Debugging is off by default.
            bool debug = false;
            void setDebugging(bool _debug);
            void getDebugging();

            // Utility math and geometry functions
            double rev(double angle);
            double sind(double angle);
            double cosd(double angle);
            double tand(double angle);
            double asind(double c);
            double acosd(double c);
            double atan2d(double y, double x);

            // Time related functions
            void setTime(int year, int month, int day, int hours, int minutes, int seconds);
            int getYear();
            int getMonth();
            int getDay();
            int getHours();
            int getMinutes();
            int getSeconds();
            double getDayNumber(int year, int month, int day, double hours);
            void setJulianDate();
            double getJulianDate();
            double determineJulianDate(int year, int month, int day, int hours, int minutes, int seconds);
            void setLocalSiderialTime(int year, int month, int day, double hours,double longitude);
            void setLocalSiderialTime();
            double getLocalSiderialTime();

            // Observer location related functions
            void setLocation(double latitude, double longitude);
            double getLatitude();
            double getLongitude();
            void setLatitude(double latitude);
            void setLongitude(double longitude);

            // Functions to calculate body position in space, and location relative to the observer
            void setRA(double ra);
            void setDec(double dec);
            double getRA();
            double getDec();
            double getAltitude();
            double getAzimuth();
            void calculateMoonPosition();
            void calculateAltitudeAndAzimuth();

            // Function to assign a name to the instance
            void setName(String);
            String getName();

        private:
            // int _pin;
    };

#endif
