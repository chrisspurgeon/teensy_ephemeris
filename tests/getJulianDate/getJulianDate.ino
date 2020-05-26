#include <Teensy_Ephemeris.h>

Teensy_Ephemeris TE;
void setup() {
  // put your setup code here, to run once:
  long JD = TE.getJulianDate(1776,7,4,13);

  Serial.begin(9600);
  Serial.println("HELLO");
  Serial.println(JD, 30);
  Serial.println("Goodbye");

}

void loop() {
  // put your main code here, to run repeatedly:

}
