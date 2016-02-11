#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define STRIP_PIN 6
#define POT_PIN A1
int val = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(POT_PIN);
  double ratio = (double) (val / 1023.0); 
  int green[3] = {0, 255, 0};
  int blue[3] = {0, 0, 255};
  int redVal = (green[0]* ratio) + (blue[0] * (1-ratio));
  int greenVal = (green[1]* ratio) + (blue[1] * (1-ratio));
  int blueVal = (green[2]* ratio) + (blue[2] * (1-ratio));
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, redVal, greenVal, blueVal);
  } 
  strip.show();
}
