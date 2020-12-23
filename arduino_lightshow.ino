#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    52


CRGB COLORS [] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::BlueViolet};
#define NUM_COLORS 4

CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void crawl() {
  for (int i = 0; i < NUM_COLORS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = COLORS[i];
      FastLED.show();
      delay(25);
    }
  }
}

CRGB random_color() {
  byte r, g, b;
  r = random(256);
  g = random(256);
  b = random(256);
  return CRGB(r, g, b);
}

void random_show() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = random_color();
    FastLED.show();
    //delay(10);
  }
}

void christmas() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB:Red
    FastLED.show();
  }
}

void loop() {
  crawl();
}
