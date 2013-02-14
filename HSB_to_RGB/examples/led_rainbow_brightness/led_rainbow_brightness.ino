/*
date: 2013-Feb-14
file: led_rainbow_brightness.ino
author: @mpinner for @crashspacela

intent: create a short led sequence that rotates through the rainbow with brightness conotrol

licence: cc-by-sa
*/

#include <HSB_to_RGB.h>
#include <Adafruit_NeoPixel.h>

// pin definitions
#define LED_STRIP_DATA_PIN 9
#define BRIGHTNESS_CONTROL_PIN A1

// number of pixel in the strip
#define PIXELS 5

// HSB_to_RGB provides conversion from HSB and brightness to RGB for smooth color cycling
HSB_to_RGB hsb = HSB_to_RGB();

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, LED_STRIP_DATA_PIN, NEO_RGB + NEO_KHZ800);

// portion of the HSB color spectrum for each pixel
#define MAX_COLOR 255.0
const float colorPortionRespondsibilities = MAX_COLOR / PIXELS;


void setup() { 
  strip.begin(); 
}


void loop() {
    rowScan();
}
  
  
/* rotates colors on strip */
void rowScan() {

  uint16_t pixel, colorIndex, hue;

  for(colorIndex = 0; colorIndex < MAX_COLOR; colorIndex++) {
    for(pixel = 0; pixel < PIXELS; pixel++) {
      
      int hue = colorIndex + pixel * colorPortionRespondsibilities;
  
      if (hue > 255) {
        hue = hue - 255;
      }
   
      setPixelColor(pixel, hue , brightness());
      
    }
    strip.show();    
  }
  
  return;  
}


/* wrapper for adafruit method that uses HSB */
void setPixelColor(uint16_t pixelNumber, uint32_t color, uint16_t bright) {
   int colors[3] = {0,0,0};
  hsb.getRGB((int)color, 255, bright, colors);
  strip.setPixelColor(pixelNumber, colors[0], colors[1], colors[2]);
  return;
}


/* returns brightness from sensor */ 
int brightness() {
  return analogRead(BRIGHTNESS_CONTROL_PIN) / 4;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
