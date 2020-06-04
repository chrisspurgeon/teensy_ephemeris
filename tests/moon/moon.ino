#include <Teensy_Ephemeris.h>

Teensy_Ephemeris moon;
void setup() {

  Serial.begin(9600);

  moon.setDebugging(true);

  moon.setName("themoon");

  moon.setTime(2020,6,1,1,51,24);
  moon.setJulianDate();

  moon.setLocation(42.4242, -155.3434);
  Serial.println(moon.getLongitude());
  Serial.println(moon.getLatitude());
  Serial.println(moon.getAltitude());

  moon.setLocation(-66.66,6.66666,333.3);
  Serial.println(moon.getLongitude());
  Serial.println(moon.getLatitude());
  Serial.println(moon.getAltitude());

  moon.setLocation(-666.66, 6000000.66666);
  Serial.println(moon.getLongitude());
  Serial.println(moon.getLatitude());
  Serial.println(moon.getAltitude());

  double foo = moon.calculateMoonPosition();
  Serial.println(foo,15 );




}

void loop() {
  // put your main code here, to run repeatedly:

}
