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


struct planetData {
    String name;
    double element[4];
};

struct PlanetsData {
    planetData planet[8];
};
