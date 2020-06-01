#include <Teensy_Ephemeris.h>

Teensy_Ephemeris moon;
void setup() {

  Serial.begin(9600);

  moon.setDebugging(true);

  moon.setName("themoon");

  moon.setTime(2020,6,1,1,51,24);

  moon.setJulianDate();
  double foo = moon.calculateMoonPosition();
  Serial.println(foo,15 );
}

void loop() {
  // put your main code here, to run repeatedly:

}
