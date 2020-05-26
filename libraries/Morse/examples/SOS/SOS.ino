#include <Morse.h>

Morse morse(13);

void setup() {
  // put your setup code here, to run once:
  morse.flash();

}

void loop() {
  morse.dot(); morse.dot(); morse.dot(); morse.space();
  morse.dash(); morse.dash(); morse.dash(); morse.space();
  morse.dot(); morse.dot(); morse.dot(); morse.space();
  delay(3000);
}
