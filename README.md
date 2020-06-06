# Teensy_Ephemeris
Arduino library to perform planetary calculations. Requires Teensy4.0 processor or above.
## Introduction
The teensy_ephemeris library can be used to calculate the position of the moon in space at any
given point in time. It can also give the moon's location in the at any time, date, and location on Earth.

## Limitations
The math used in the planetary calculations requires greater precision than is possible with standard Arduino boards such as the UNO. This library requires a Teensy board, version 4.0 or later. More information about Teensy boards is available at https://www.pjrc.com/store/ Teensy boards are available for purchase at [Adafruit](https://www.adafruit.com/?q=teensy), [Sparkfun](https://www.sparkfun.com/categories/356), and other suppliers.
***WARNING: If you attempt to use this library with a standard Arduino board, the results will be unreliable!***

## Installation
**NOTE:** Uploading a program to a Teensy board is a little bit different than uploading program to a standard Arduino board such as the UNO. There are some instructions from the board's designers on getting started with the board [here](https://www.pjrc.com/teensy/first_use.html), and a helpful page and video explaining how to install a special version of the Arduino IDE with Teensy support already built in [here](https://core-electronics.com.au/tutorials/teensy/using-teensy-with-arduino-ide.html).

To install the library, download the .zip file for the library [here](https://github.com/chrisspurgeon/teensy_ephemeris/archive/master.zip), unzip the file, and drop the folder named "Teensy_Ephemeris" into the "Libraries" folder used by your Arduino or Teensyduino IDE.

Once the library is installed, add it to any Arduino sketch by choosing "Add Library" from the "Sketch" menu in the Arduino/Teensyduino IDE and selecting the library named "Teensy_Ephemeris". That should automatically add this line at the top of your sketch...

```C++
#include <Teensy_Ephemeris.h>
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

## Using the library
To use the library in your Arduino sketch, first create a new Teensy_Ephemeris object, like this...

```C++
#include <Teensy_Ephemeris.h>

Teensy_Ephemeris myPlanet;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

You'll typically then provide the object with an observation time, and an observer's position on the earth...
```C++
#include <Teensy_Ephemeris.h>

Teensy_Ephemeris myPlanet;
void setup() {
  // put your setup code here, to run once:
myPlanet.setLocation(42.34625, -71.09775);
myPlanet.setsetTime(2020,12,25,5,15,42);
}

void loop() {
  // put your main code here, to run repeatedly:

}
```
