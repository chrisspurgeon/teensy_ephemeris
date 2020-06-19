#include "Teensy_Ephemeris.h"

void Teensy_Ephemeris::calculateMoonPosition() {

  unsigned char T45AD [60] = { 0, 2, 2, 0, 0, 0, 2, 2, 2, 2,
                               0, 1, 0, 2, 0, 0, 4, 0, 4, 2,
                               2, 1, 1, 2, 2, 4, 2, 0, 2, 2,
                               1, 2, 0, 0, 2, 2, 2, 4, 0, 3,
                               2, 4, 0, 2, 2, 2, 4, 0, 4, 1,
                               2, 0, 1, 3, 4, 2, 0, 1, 2, 2 };

  int T45AM [60] = {  0,  0,  0,  0,  1,  0,  0, -1,  0, -1,
                      1,  0,  1,  0,  0,  0,  0,  0,  0,  1,
                      1,  0,  1, -1,  0,  0,  0,  1,  0, -1,
                      0, -2,  1,  2, -2,  0,  0, -1,  0,  0,
                      1, -1,  2,  2,  1, -1,  0,  0, -1,  0,
                      1,  0,  1,  0,  0, -1,  2,  1,  0,  0 };

  int T45AMP [60] = { 1, -1,  0,  2,  0,  0, -2, -1,  1,  0,
                     -1,  0,  1,  0,  1,  1, -1,  3, -2, -1,
                      0, -1,  0,  1,  2,  0, -3, -2, -1, -2,
                      1,  0,  2,  0, -1,  1,  0, -1,  2, -1,
                      1, -2, -1, -1, -2,  0,  1,  4,  0, -2,
                      0,  2,  1, -2, -3,  2,  1, -1,  3, -1 };

  int T45AF [60] = {  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
                      0,  0,  0, -2,  2, -2,  0,  0,  0,  0,
                      0,  0,  0,  0,  0,  0,  0,  0,  2,  0,
                      0,  0,  0,  0,  0, -2,  2,  0,  2,  0,
                      0,  0,  0,  0,  0, -2,  0,  0,  0,  0,
                     -2, -2,  0,  0,  0,  0,  0,  0,  0, -2 };

  int T45AL [60] = { 6288774, 1274027, 658314, 213618, -185116,
                     -114332,   58793,  57066,  53322,   45758,
                      -40923,  -34720, -30383,  15327,  -12528,
                       10980,   10675,  10034,   8548,   -7888,
                       -6766,   -5163,   4987,   4036,    3994,
                        3861,    3665,  -2689,  -2602,    2390,
                       -2348,    2236,  -2120,  -2069,    2048,
                       -1773,   -1595,   1215,  -1110,    -892,
                        -810,     759,   -713,   -700,     691,
                         596,     549,    537,    520,    -487,
                        -399,    -381,    351,   -340,     330,
                         327,    -323,    299,    294,       0 };

  int T45AR [60] = { -20905355, -3699111, -2955968, -569925,   48888,
                         -3149,   246158,  -152138, -170733, -204586,
                       -129620,   108743,   104755,   10321,       0,
                         79661,   -34782,   -23210,  -21636,   24208,
                         30824,    -8379,   -16675,  -12831,  -10445,
                        -11650,    14403,    -7003,       0,   10056,
                          6322,    -9884,     5751,       0,   -4950,
                          4130,        0,    -3958,       0,    3258,
                          2616,    -1897,    -2117,    2354,       0,
                             0,    -1423,    -1117,   -1571,   -1739,
                             0,    -4421,        0,       0,       0,
                             0,     1165,        0,       0,    8752 };

  // Meeus table 45B latitude of the moon

  unsigned char T45BD [60] = { 0, 0, 0, 2, 2, 2, 2, 0, 2, 0,
                               2, 2, 2, 2, 2, 2, 2, 0, 4, 0,
                               0, 0, 1, 0, 0, 0, 1, 0, 4, 4,
                               0, 4, 2, 2, 2, 2, 0, 2, 2, 2,
                               2, 4, 2, 2, 0, 2, 1, 1, 0, 2,
                               1, 2, 0, 4, 4, 1, 4, 1, 4, 2 };

  int T45BM [60] = { 0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
                    -1,  0,  0,  1, -1, -1, -1, 1,  0,  1,
                     0,  1,  0,  1,  1,  1,  0, 0,  0,  0,
                     0,  0,  0,  0, -1,  0,  0, 0,  0,  1,
                     1,  0, -1, -2,  0,  1,  1, 1,  1,  1,
                     0, -1,  1,  0, -1,  0,  0, 0, -1, -2 };

  int T45BMP [60] = { 0,  1, 1,  0, -1, -1,  0,  2,  1,  2,
                      0, -2, 1,  0, -1,  0, -1, -1, -1,  0,
                      0, -1, 0,  1,  1,  0,  0,  3,  0, -1,
                      1, -2, 0,  2,  1, -2,  3,  2, -3, -1,
                      0,  0, 1,  0,  1,  1,  0,  0, -2, -1,
                      1, -2, 2, -2, -1,  1,  1, -1,  0,  0 };

  int T45BF [60] = { 1,  1, -1, -1,  1, -1,  1,  1, -1, -1,
                    -1, -1,  1, -1,  1,  1, -1, -1, -1,  1,
                     3,  1,  1,  1, -1, -1, -1,  1, -1,  1,
                    -3,  1, -3, -1, -1,  1, -1,  1, -1,  1,
                     1,  1,  1, -1,  3, -1, -1,  1, -1, -1,
                     1, -1,  1, -1, -1, -1, -1, -1, -1,  1 };

  int T45BL [60] = { 5128122, 280602, 277693, 173237, 55413,
                       46271,  32573,  17198,   9266,  8822,
                        8216,   4324,   4200,  -3359,  2463,
                        2211,   2065,  -1870,   1828, -1794,
                       -1749,  -1565,  -1491,  -1475, -1410,
                       -1344,  -1335,   1107,   1021,   833,
                         777,    671,    607,    596,   491,
                        -451,    439,    422,    421,  -366,
                        -351,    331,    315,    302,  -283,
                        -229,    223,    223,   -220,  -220,
                        -185,    181,   -177,    176,   166,
                        -164,    132,   -119,    115,   107 };



  setJulianDate();

  if (debug) {
    Serial.println("DEBUG: calculateMoonPosition()");
  }
  double T = 0.000L;
  double T2 = 0.000L;
  double T3 = 0.000L;
  double T4 = 0.000L;
  double Tshifted = 0.000L;
  double T2shifted = 0.00L;
  double T3shifted = 0.00L;
  double T4shifted = 0.00L;
  Tshifted = (getJulianDate() - 2451545.0) / 365.250; // increase by 100 to stop rounding errors.
  T = Tshifted / 100.00;
  T2shifted = Tshifted * Tshifted;
  T2 = T2shifted / 10000.00;
  T3shifted = Tshifted * Tshifted * Tshifted;
  T3 = T3shifted / 1000000.00;
  T4shifted = Tshifted * Tshifted * Tshifted * Tshifted;
  T4 = T4shifted / 100000000.00;

  // Moons mean longitude L'
  double LP = 218.3164477 + 481267.88123421 * T -0.0015786 * T2 + T3 / 538841.0 - T4 / 65194000.0;

  // Moons mean elongation Meeus second edition
  double D = 297.8501921 + 445267.1114034 * T - 0.0018819 * T2 + T3 / 545868.0 - T4 / 113065000.0;

  // Moons mean anomaly M' Meeus second edition
  double MP = 134.9633964 + 477198.8675055 * T + 0.0087414 * T2 + T3 / 69699.0 - T4 / 14712000.0;

  // Moons argument of latitude
  double F = 93.2720950 + 483202.0175233 * T - 0.0036539 * T2 - T3 / 3526000.0 + T4 / 863310000.0;

  // Suns mean anomaly
  double M = 357.5291092 + 35999.0502909 * T - 0.0001536 * T2 + T3 / 24490000.0;

  double A1 = 119.75 + 131.849 * T;
  double A2 = 53.09 + 479264.290 * T;
  double A3 = 313.45 + 481266.484 * T;
  double E = 1.0 - 0.002516 * T - 0.0000074 * T2;
  double E2 = E * E;

  if (debug) {
    Serial.print("       T:  ");
    Serial.println(T,12);
    Serial.print("       T2: ");
    Serial.println(T2,12);
    Serial.print("       T3: ");
    Serial.println(T3,12);
    Serial.print("       T4: ");
    Serial.println(T4,12);
    Serial.print("       LP: ");
    Serial.println(LP,12);
    Serial.print("       D:  ");
    Serial.println(D,12);
    Serial.print("       MP: ");
    Serial.println(MP,12);
    Serial.print("       F:  ");
    Serial.println(F,12);
    Serial.print("       M:  ");
    Serial.println(M,12);
    Serial.print("       A1: ");
    Serial.println(A1,12);
    Serial.print("       A2: ");
    Serial.println(A2,12);
    Serial.print("       A3: ");
    Serial.println(A3,12);
    Serial.print("       E:  ");
    Serial.println(E,12);
    Serial.print("       E2: ");
    Serial.println(E2,12);
  }

  // Sums of periodic terms from table 45.A and 45.B
  double Sl = 0.0;
  double Sr = 0.0;
  double Eterm = 0.0;
  int i;
  for (i = 0; i < 60; i++) {
    Eterm = 1.0;
    if (abs(T45AM[i]) == 1) {
      Eterm = E;
    }
    if (abs(T45AM[i]) == 2) {
      Eterm=E2;
    }
    Sl += T45AL[i] * Eterm * sind(rev(T45AD[i] * D + T45AM[i] * M + T45AMP[i] * MP + T45AF[i] * F));
    Sr += T45AR[i] * Eterm * cosd(rev(T45AD[i] * D + T45AM[i] * M + T45AMP[i] * MP + T45AF[i] * F));
  }

  double Sb = 0.0;
  for (i = 0; i < 60; i++) {
    Eterm = 1.00;
    if (abs(T45BM[i]) == 1) {
      Eterm = E;
    }
    if (abs(T45BM[i]) == 2) {
      Eterm = E2;
    }
    Sb += T45BL[i] * Eterm * sind(rev(T45BD[i] * D + T45BM[i] * M + T45BMP[i] * MP + T45BF[i] * F));
  }
  // Additional additive terms
  Sl = Sl + 3958 * sind(rev(A1)) + 1962 * sind(rev(LP - F)) + 318.0 * sind(rev(A2));
  Sb = Sb - 2235 * sind(rev(LP)) + 382 * sind(rev(A3)) + 175.0 * sind(rev(A1-F)) + 175.0 * sind(rev(A1 + F)) + 127.0 * sind(rev(LP - MP)) - 115.0 * sind(rev(LP + MP));

  if (debug) {
    Serial.print("       Sl: ");
    Serial.println(Sl,12);
    Serial.print("       Sr: ");
    Serial.println(Sr,12);
    Serial.print("       Sb: ");
    Serial.println(Sb,12);
  }

  // geocentric longitude, latitude and distance
  double mglong = rev(LP + Sl / 1000000.0);
  double mglat = rev(Sb / 1000000.0);
  if (mglat > 180.0) {
    mglat = mglat - 360.0;
  }
  double mr = round(385000.56 + Sr / 1000.0);

  // Obliquity of Ecliptic
  double obl = 23.4393 - 3.563E-7 * (time.JulianDate - 2451543.5);
  // RA and dec
  double ra = rev(atan2d(sind(mglong) * cosd(obl) - tand(mglat) * sind(obl), cosd(mglong))) / 15.0;
  double dec = rev(asind(sind(mglat) * cosd(obl) + cosd(mglat) * sind(obl) * sind(mglong)));
  if (dec > 180.0) {
    dec = dec - 360.0;
  }

  body.RA  = ra;
  body.dec = dec;

  if (debug) {
    Serial.print("       mglong: ");
    Serial.println(mglong,12);
    Serial.print("       mglat: ");
    Serial.println(mglat,12);
    Serial.print("       mr: ");
    Serial.println(mr,12);
    Serial.print("       obl: ");
    Serial.println(obl,12);
    Serial.print("       ra: ");
    Serial.println(ra,12);
    Serial.print("       dec: ");
    Serial.println(dec,12);
  }

  // phase angle
  double pa = 180.0 - D - 6.289 * sind(MP) + 2.1 * sind(M) - 1.274 * sind(2 * D - MP) - 0.658 * sind(2 * D) - 0.214 * sind(2 * MP) - 0.11 * sind(D);

  if (debug) {
    Serial.print("       pa: ");
    Serial.println(pa,12);
  }


  // // Altitude and azimuth
  // var altaz=radtoaa(ra,dec,obs);
  // return new Array(ra,dec,mr,altaz[0],altaz[1],rev(pa));

  calculateAltitudeAndAzimuth();
}
