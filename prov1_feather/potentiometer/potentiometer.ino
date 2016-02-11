#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define STRIP_PIN 6
#define POT_PIN A1

#define STRIP_ONE 12
#define STRIP_TWO 4
#define STRIP_THREE 8
#define STRIP_FOUR 0

int val = 0;
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int purple[3] = {255, 0, 255};
int red[3] = {255, 0, 0};
int yellow[3] = {255, 255, 0}; 

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
  showColor(STRIP_ONE, ratio);
//  Show additional columns only when we have the full grid
//  showColor(STRIP_TWO, ratio);
//  showColor(STRIP_THREE, ratio);
//  showColor(STRIP_FOUR, ratio);
  strip.show(); 
}

void showColor(int strip_number, double ratio) {
  int redVal = 0;
  int greenVal = 0;
  int blueVal = 0; 
  // TODO: make this less jank
  if (strip_number == STRIP_ONE) { 
    redVal = (green[0] * ratio) + (blue[0] * (1-ratio)); 
    greenVal = (green[1] * ratio) + (blue[1] * (1-ratio)); 
    blueVal = (green[2] * ratio) + (blue[2] * (1-ratio));
  } else if (strip_number == STRIP_TWO) {
    redVal = (blue[0] * ratio) + (purple[0] * (1-ratio)); 
    greenVal = (blue[1] * ratio) + (purple[1] * (1-ratio)); 
    blueVal = (blue[2] * ratio) + (purple[2] * (1-ratio));
  } else if (strip_number == STRIP_THREE) {
    redVal = (purple[0] * ratio) + (red[0] * (1-ratio)); 
    greenVal = (purple[1] * ratio) + (red[1] * (1-ratio)); 
    blueVal = (purple[2] * ratio) + (red[2] * (1-ratio));
  } else { // strip_number == STRIP_FOUR
    redVal = (red[0] * ratio) + (yellow[0] * (1-ratio)); 
    greenVal = (red[1] * ratio) + (yellow[1] * (1-ratio)); 
    blueVal = (red[2] * ratio) + (yellow[2] * (1-ratio));
  }
  // use strip_number as an offset to set the correct pixels on the board
  for (int i = strip_number; i < strip_number + NUM_PIXELS; i++) {
    strip.setPixelColor(i, redVal, greenVal, blueVal);
  }  
}

