#include <Teensy_Ephemeris.h>

Teensy_Ephemeris TE;
void setup() {

  // TE.getJulianDate(2020,5,29,23,50,54) should return 2458999.4936805554
  double JD = TE.getJulianDate(2020,5,29,23,50,54);

  Serial.begin(9600);
  Serial.println("For TE.getJulianDate(2020,5,29,23,50,54) I expect a value of 2458999.4936805554. We got...");
  Serial.println(JD, 10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
