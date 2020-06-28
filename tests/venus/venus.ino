#include <Teensy_Ephemeris.h>

// Let's calculate the position of Venus!
//
// We start by creating a new Teensy_Ephemeris object.
// We'll name it "MyVenusObject".

Teensy_Ephemeris MyVenusObject;

void setup() {

  Serial.begin(9600);

  // uncomment this line to output debugging information when
  // values are changed or calculated.
  MyVenusObject.setDebugging(true);
  
  MyVenusObject.setName("venus");

  Serial.println("Let's see if the enum works...");
  MyVenusObject.getPlanetOffset("VENUS");

}

void loop() {
  // put your main code here, to run repeatedly:

}
