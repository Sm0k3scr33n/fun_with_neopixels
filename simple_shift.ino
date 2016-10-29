// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
}

void fade(int startRED, int startGREEN, int startBLUE, int endRED, int endGREEN, int endBLUE, int fadeTIME){

long deltaR;
long deltaG;
long deltaB;
long RedStep;
long GreenStep;
long BlueStep;

if (startRED>endRED){deltaR = startRED - endRED; serial.print("deltaR: "+deltaR+" StartRED > endRED")}
if (startRED<endRED){deltaR = endRED - startRED; serial.print(" StartRED < endRED")}
if (startGREEN>endGREEN){deltaG = startGREEN - endGREEN; serial.print("StartRED > endRED")}
if (startGREEN<endGREEN){deltaG = endGREEN - startGREEN; serial.print("StartRED < endRED")}
if (startBLUE>endBLUE){deltaB = startBLUE - endBLUE; serial.print("StartRED > endRED")}
if (startBLUE<endBLUE){deltaB = endBLUE - startBLUE; serial.print("StartRED < endRED")}

RedStep   = deltaR/255;serial.print()
GreenStep = deltaG/255;
BlueStep  = deltaB/255;

long delayTime = fadeTIME/255;


     long rVal = startRED;
     long gVal = startGREEN;
     long bVal = startBLUE;

  delay(500);
for(int i=0;i<255;i++){
    for(int j=0;j<NUMPIXELS;j++){
   pixels.setPixelColor(j, pixels.Color(rVal,gVal,bVal)); // Moderately bright green color.
   pixels.show(); // This sends the updated pixel color to the hardware.
      }

  if (startRED>endRED){rVal=rVal - RedStep;}
  if (startRED<endRED){rVal=rVal + RedStep;}
  if (startGREEN>endGREEN){gVal=gVal - GreenStep;}
  if (startGREEN<endGREEN){gVal=gVal + GreenStep;}
  if (startBLUE>endBLUE){bVal=bVal - BlueStep;}
  if (startBLUE<endBLUE){bVal=bVal + BlueStep;}
  delay(delayTime);

  }





}


void loop() {
//       for(int j=0;j<NUMPIXELS;j++){
//   pixels.setPixelColor(j, pixels.Color(255,0,0)); // Moderately bright green color.
//   pixels.show(); // This sends the updated pixel color to the hardware.
//   
//  }
  
  fade(0,40,255,
       255,155,0,2500);//
       
  fade(255,155,0,
       0,40,255,2500);
 

  
  
}
