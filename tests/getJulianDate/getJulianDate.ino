#include <Teensy_Ephemeris.h>

Teensy_Ephemeris TE;
void setup() {

  // This should return 2369914.0416666665
  double JD = TE.getJulianDate(1776,7,4,13);

  Serial.begin(9600);
  Serial.println("HELLO");
  Serial.println(JD, 10);
  Serial.println("Goodbye");

}

void loop() {
  // put your main code here, to run repeatedly:

}
