#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT_ONE 7

unsigned long time; //Keep track of the time
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //Fade all at once
  time = millis(); //We'll need this for when different things start fading differently
  for (int i = 0; i < NUM_PIXELS; i++) {
    int whiteLevel = time - stripArr[i]; //Flashing white, so all the same
    strip.setPixelColor(i, strip.Color(whiteLevel, whiteLevel, whiteLevel));
    if (whiteLevel >= 255) { //Reset when it's fully white (Change when we do colours.)
      stripArr[i] = time;
    }
  }
  strip.show();
}
