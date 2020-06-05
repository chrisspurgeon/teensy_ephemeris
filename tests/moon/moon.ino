#include <Teensy_Ephemeris.h>


// Let's create a new Teensy_Ephemeris object
// to hold our location and time, and the calculations
// we'll generate. Since we're going to do some calculations
// to determine the position of the moon in the sky, we've named this
// variable "moon".

Teensy_Ephemeris moon;

void setup() {

  Serial.begin(9600);

// uncomment this line to output debugging information when
// values are changed or calculated.
//  moon.setDebugging(true);

// Let's look at the moon's position on December 25th, 2020,
// at 5:15:42. (The time and date are UTC, not local time).
  moon.setTime(2020,12,25,5,15,42);

// Let's do our calculations assuming we're going to be looking at
// the moon while at Fenway Park in Boston, MA, USA.
// (latitude: 42.34625, longitude: -71.09775)
  moon.setLocation(42.34625, -71.09775);

// Now go ahead and calculate where the moon will be in the sky at that time
// and location.
  moon.calculateMoonPosition();

// Finally, let's output the altitude (the angle between the moon and the horizon).
// An altitude of zero means the moon is on the horizon, an altitude of 90 means it's
// directly overhead.),
  Serial.println(moon.getAltitude(),5);

// And output the azimuth(which direction to face to see the moon. 0 is north, 90 is east, etc.).
  Serial.println(moon.getAzimuth(),5);

}

void loop() {
  // put your main code here, to run repeatedly:

}
