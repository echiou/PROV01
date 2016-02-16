#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 16
#define NP_PIN 6
#define POT1_PIN A1

#define Y_INPUT A5

#define COL_TWO 4
#define COL_THREE 8
#define COL_FOUR 12

// Neopixel Randomness
unsigned long time; //Keep track of the time
unsigned long stripArr[NUM_PIXELS]; //Time data for strip (when to turn them on/off, etc.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int onTime = 1500; // How long light is on
long randOn = 50; // ~5% of cycles, turn on random pixel

// Potentiometer & Colors
int val1; // Value of first pot
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int purple[3] = {255, 0, 255};
int red[3] = {255, 0, 0};
int yellow[3] = {255, 255, 0};

// Accelerometer Things
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis
int yRawMin = 512;
int yRawMax = 512;
 
// Take multiple samples to reduce noise
const int sampleSize = 10;
 
void setup() {
  memset(stripArr, 0, sizeof(stripArr));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
  Serial.println("Serial Up");
  
  onTime = 1500;
}

void loop() {
  // Find the Acceleration
  int yRaw = ReadAxis(Y_INPUT);
  
  AutoCalibrate(yRaw);
  
  // Convert raw values to 'milli-Gs"
  long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);

  // re-scale to fractional Gs
  float yAccel = yScaled / 1000.0;

  
  // Light Control
  onTime += (int)(50 * yAccel); //We'll change this when we get an accelerometer.
  if (onTime < 500) {
    onTime = 500;
  }
  else if (onTime > 2500) {
    onTime = 2500;
  }
  // Debugging
//  Serial.println(yAccel);
//  Serial.println(onTime);
//  Serial.println();
  randOn = 50; //This should also shift with accelerometer maybe.
  time = millis();

  val1 = analogRead(POT1_PIN); // value for first potentiometer
  double ratio1 = (double) (val1 / 1023.0); // used to determine position between hues

  double brightness;
  for (int i = 0; i < NUM_PIXELS; i++) {
    double diff = time - stripArr[i]; //Time always >= set stripArrs
    double halfOnTime = (double)onTime / 2;
    if (diff < halfOnTime) { //Increase brightness
      brightness = diff / (halfOnTime) * 255;
    } else if  (diff >= halfOnTime && diff < onTime) { //Decrease
      brightness = ((double)onTime - diff) / (halfOnTime) * 255;
    }
    else {
      brightness = NULL;
      if (random(0, 1000) < randOn) {
        stripArr[i] = time;
      }
    }
    if (brightness) {
      if (brightness < 20) {
        brightness = 20;
      }
      //TODO: This should probably be less jank as well
      if (i < COL_TWO) {
        int ratio = ratio1;
      } else if (i < COL_THREE) {
        int ratio = ratio1; // should be ratio2
      } else if (i < COL_FOUR) {
        int ratio = ratio1; // should be ratio3
      } else { // i >= COL_FOUR
        int ratio = ratio1; // should be ratio4
      }
      setColor(i, ratio1, brightness); // TODO: Currently only uses ratio1
    }
    else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();
  delay(50); //This should be kept constant
}

void setColor(int ledNum, double ratio, double brightness) {
  byte redVal = 0;
  byte greenVal = 0;
  byte blueVal = 0;

  // TODO: make this less jank
  if (ledNum < COL_TWO) {
    redVal = (green[0] * ratio) + (blue[0] * (1 - ratio));
    greenVal = (green[1] * ratio) + (blue[1] * (1 - ratio));
    blueVal = (green[2] * ratio) + (blue[2] * (1 - ratio));
  } else if (ledNum < COL_THREE) {
    redVal = (blue[0] * ratio) + (purple[0] * (1 - ratio));
    greenVal = (blue[1] * ratio) + (purple[1] * (1 - ratio));
    blueVal = (blue[2] * ratio) + (purple[2] * (1 - ratio));
  } else if (ledNum < COL_FOUR) {
    redVal = (purple[0] * ratio) + (red[0] * (1 - ratio));
    greenVal = (purple[1] * ratio) + (red[1] * (1 - ratio));
    blueVal = (purple[2] * ratio) + (red[2] * (1 - ratio));
  } else { // ledNum >= COL_FOUR
    redVal = (red[0] * ratio) + (yellow[0] * (1 - ratio));
    greenVal = (red[1] * ratio) + (yellow[1] * (1 - ratio));
    blueVal = (red[2] * ratio) + (yellow[2] * (1 - ratio));
  }

  int rAdjusted = redVal * brightness / 255;
  int gAdjusted = greenVal * brightness / 255;
  int bAdjusted = blueVal * brightness / 255;

  strip.setPixelColor(ledNum, rAdjusted, gAdjusted, bAdjusted);
}

//
// Read "sampleSize" samples and report the average
//
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
 
//
// Find the extreme raw readings from each axis
//
void AutoCalibrate(int yRaw)
{
  Serial.println("Calibrate");
  if (yRaw < yRawMin)
  {
    yRawMin = yRaw;
  }
  if (yRaw > yRawMax)
  {
    yRawMax = yRaw;
  }
}
