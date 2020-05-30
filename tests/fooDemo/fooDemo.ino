#include <Teensy_Ephemeris.h>

Teensy_Ephemeris TE;
void setup() {

  Serial.begin(9600);

  TE.fooholder.var1 = 18;
  TE.fooholder.var2 = 333;
  TE.fooholder.var1 = TE.foocheck();
  Serial.println(TE.fooholder.var1);

}

void loop() {
  // put your main code here, to run repeatedly:

}
