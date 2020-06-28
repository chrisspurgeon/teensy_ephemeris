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
#include "Teensy_Ephemeris.h"

/** @enum planet
 * @brief enumeration used to map specific planets to their position in the PlanetsData array.
 */

enum planet {MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE};

void getPlanetOffset(String thePlanet);