#include <Process.h>
#include <Bridge.h>
#include <FastLED.h>

#define NUM_LEDS 512
#define DATA_PIN 2
#define MIC 0
#define MAX_BRIGHTNESS 20

char D13value[3];
CRGB leds[NUM_LEDS];
Process p;

void l3dSetup() {
  pinMode(MIC, INPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.showColor(CRGB::Black);
}

void setup() {
  l3dSetup();
  
  memset(D13value, 0, 3);
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  Bridge.begin();
}

void loop() {
  runPython();
  Bridge.get("D13", D13value, 3);
  int D13int = atoi(D13value);
  if (D13int >= 0 && D13int < NUM_LEDS) {
    leds[D13int] = CRGB(255, 255, 0);
    FastLED.show();
  }
}

void runPython() {
  // p.runShellCommand("/etc/init.d/l3d stop");
  p.runShellCommand("/etc/init.d/l3d start");
}

