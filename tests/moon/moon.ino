#include <Teensy_Ephemeris.h>

Teensy_Ephemeris moon;
void setup() {

  Serial.begin(9600);
  moon.setName("themoon");
  Serial.println(moon.getName());
  moon.setTime(2020,6,1,1,51,24);
  Serial.println(moon.getMinutes());
  moon.setJulianDate();
  Serial.println(moon.getJulianDate(),10);
  Serial.println(moon.time.JulianDate,10);
  double foo = moon.calculateMoonPosition();
  Serial.println(foo,15);
}

void loop() {
  // put your main code here, to run repeatedly:

}
