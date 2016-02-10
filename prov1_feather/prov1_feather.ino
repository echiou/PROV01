#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT_ONE 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:

}
