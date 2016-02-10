#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT_ONE 7

unsigned long time; //Keep track of the time
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int delayTime = 1000;
//int whiteLevel;
//bool up = true;

void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //This is a global variable so that we can just rely on loop() to repeat behavior
//  if (whiteLevel >= 240) {
//    up = false;
//  }
//  else if (whiteLevel < 10) {
//    up = true;
//  }
  
//  if (up){
//   whiteLevel = whiteLevel % 255; 
//  }
//  else {
//    whiteLevel = 255 - (whiteLevel % 255);
//  }
  
//  for (int i = 0; i < NUM_PIXELS; i++) { 
//    strip.setPixelColor(i, whiteLevel, whiteLevel, whiteLevel);
//  }
//  if (up) {
//    whiteLevel = whiteLevel + 10;
//  } else {
//    whiteLevel = whiteLevel - 10;
//  }
//  delay(100); // Delay can be adjusted as we like
//  strip.show();

  delayTime = 1000; //We'll change this when we get an accelerometer.
  double delayTimeOffset = double(delayTime) / 2
  time = millis();
  double whiteLevel;
  for (int i = 0; i < NUM_PIXELS; i++) {
    double diff = time - stripArr[i] - delayTimeOffset; //Flashing white, so all the same
    if(diff < 0) { //Increase brightness
      whiteLevel = -diff / delayTimeOffset * 255;
    } else {
      whiteLevel = diff / delayTimeOffset * 255;
    }
    strip.setPixelColor(i, strip.Color((int)whiteLevel, (int)whiteLevel, (int)whiteLevel));
    if (diff >= delayTimeOffset) { //Reset after a full cycle
      stripArr[i] = time;
    }
  }
  delay(50); //This should be kept constant
}
