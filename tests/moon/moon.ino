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

  moon.setLocation(51.47722222222222, 0.00);
  Serial.println(moon.getLongitude());
  Serial.println(moon.getLatitude());

  moon.calculateMoonPosition();

}

void loop() {
  // put your main code here, to run repeatedly:

}
