// use the library manager to install the neopixel library
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
  // includes the library

#define PIXEL_PIN 4
  // defines the digital pin that the LED strip is connected to

#define NUM_PIXELS 24
  // defines the number of neopixels in the strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
  // declares a neopixel object for the strip

int flow_start = 0;
int flow_end = flow_start + 8;

const int DELAY_MIN = 10;
const int DELAY_MAX = 1200;

#define POT_PIN A0
  // defines the analog pin that the potentiometer is connected to
const int POT_MID = 600;
const int POT_THRESH_1 = 400;
const int POT_THRESH_2 = 800;
  // stores the max and min values of the potentiometer shown on the 
  // serial monitor for mapping purposes

#define PHOTO_PIN A2
  // defines the analog pin that the photoresistor is connected to
const int PHOTO_MAX = 650;
const int PHOTO_MIN = 1023;

void setup() { 
  Serial.begin(9600); // begin serial monitor

  strip.begin(); // we always need to do this
  strip.show(); // initialize strip off
  
  pinMode(POT_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
    // initilaizes switch and button pins as input
}

int checkPixelLimit(int x) {
  if (x >= NUM_PIXELS) {
      x = x - NUM_PIXELS;
  }
  if (x < 0) {
    x = NUM_PIXELS + x;
  }
  return x; 
}

// lights the neopixels one after the other with specified color
void wipeOut(uint32_t c, uint8_t wait) {
  flow_start = checkPixelLimit(flow_start);
  flow_end = checkPixelLimit(flow_end);
  for(uint16_t i=0; i<NUM_PIXELS; i++) {
    if (flow_start < flow_end) {
      if (i >= flow_start && i <= flow_end) {
        strip.setPixelColor(i, c);
      }
      else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
    else {
      if (i >= flow_start || i <= flow_end) {
        strip.setPixelColor(i, c);
      }
      else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
  }
  strip.show();
  delay(wait);
  flow_start++;
  flow_end++;
}

// lights the neopixels one after the other with specified color
void wipeIn(uint32_t c, uint8_t wait) {
  flow_start = checkPixelLimit(flow_start);
  flow_end = checkPixelLimit(flow_end);
  for(uint16_t i=0; i<NUM_PIXELS; i++) {
    if (flow_start < flow_end) {
      if (i >= flow_start && i <= flow_end) {
        strip.setPixelColor(i, c);
      }
      else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
    else {
      if (i >= flow_start || i <= flow_end) {
        strip.setPixelColor(i, c);
      }
      else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
  }
  strip.show();
  delay(wait);
  flow_start--;
  flow_end--;
}

// turns off all neopixels
void endShow() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

// makes neopixels point to specific element
void pixelPoint(int timeless, uint32_t c) {

  int pixelRangeMin = timeless*3;
  int pixelRangeMax = (timeless*3) + 3;
  
  //string timeless = "ace";
  for(int i=pixelRangeMin; i<pixelRangeMax; i++) {
    strip.setPixelColor(i,c);
  }
  for(int i=pixelRangeMax; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  for (int i=0; i<pixelRangeMin; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void loop() {
  int pot_val = analogRead(POT_PIN);
  int photo_val = analogRead(PHOTO_PIN);
  
  /*Serial.print("pot val: ");
  Serial.println(pot_val);
  Serial.print("photo val: ");
  Serial.println(photo_val);*/
  
  int speed_val = map(photo_val, PHOTO_MIN, PHOTO_MAX, DELAY_MIN, DELAY_MAX);
  
  uint32_t r_mode = strip.Color(200, 0, 55);
  uint32_t g_mode = strip.Color(55, 200, 0);
  uint32_t b_mode = strip.Color(55, 0, 200);
  uint32_t mode;

  int spade = 0;
  int dice = 1;
  int club = 2;
  int eye = 3;
  int heart = 4;
  int mush = 5;
  int diamond = 6;
  int hand = 7;
  int timeless;

 /* if (pot_val <= POT_THRESH_1) {
    mode = r_mode;
  }
  else if (pot_val <= POT_THRESH_2) {
    mode = g_mode;
  }
  else {
    mode = b_mode;
  }*/

  if (photo_val <= 800) {
    mode = r_mode;
  }
  else if (photo_val <= 950) {
    mode = g_mode;
  }
  else {
    mode = b_mode;
  }

  if (pot_val <= 300) {
    timeless = spade;
  }
  else if (pot_val <= 400) {
    timeless = dice;
  }
  else if (pot_val <= 500) {
    timeless = club;    
  }
  else if (pot_val <= 600) {
    timeless = eye;    
  }
  else if (pot_val <= 700) {
    timeless = heart;    
  }
  else if (pot_val <= 800) {
    timeless = mush;    
  }
  else if (pot_val <= 900) {
    timeless = diamond;    
  }
  else {
    timeless = hand;    
  }

  pixelPoint(timeless, mode);

  Serial.print(photo_val/4);
  Serial.print(',');
  Serial.println(timeless);
  
  /*if (pot_val >= POT_MID) {
    wipeOut(mode, speed_val);
  }
  else {
    wipeIn(mode, speed_val);
  }*/

  
}
