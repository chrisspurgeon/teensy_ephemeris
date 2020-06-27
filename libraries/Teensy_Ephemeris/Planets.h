/*!
 * @file Planets.h
 *
 * This is part of Teensy_Ephemeris, a library for calculating
 * positions of the sun, moon, and planets. It is designed to work
 * with the Teensy microcontrollers (https://www.pjrc.com/teensy), 
 * starting with version 4.0.
 *
 * GNU General Public License (GPL) version 3. License details at https://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#include "Arduino.h"


/** @struct planetData
 *  @brief This structure holds the orbital elements for an individual planet.
 *  @var planetData::name
 *  The planet name, in all caps (e.g. "NEPTUNE").
 *  @var planetData::element
 *  Two-dimensional array holding 24 orbital elements for the planet.
 */
struct planetData {
    String name;
    double element[6][4];
};

/** @struct PlanetsData
 *  @brief This structure contains an array of objects containing the unique orbital parameters for 
 *  the eight planets (sorry Pluto).
 *  @var PlanetsData::planet
 *  Orbital parameters for an individual planet.
 */
struct PlanetsData {
    planetData planet[8];
};


/** @enum planet
 * @brief enumeration used to map specific planets to their position in the PlanetsData array.
 */

enum planet {MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE};