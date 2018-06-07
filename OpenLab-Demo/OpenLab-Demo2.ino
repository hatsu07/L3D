#include <Process.h>
#include <FastLED.h>
#include <avr/pgmspace.h>
#include "picture.h"

const uint16_t NUM_LEDS = 512;
const uint8_t DATA_PIN = 2;
const uint8_t MAX_BRIGHTNESS = 20;
const uint8_t BUFLEN = 2;
const uint16_t Threshold = 5000;

CRGB leds[NUM_LEDS];
uint8_t oldval;
uint16_t count;
char cval[BUFLEN];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.showColor(CRGB::Black);

  for (uint8_t x = 0; x < 8; x++) {
    for (uint8_t y = 0; y < 8; y++) {
      for (uint8_t z = 0; z < 8; z++) {
        led(x, y, z) = CRGB(x * 32, y * 32, z * 32);
      }
    }
  }
  FastLED.show();

  Bridge.begin(); // arduinoとlinuxの通信準備

  memset(cval, 0, BUFLEN);
  runPython();
  oldval = 0;
  count = 0;
}

void loop() {
  Bridge.get("v", cval, BUFLEN);

  uint8_t val = atoi(cval);

  if (oldval == val) {
    if (count > Threshold) {
      Bridge.get("n", cval, BUFLEN);
      int num = atoi(cval);

      if (num > 0) {
        drawNumber(num);
      } else {
        val = random(1, 5);
        if (val == 1) {
          for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, y, z) = CRGB(255, 0, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
          for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, y, z) = CRGB(0, 0, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
        } else if (val == 2) {
          for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(7 - x, y, z) = CRGB(0, 255, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
          for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(7 - x, y, z) = CRGB(0, 0, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
        } else if (val == 3) {
          for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, y, z) = CRGB(0, 0, 255);
              }
            }
            FastLED.show();
            delay(50);
          }
          for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, y, z) = CRGB(0, 0, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
        } else if (val == 4) {
          for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, 7 - y, z) = CRGB(255, 255, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
          for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, 7 - y, z) = CRGB(0, 0, 0);
              }
            }
            FastLED.show();
            delay(50);
          }
        } else {
          for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
              for (uint8_t z = 0; z < 8; z++) {
                led(x, y, z) = CRGB(x * 32, y * 32, z * 32);
              }
            }
          }
          FastLED.show();
        }
        delay(500);
      }
    } else {
      count++;
    }
  } else {
    count = 0;
    if (val == 1) {
      for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 8; y++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, y, z) = CRGB(255, 0, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
      for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 8; y++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, y, z) = CRGB(0, 0, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
    } else if (val == 2) {
      for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 8; y++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(7 - x, y, z) = CRGB(0, 255, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
      for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 8; y++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(7 - x, y, z) = CRGB(0, 0, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
    } else if (val == 3) {
      for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, y, z) = CRGB(0, 0, 255);
          }
        }
        FastLED.show();
        delay(50);
      }
      for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, y, z) = CRGB(0, 0, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
    } else if (val == 4) {
      for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, 7 - y, z) = CRGB(255, 255, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
      for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, 7 - y, z) = CRGB(0, 0, 0);
          }
        }
        FastLED.show();
        delay(50);
      }
    } else if (val == 5) {
      for (uint8_t x = 0; x < 8; x++) {
        for (uint8_t y = 0; y < 8; y++) {
          for (uint8_t z = 0; z < 8; z++) {
            led(x, y, z) = CRGB(255, 255, 255);
          }
        }
      }
      FastLED.show();
    }
    oldval = val;
  }
}

// 3次元座標からLED番号を返す
CRGB& led(uint8_t x, uint8_t y, uint8_t z) {
  return leds[7 - x + (7 - y) * 8 + (7 - z) * 64];
}

// 番号表示
void drawNumber(uint8_t n) {
  FastLED.clear();
  if (n == 1) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(One + i) == 1) {
        leds[511 - i] = CRGB(255, 0, 0);
      }
    }
  } else if (n == 2) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(Two + i) == 1) {
        leds[511 - i] = CRGB(0, 0, 255);
      }
    }
  } else if (n == 3) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(Three + i) == 1) {
        leds[511 - i] = CRGB(0, 255, 0);
      }
    }
  } else if (n == 4) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(Four + i) == 1) {
        leds[511 - i] = CRGB(255, 255, 0);
      }
    }
  } else if (n == 5) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(Five + i) == 1) {
        leds[511 - i] = CRGB(255, 0, 255);
      }
    }
  } else if (n == 6) {
    for (uint8_t i = 0; i < 64; i++) {
      if (pgm_read_byte_near(Six + i) == 1) {
        leds[511 - i] = CRGB(0, 255, 255);
      }
    }
  }
  FastLED.show();
}

void runPython() {
  Process p;
  p.runShellCommand("sh /mnt/receive.sh");
}

