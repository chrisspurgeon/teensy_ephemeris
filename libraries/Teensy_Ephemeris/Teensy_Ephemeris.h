/*!
 * @file Teensy_Ephemeris.h
 *
 * This is part of Teensy_Ephemeris, a library for calculating
 * positions of the sun, moon, and planets. It is designed to work
 * with the Teensy microcontrollers (https://www.pjrc.com/teensy), 
 * starting with version 4.0.
 *
 * GNU General Public License (GPL) version 3. License details at https://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#ifndef Teensy_Ephemeris_H
#define Teensy_Ephemeris_H

    #include "Arduino.h"

/** @struct planetbody
 *  @brief This structure holds basic info about the planetary body, and its location in space.
 *  @var planetbody::name 
 *  Member 'name' holds the user assigned name of the body.
 *  @var planetbody::RA
 *  Member 'RA' holds the planetary body's right ascension.
 *  @var planetbody::dec 
 *  Member 'de' holds the planetary body's declination.
 *  @var planetbody::altitude 
 *  Member 'altitude' holds the planetary body's altitude in the sky in degrees above the horizon,
 *  at the observer's location and observation time. Calculating it requres that observertime and observerLocation be set first.
 *  @var planetbody::azimuth 
 *  Member 'azimuth' holds the planetary body's direction from the observer at the observer's location 
 *  and observation time. Calculating it requres that observertime and observerLocation be set first. 
 *  NOTE: This is true direction, not compass direction. To convert true direction to
 *  a magnetic compass heading, see https://en.wikipedia.org/wiki/TVMDC .
 */
    struct planetbody {
        String    name;
        double    RA;
        double    dec;
        double    altitude;
        double    azimuth;
    };

/** @struct observertime
 *  @brief This structure holds the time to be used for all position calculations. 
 *  NOTE: Time is UTC, not local observer time.
 *  @var observertime::year 
 *  Member 'year' holds the year of the observation time.
 *  @var observertime::month 
 *  Member 'month' holds the month of the observation time.
 *  @var observertime::day 
 *  Member 'day' holds the day of the month of the observation time.
 *  @var observertime::hours 
 *  Member 'hours' holds the hour of the observation time.
 *  @var observertime::minutes 
 *  Member 'minutes' holds the minute of the observation time.
 *  @var observertime::seconds 
 *  Member 'seconds' holds the seconds of the observation time.
 *  @var observertime::JulianDate 
 *  Member 'JulianDate' holds the calculated Julian date of the observation.
 *  @var observertime::localSiderialTime 
 *  Member 'localSiderialTime' holds the local siderial time of the observation.
 *  Calculating it requires that an observer location has been set.
 */
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

/** @struct observerLocation
 *  @brief This structure holds the observer's latitude and longitude
 *  @var observerLocation::latitude 
 *  Member 'latitude' holds the observer's latitude
 *  @var observerLocation::longitude 
 *  Member 'longitude' holds the observer's longitude
 */
    struct observerLocation {
        double latitude = 34.225;
        double longitude = -118.236944;
    };


/**************************************************************************/
/*! 
    @brief  Class that stores the information about the planetary body.
*/
/**************************************************************************/
    class Teensy_Ephemeris {

        public:
            Teensy_Ephemeris();
            planetbody body;
            observertime time;
            observerLocation location;

            // Debugging functions. Turn debugging on and off, and get the debugging status.
            // Debugging is off by default.

            bool debug = false;

/**************************************************************************/
/*!
    @brief  Toggles debugging on and off.
            When debugging is on, calculated values (including intermediary values 
            created during calculation) are outputted via the Serial buffer.
    @param    _debug
              Boolean true/false value indicating whether debugging should be on or off.
*/
/**************************************************************************/
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
