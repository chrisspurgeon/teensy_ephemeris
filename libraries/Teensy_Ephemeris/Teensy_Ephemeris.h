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
 *  Member 'dec' holds the planetary body's declination.
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
    @param  body - Object that holds information about the planet, such as RA and declination.
    @param  time - Object that holds the time of the observation, time-based
                   calculations, such as the Julian date.
    @param  location - Object that holds the observer's latitude and longitude.
    @param  orbitalElements - Object holding the orbital parameters for a given planet. Not
    used for the Moon.
*/
/**************************************************************************/
    class Teensy_Ephemeris {


/**************************************************************************/
/*!
    Planet position stuff is in Planets.h and Planets.cpp

*/
/**************************************************************************/

#include "Planets.h"

        public:
        /// Create a new Teensy_Ephemeris instance
            Teensy_Ephemeris();
            planetbody body;/**< holds information about the planet.*/
            observertime time;/**< holds information about the observation time.*/
            observerLocation location;/**< holds the observer's latitude and longitude.*/
            planetData orbitalElements;/**< holds the orbital parameters for a planet.*/







// Debugging functions. Turn debugging on and off, and get the debugging status.
// Debugging is off by default.

            bool debug = false;/**< debugging setting of the instance. Initially set to false.*/

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


/**************************************************************************/
/*!
    @brief  Gets current debugging state. NOTE: This doesn't return a value.
    Instead it writes a message to Serial output, indicating whether debugging
    is on or off.
*/
/**************************************************************************/
            void getDebugging();






// Utility math and geometry functions

/*!
    @brief Returns an angle between 0 and 360.
    @param angle
            The angle in degrees.
    @return The angle, in degrees, between 0.0 and 360.0.

*/
            double rev(double angle);


/*!
    @brief Returns the sine of an angle.
    @param angle
            The angle, in degrees.
    @return Sine of the angle.

*/
            double sind(double angle);


/*!
    @brief Returns the cosine of an angle.
    @param angle
           The angle, in degrees.
    @return Cosine of the angle.
*/
            double cosd(double angle);


/*!
    @brief Returns the tangent of an angle.
    @param angle
           angle, in degrees.
    @return Tangent of the angle.
*/
            double tand(double angle);

/*!
    @brief Returns arcsine of an angle, in degrees.
    @param c
           sine value to be converted.
    @return The corresponding angle, in degrees.

*/
            double asind(double c);

/*!
    @brief Returns arccosine of an angle, in degrees.
    @param c
           cosine value to be converted.
    @return The corresponding angle, in degrees.

*/
            double acosd(double c);

/*!
    @brief Returns arctangent of two parameters.
    @param y
           y coordinate.
    @param x
           x coordinate.
    @return The tangent of the coordinates.

*/
            double atan2d(double y, double x);









// Time related functions


/**************************************************************************/
/*!
    @brief  Stores the components of the specified in the Teensy_Ephemeris object.
            Assumes UTC time. When debugging is on, the stored values will be output via the Serial buffer.
    @param  year
            The year.
    @param  month
            The numerical of the month (January = 1, December = 12).
    @param  day
            The day of the month.
    @param  hours
            The hours.
    @param  minutes
            The minutes.
    @param  seconds
            The seconds.
*/
/**************************************************************************/
            void setTime(int year, int month, int day, int hours, int minutes, int seconds);

/*!
    @brief Returns the stored year.
    @return The stored year.
*/
            int getYear();

/*!
    @brief Returns the stored month.
    @return The stored month.
*/
            int getMonth();

/*!
    @brief Returns the stored day.
    @return The stored day.
*/
            int getDay();

/*!
    @brief Returns the stored hour.
    @return The stored hour.
*/
            int getHours();

/*!
    @brief Returns the stored minutes.
    @return The stored minutes.
*/
            int getMinutes();

/*!
    @brief Returns the stored seconds.
    @return The stored seconds.
*/
            int getSeconds();

/**************************************************************************/
/*!
    @brief  Calculates the Julian day number. Assumes UTC time.
    @param  year
            The year.
    @param  month
            The numerical of the month (January = 1, December = 12).
    @param  day
            The day of the month.
    @param  hours
            The hours. Partial hours allowed.
    @return The Julian day number
*/
/**************************************************************************/
            double getDayNumber(int year, int month, int day, double hours);

/*!
    @brief Calculates the Julian date, using the stored time values. Stores the value in the planet object.
*/
            void setJulianDate();

/*!
    @brief Returns the Julian date.
    @return The Julian dates.
*/
            double getJulianDate();

/**************************************************************************/
/*!
    @brief  Calculates the Julian date. Assumes UTC time.
    @param  year
            The year.
    @param  month
            The numerical of the month (January = 1, December = 12).
    @param  day
            The day of the month.
    @param  hours
            The hours.
    @param  minutes
            The minutes.
    @param  seconds
            The seconds.
    @return The Julian date.
*/
/**************************************************************************/
            double determineJulianDate(int year, int month, int day, int hours, int minutes, int seconds);

/**************************************************************************/
/*!
    @brief  Calculates the local siderial time and stores the result in the planet object.
    @param  year
            The year.
    @param  month
            The numerical of the month (January = 1, December = 12).
    @param  day
            The day of the month.
    @param  hours
            The hours.
    @param  longitude
            The longitude.
*/
/**************************************************************************/
            void setLocalSiderialTime(int year, int month, int day, double hours, double longitude);

/**************************************************************************/
/*!
    @brief  Calculates the local siderial time using the stored time and longitude. Stores the result in the planet object.
*/
/**************************************************************************/
            void setLocalSiderialTime();

/*!
    @brief Returns the stored local siderial time.
    @return The local siderial time.
*/
            double getLocalSiderialTime();









// Observer location related functions



/**************************************************************************/
/*!
    @brief  Stores the location.
    @param  latitude
            The latitude.
    @param  longitude
            The longitude. Eastern hemisphere values are positive, western values are negative.
*/
/**************************************************************************/
            void setLocation(double latitude, double longitude);

/*!
    @brief Returns the stored latitude.
    @return The latitude.
*/
            double getLatitude();

/*!
    @brief Returns the stored longitude.
    @return The longitude.
*/
            double getLongitude();

/**************************************************************************/
/*!
    @brief  Stores the latitude.
    @param  latitude
            The latitude.
*/
/**************************************************************************/
            void setLatitude(double latitude);

/**************************************************************************/
/*!
    @brief  Stores the longitude.
    @param  longitude
            The longitude. Eastern hemisphere values are positive, western values are negative.
*/
/**************************************************************************/
            void setLongitude(double longitude);









// Functions to calculate planetary body's position in space, and location relative to the observer




/**************************************************************************/
/*!
    @brief  Loads the orbital parameters into the planet object.
    @param  thePlanet
            The planet name. Must be one of the values in the "planets" enum.
*/
/**************************************************************************/

            void setOrbitalElements(String thePlanet);


/**************************************************************************/
/*!
    @brief  Sets the right ascention.
    @param  ra
            The right ascention, in degrees.
*/
/**************************************************************************/
            void setRA(double ra);

/**************************************************************************/
/*!
    @brief  Sets the declination.
    @param  dec
            The declination, in degrees.
*/
/**************************************************************************/
            void setDec(double dec);

/**************************************************************************/
/*!
    @brief  Gets the right ascention.
    @return The right ascention, in degrees.
*/
/**************************************************************************/
            double getRA();

/**************************************************************************/
/*!
    @brief  Gets the declination.
    @return The declination, in degrees.
*/
/**************************************************************************/
            double getDec();

/**************************************************************************/
/*!
    @brief  Gets the altitude of the object above the horizon.
    @return The altitude above the horizon, in degrees.
*/
/**************************************************************************/
            double getAltitude();

/**************************************************************************/
/*!
    @brief  Gets the bearing of the object.
    @return The bearing of the object. Straight north is 0.0, south is 180.0, etc.

    NOTE: This bearing is based on true north. If you are using a magnetic
    compass in conjunction with this bearing, make sure to take magnetic
    declination into account.
*/
/**************************************************************************/
            double getAzimuth();


/**************************************************************************/
/*!
    @brief  Calculates the position of an object in the sky.

    To do the calculation the time and observer location needs to be set. Make
    sure to do that if you haven't already. The calculation determines the
    celestial object's altitude in the sky and bearing from the observation position.

    Those values can then be retrieved with the getAltitude() and getAzimuth()
    functions.

    If debugging is on, the function will output the intermediate calculations
    via the Serial buffer.
*/
/**************************************************************************/
            void calculateAltitudeAndAzimuth();




            // Functions to assign a name to the instance



/**************************************************************************/
/*!
    @brief  Sets the object's name.
            The name is not used in any other functions, it's purely a convenience.
    @param  planetName
            The object's name.
*/
/**************************************************************************/
            void setName(String);


/**************************************************************************/
/*!
    @brief  Retrieves the object's name.
    @return  The object's name.
*/
/**************************************************************************/
            String getName();





/**************************************************************************/
/*!
    Moon position function is in Moon.h and Moon.cpp

*/
/**************************************************************************/

#include "Moon.h"



        private:
            // int _pin;
    };

#endif
