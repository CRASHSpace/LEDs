/*
 File: HSB_to_RGB.cpp
 Created for Arduino by @mpinner 

 orginial code by David A. Mellis, November 2, 2007.
 Released into the public domain.
*/

#include "HSB_to_RGB.h"

void HSB_to_RGB::getRGB(int hue, int sat, int val, int colors[3]) {
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.      
  */
  
    
  val = dim_curve[val];
  sat = 255-dim_curve[255-sat];
  
  int r;
  int g;
  int b;
  int base;
  
  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;  
  } else  { 
    
    base = ((255 - sat) * val)>>8;
  
    switch(hue/60) {
    case 0:
      r = val;
      g = (((val-base)*hue)/60)+base;
      b = base;
      break;
      
    case 1:
      r = (((val-base)*(60-(hue%60)))/60)+base;
      g = val;
      b = base;
      break;
      
    case 2:
      r = base;
      g = val;
      b = (((val-base)*(hue%60))/60)+base;
      break;
      
    case 3:
      r = base;
      g = (((val-base)*(60-(hue%60)))/60)+base;
      b = val;
      break;
      
    case 4:
      r = (((val-base)*(hue%60))/60)+base;
      g = base;
      b = val;
      break;
      
    case 5:
      r = val;
      g = base;
      b = (((val-base)*(60-(hue%60)))/60)+base;
      break;
    }
      
    colors[0]=r;
    colors[1]=g;
    colors[2]=b; 
  }

}
