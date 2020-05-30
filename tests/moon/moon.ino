#include <Teensy_Ephemeris.h>

Teensy_Ephemeris moon;
void setup() {

  Serial.begin(9600);
  moon.setName("themoon");
  Serial.println(moon.getName());
  moon.setName("Venus");
  Serial.println(moon.getName());
  moon.setTime(2020,5,29,23,50,54);
  Serial.println(moon.getMinutes());
  moon.setJulianDate();
  Serial.println(moon.getJulianDate(),10);
  Serial.println(moon.time.JulianDate,10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
