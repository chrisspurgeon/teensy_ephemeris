#include <Teensy_Ephemeris.h>

Teensy_Ephemeris TE;
void setup() {

  TE.setTime(2020,5,29,23,50,54);
  TE.setJulianDate();

  Serial.begin(9600);

  // TE.getJulianDate() should return 2458999.4936805554
  Serial.println(TE.getJulianDate(), 10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
