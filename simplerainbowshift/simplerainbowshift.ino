// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS     7
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int rgbLights = 7;
int red[7];
int green[7];
int blue[7];

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.

}


void hsi_to_rgb(int startChannel, float H, float S, float I) {
  int r, g, b;
  //  if (H > 360) {
  //    H = H - 360;
  //  }
  // Serial.println("H: "+String(H));
  H = fmod(H, 360); // cycle H around to 0-360 degrees
  H = 3.14159 * H / (float)180; // Convert to radians.
  S = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
  I = I > 0 ? (I < 1 ? I : 1) : 0;
  if (H < 2.09439) {
    r = 255 * I / 3 * (1 + S * cos(H) / cos(1.0471967 - H));
    g = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.0471967 - H)));
    b = 255 * I / 3 * (1 - S);
  } else if (H < 4.188787) {
    H = H - 2.09439;
    g = 255 * I / 3 * (1 + S * cos(H) / cos(1.047196667 - H));
    b = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.0471967 - H)));
    r = 255 * I / 3 * (1 - S);
  } else {
    H = H - 4.188787;
    b = 255 * I / 3 * (1 + S * cos(H) / cos(1.047196667 - H));
    r = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.0471967 - H)));
    g = 255 * I / 3 * (1 - S);
  }
  red[startChannel] = r;
  green[startChannel] = g;
  blue[startChannel] = b;

}


void rainbowShift(float brightness, float saturation, int delayint, int interval) {
 
  for (int n = 0; n <= 360; n++) {
    for (int i = 0, j = 0; i < NUMPIXELS; i++) {
      //We initialize each value of each pixel with the hsi to rgb function
      hsi_to_rgb(i, (n + i)*interval, saturation, brightness) ;
      //Serial.println("rgb" +String(i)+": "+String(rgb[j])+","+String(rgb[j+1])+","+String(rgb[j+2]));
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
      j++;
    }
    // This sends the updated pixel color to the hardware.
    pixels.show();
    delay(delayint);
  }
}



void rainbowShiftRv(float brightness, float saturation, int delayint, int interval) {

  for (int n = 360; n >= 0; n--) {
    for (int i = 0, j = 0; i < NUMPIXELS; i++) {
      hsi_to_rgb(i, (n + i)*interval, saturation, brightness) ;
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
      j++;
    }
    pixels.show();
    // This sends the updated pixel color to the hardware.
    delay(delayint);
  }
}


void rainbowShiftEveryOther(float brightness, float saturation, int delayint) {
  
  for (int n = 0; n <= 360; n++) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      hsi_to_rgb(i, n, saturation, brightness) ;
    }
    for (int i = 1; i < NUMPIXELS; i = i + 2) {
      hsi_to_rgb(i, n + 180, saturation, brightness) ;
    }
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
    }
    pixels.show();
    // This sends the updated pixel color to the hardware.
    delay(delayint);
  }
}


void rainbowShiftSegments(float brightness, float saturation, int delayint) {
  
  for (int n = 0; n <= 360; n++) {
    for (int i = 0; i < NUMPIXELS; i = i + 4) {
      hsi_to_rgb(i, n, saturation, brightness) ;
    }
    for (int i = 1; i < NUMPIXELS; i = i + 4) {
      hsi_to_rgb(i, n + 60, saturation, brightness) ;
    }
    for (int i = 2; i < NUMPIXELS; i = i + 4) {
      hsi_to_rgb(i, n + 120, saturation, brightness) ;
    }
    for (int i = 3; i < NUMPIXELS; i = i + 4) {
      hsi_to_rgb(i, n + 180, saturation, brightness) ;
    }
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
    }
    pixels.show();
    // This sends the updated pixel color to the hardware.
    delay(delayint);
  }
}


void rainbowShiftHalves() {
  float brightness = .5;
  float saturation = 1;
  for (int n = 0; n <= 360; n++) {
    for (int i = 6, j = 0; i < NUMPIXELS; i++, j++) {
      //We initialize each value of each pixel with the hsi to rgb function
      hsi_to_rgb(i, n, saturation, brightness) ;
      hsi_to_rgb(j, n + 180, saturation, brightness) ;

      //Serial.println("rgb" +String(i)+": "+String(rgb[j])+","+String(rgb[j+1])+","+String(rgb[j+2]));
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
      pixels.setPixelColor(j, pixels.Color(red[j], green[j], blue[j]));

    }
    // This sends the updated pixel color to the hardware.
    pixels.show();
    delay(25);
  }
}



void theaterChaseRainbow(uint8_t wait) {
  float brightness = .5;
  float saturation = 1;
  for (int j = 0; j < 360; j++) {   // cycle all 360 colors in the hsi color space
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < NUMPIXELS; i = i + 3) {
        hsi_to_rgb(i, j, saturation, brightness) ;
        pixels.setPixelColor(i + q, red[i], green[i], blue[i]);  //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i = 0; i < NUMPIXELS; i = i + 3) {
        pixels.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}





void colorShift(float brightness, float saturation, int delayint) {
 // float brightness = .5;
 // float saturation = 1;
  for (int n = 0; n <= 360; n++) {
    for (int i = 0, j = 0; i < NUMPIXELS; i++) {
      //We initialize each value of each pixel with the hsi to rgb function
      hsi_to_rgb(i, n, saturation, brightness) ;
      //Serial.println("rgb" +String(i)+": "+String(rgb[j])+","+String(rgb[j+1])+","+String(rgb[j+2]));
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
      j++;
    }
    // This sends the updated pixel color to the hardware.
    pixels.show();
    delay(delayint);
  }
}
//
// void colorshift(int delyValue, int pixel, int startColor, int endColor){
//
//
//       for(){}


void rainbowShiftHalves(float brightness, float saturation, int delayint, int interval) {

  for (int n = 0; n <= 360; n++) {
    for (int i = 0, j = 0; i < NUMPIXELS; i++) {
      //We initialize each value of each pixel with the hsi to rgb function
      hsi_to_rgb(i, (n + i)*interval, saturation, brightness) ;
      //Serial.println("rgb" +String(i)+": "+String(rgb[j])+","+String(rgb[j+1])+","+String(rgb[j+2]));
      pixels.setPixelColor(i, pixels.Color(red[i], green[i], blue[i]));
      j++;
    }
    // This sends the updated pixel color to the hardware.
    pixels.show();
    delay(delayint);
  }
}

void loop() {
//function does not work well
//  rainbowShiftHalves(); 
//
//theaterChaseRainbow(50);
// rainbowShiftHalves(.7,1,25,30);
//  rainbowShiftEveryOther(.7,1,25);
// rainbowShiftHalves(.7,1,random(10, 200),random(1,50));
  
  
  colorShift(.7,1,random(10, 200));
  colorShift(.7,1,random(10, 200)); 
  rainbowShiftSegments(.7,1,random(10, 200));
  rainbowShiftEveryOther(.7,1,random(10, 200));
  rainbowShift(.7,1,random(10, 200),random(1,50));
  rainbowShiftHalves(.7,1,random(10, 200),random(1,50));
  colorShift(.7,1,random(100, 500));
 /* 
  rainbowShift(.7,2,25,30);
  colorShift(.7,1,75);
  rainbowShiftRv(.7,1,25,30);
  rainbowShiftRv(.7,1,150,6);
  colorShift(.7,1,random(10, 1000));
  rainbowShiftHalves(.7,1,25,2);
  rainbowShiftEveryOther(.7,1,25);
  colorShift(.7,1,25);
 */
}
