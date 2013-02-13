#include <HSB_to_RGB.h>

#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

#define PIXELS 24
#define BRIGHTNESS 74



int rowOffset[] = {0, 0, 5, 24, 39, 60};
int rowsColumns[] = {8, 13, 16, 16, 13, 8};
int rowCount = 6; 

int strobeSpeed = 4;





Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, 9, NEO_RGB + NEO_KHZ800);

HSB_to_RGB hsb = HSB_to_RGB();

int pixel;

void setup() {
  //Serial.begin(9600);
  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  int each = 5;
  
  ///*
  for (int i = 3; i < each; i++) {
    strobeSpeed = i;
    longitude();
  }  
  //*/
  
  for (int i = 1; i < each; i++) {
    strobeSpeed = i;
    longitudeSingleColor();
  }

  for (int i = 1; i < each; i++) {
    strobeSpeed = i;
    latitudeScan();
  }

}
  
  
  void latitudeScan() {

  uint16_t pixel, colorIndex, hue;
  
  float colorPortionRespondsibilities = 255.0 / PIXELS;

 for(colorIndex = 0; colorIndex < 255; colorIndex++) {
  
    for(pixel = 0; pixel < strip.numPixels(); pixel++) {

//      hue = ((int)(colorIndex + ((float)pixel * colorPortionRespondsibilities)));
      
      int hue = colorIndex + pixel * colorPortionRespondsibilities;
  
      ///*
      if (hue > 255) {
        hue = hue - 255;
      }
      //*/
  //    Serial.print(hue);
    //  Serial.print(",");

    
      setPixelColor(pixel, hue , brightness());
      
    }

    strip.show();
  //  Serial.println();
//      Serial.print(",");

    
  }
  
    
}

void setPixelColor(uint16_t n, uint32_t c, uint16_t b) {
 
  //uint8_t r;
  //uint8_t g; 
  //uint8_t blue;
  int colors[3] = {0,0,0};
  
  hsb.getRGB((int)c, 255, b, colors);
  
  strip.setPixelColor(n, colors[0], colors[1], colors[2]);
  
  return;
  
}

void longitude(){

  uint16_t i, j;
  uint16_t pixel;
  

  for(j=0; j<256; j+=2) { // 5 cycles of all colors on wheel
  
    pixel = 0;
  //  int row = 0;
    for (int row = 0; row < rowCount; row++) {
      
      int columnCount = rowsColumns[row];
      int colorRatio = 255/columnCount;
      int columnOffest = rowOffset[row];

      for(int column=0; column < columnCount; column++) {
      //  strip.setPixelColor(pixel, Wheel(j-column*colorRatio));
  // setPixelColor(pixel, j-column*colorRatio+columnOffest,30);
  int hue = column*colorRatio-columnOffest+j;
        if (hue > 255) {
        hue = hue - 255;
      }
         if (hue < 0) {
        hue = hue + 255;
      }
  setPixelColor(pixel, hue,brightness());
   
   
        pixel++;
      }
      
    }
    
  //  j+=analogRead(A0)/12;

    strip.show();
  }
}


void longitudeSingleColor(){

  uint16_t i, j;
  uint16_t pixel;
  

  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
  
    pixel = 0;
  //  int row = 0;
    for (int row = 0; row < rowCount; row++) {
      
      int columnCount = rowsColumns[row];
      int colorRatio = 255/columnCount;
      int columnOffest = rowOffset[row];

      for(int column=0; column < columnCount; column++) {
      //  strip.setPixelColor(pixel, Wheel(j-column*colorRatio));
  // setPixelColor(pixel, j-column*colorRatio+columnOffest,30);
  
  
      int hue = column*colorRatio-columnOffest;
 
      
      if (hue > 255) {
        hue = hue - 255;
      }
      if (hue < 0) {
        hue = hue + 255;
      }
      
   
      
      setPixelColor(pixel, hue, brightness());
   
   
        pixel++;
      }
      
    }
    
  //  j+=analogRead(A0)/12;

    strip.show();
  }
}


int brightness() {
  
  return analogRead(A1) / 4;
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
