/*!
 * @file Moon.h
 *
 * This is part of Teensy_Ephemeris, a library for calculating
 * positions of the sun, moon, and planets. It is designed to work
 * with the Teensy microcontrollers (https://www.pjrc.com/teensy), 
 * starting with version 4.0.
 *
 * GNU General Public License (GPL) version 3. License details at https://www.gnu.org/licenses/gpl-3.0.html
 *
 */


/**************************************************************************/
/*!
    @brief  Calculates the position of the moon, given a location and time.

    To do the calculation the time and observer location needs to be set. Make
    sure to do that if you haven't already. The calculation determines the
    moon's altitude in the sky and bearing from the observation position.

    Those values can then be retrieved with the getAltitude() and getAzimuth()
    functions.

    If debugging is on, the function will output the intermediate calculations
    via the Serial buffer.
*/
/**************************************************************************/
    void calculateMoonPosition();
