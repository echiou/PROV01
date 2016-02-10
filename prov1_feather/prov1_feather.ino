#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT_ONE 7

unsigned long time; //Keep track of the time
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int whiteLevel = 0;
bool up = true;

void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //This is a global variable so that we can just rely on loop() to repeat behavior
  if (whiteLevel >= 240) {
    up = false;
  }
  else if (whiteLevel < 10) {
    up = true;
  }
  
  /*
  if (up){
   whiteLevel = whiteLevel % 255; 
  }
  else {
    whiteLevel = 255 - (whiteLevel % 255);
  }
  */
  for (int i = 0; i < NUM_PIXELS; i++) { 
    strip.setPixelColor(i, whiteLevel, whiteLevel, whiteLevel);
  }
  if (up) {
    whiteLevel = whiteLevel + 10;
  } else {
    whiteLevel = whiteLevel - 10;
  }
  delay(100); // Delay can be adjusted as we like
  strip.show();

  /*
  //Fade all at once
  time = millis(); //We'll need this for when different things start fading differently
  int whiteLevel = 0;
  for (int i = 0; i < NUM_PIXELS; i++) {
    whiteLevel = time - stripArr[i]; //Flashing white, so all the same
    strip.setPixelColor(i, strip.Color(whiteLevel, whiteLevel, whiteLevel));
    if (whiteLevel >= 255) { //Reset when it's fully white (Change when we do colours.)
      stripArr[i] = time;
    }
  }
  */
}
