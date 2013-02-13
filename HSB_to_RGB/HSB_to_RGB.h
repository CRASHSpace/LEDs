/*
 File: HSB_to_RGB.h
 Created for Arduino by @mpinner 

 orginial code by David A. Mellis, November 2, 2007.
 Released into the public domain.
*/

#ifndef HSP_TO_RGB_h
#define HSP_TO_RGB_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

/*
 Control a RGB led with Hue, Saturation and Brightness (HSB / HSV )
 
 Hue is change by an analog input.
 Brightness is changed by a fading function.
 Saturation stays constant at 255
 
 getRGB() function based on <http://www.codeproject.com/miscctrl/CPicker.asp>
 dim_curve idea by Jims
 
 created 05-01-2010 by kasperkamperman.com
 */

/*
 dim_curve 'lookup table' to compensate for the nonlinearity of human vision.
 Used in the getRGB function on saturation and brightness to make 'dimming' look more natural.
 Exponential function used to create values below :
 x from 0 - 255 : y = round(pow( 2.0, x+64/40.0) - 1)
 */

const byte dim_curve[] = {
    0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
    3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
    6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
    11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
    15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
    20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
    27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
    36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
    48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
    63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
    83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};


class HSB_to_RGB {
  public: void getRGB(int hue, int sat, int val, int colors[3]);
};

#endif
