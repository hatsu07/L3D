#include <FastLED.h>

#define NUM_LEDS 512
#define DATA_PIN 2
#define MIC 0
#define X 1
#define Y 2
#define Z 3
#define MAX_BRIGHTNESS 20

CRGB leds[NUM_LEDS];

CRGB& led(uint8_t x, uint8_t y, uint8_t z) {
  return leds[y + x*8 + (7-z) * 64];
}

CRGB setColor(uint8_t y) {
  switch(y) {
    case 0:
      return CRGB(128, 0, 128);
    case 1:
      return CRGB(0, 0, 255);
    case 2:
      return CRGB(0, 255, 255);
    case 3:
      return CRGB(0, 128, 0);
    case 4:
      return CRGB(128, 255, 0);
    case 5:
      return CRGB(255, 255, 0);
    case 6:
      return CRGB(255, 165, 0);
    case 7:
      return CRGB(255, 0, 0);
    default:
      return CRGB(0, 0, 0);
  }
}

void setup() {
  pinMode(MIC, INPUT);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(Z, INPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.showColor(CRGB::Black);
}

void loop() {
  int x, y, z;
  int mic = analogRead(MIC);
  int accx = analogRead(X);
  int accy = analogRead(Y);
  int accz = analogRead(Z);

  mic = abs(512 - mic);

  mic = mic / 16;

  for (x = 0; x < 8; x++) {
    for (y = 0; y < 8; y++) {
      for (z = 0; z < 8; z++) {
        if (y + 8 < mic) {
          led(x, y, z) = setColor(y);
        } else {
          led(x, y, z) = CRGB(0, 0, 0);
        }
      }
    }
  }
  FastLED.show();
}

