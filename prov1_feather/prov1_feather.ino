#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 4
#define NP_PIN 6
#define POT_ONE 7

unsigned long time; //Keep track of the time
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int onTime = 1000;
//int whiteLevel;
//bool up = true;

void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Up");
}

void loop() {
  onTime = 1000; //We'll change this when we get an accelerometer.
  time = millis();
  double whiteLevel;
  for (int i = 0; i < NUM_PIXELS; i++) {
    double diff = time - stripArr[i]; //Time always >= set stripArrs
    if(diff < (double)onTime / 2) { //Increase brightness
      whiteLevel = diff / ((double)onTime / 2) * 255;
    } else { //Decrease
      whiteLevel = ((double)onTime - diff) / ((double)onTime / 2) * 255;
    }
    if (whiteLevel < 0) {
      whiteLevel = 0;
    }
    strip.setPixelColor(i, strip.Color((int)whiteLevel, (int)whiteLevel, (int)whiteLevel));
    if (diff >= onTime) { //Reset after a full cycle
      stripArr[i] = time;
    }
  }
  strip.show();
  delay(100); //This should be kept constant
}
