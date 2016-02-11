#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT1_PIN A1

unsigned long time; //Keep track of the time

// Neopixel randomness
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int onTime = 1000;
long randOn = 50; // ~5% of cycles, turn on random pixel

// Potentiometer & Colors
int val1;
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int purple[3] = {255, 0, 255};
int red[3] = {255, 0, 0};
int yellow[3] = {255, 255, 0}; 

void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  Serial.println("Serial Up");
}

void loop() {
  onTime = 1000; //We'll change this when we get an accelerometer.
  randOn = 50; //This should also shift with accelerometer maybe.
  time = millis();
  
  val1 = analogRead(POT1_PIN); // value for first potentiometer
  double ratio1 = (double) (val1 / 1023.0); // used to determine position between hues
  
  double whiteLevel;
  for (int i = 0; i < NUM_PIXELS; i++) {
    double diff = time - stripArr[i]; //Time always >= set stripArrs
    double halfOnTime = (double)onTime / 2;
    if(diff < halfOnTime) { //Increase brightness
      whiteLevel = diff / (halfOnTime) * 255;
    } else if  (diff >= halfOnTime && diff < onTime) { //Decrease
      whiteLevel = ((double)onTime - diff) / (halfOnTime) * 255;
    }
    else {
      whiteLevel = NULL;
      if (random(0, 1000) < randOn) {
        stripArr[i] = time;
      }
    }
    if (whiteLevel) {
      if (whiteLevel < 20) {
        whiteLevel = 20;
      }
      strip.setPixelColor(i, strip.Color((int)whiteLevel, (int)whiteLevel, (int)whiteLevel));
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
  }
  strip.show();
  delay(50); //This should be kept constant
}
