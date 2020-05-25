void setup() {
  float foo = 3.1234567890123456789; // regular float
  double bar = 4.1234567890123456789; // double
  double bar2 = 4.1234567890123456789L; // double with additional "L" flag.

  Serial.begin(9600);
  Serial.println("HELLO?");
  Serial.println(foo, 30);
  Serial.println(bar, 30);
  Serial.println(bar2, 30);
  Serial.println(bar + bar2, 30);
  Serial.println("Goodbye!");

/*  
    Got this output back. Note that the float has a rounding error seven digits in, but the longs
    are good for at least 15 digits.
*/

// HELLO?
// 3.123456716537475
// 4.123456789012345
// 4.123456789012345
// 8.246913578024690
// Goodbye
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
