#include <FastLED.h>
#define LED_PIN     7
/* #define NUM_LEDS    52 */
#define NUM_LEDS    20
#define NUM_COLORS 3
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define BRIGHTNESS  100
#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];
CRGB COLORS [] = {CRGB::Red, CRGB::White, CRGB::Green};
CRGB HeatColor( uint8_t temperature);


void setup() {
    delay(1000);
    FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
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
  r = random8();
  g = random8();
  b = random8();
  return CRGB(r, g, b);
}

void random_show() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = random_color();
    FastLED.show();
    /* //delay(10); */
  }
}

void christmas() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  christmas()
  FastLED.show(); // display this frame

  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// CRGB HeatColor( uint8_t temperature)
// [to be included in the forthcoming FastLED v2.1]
//
// Approximates a 'black body radiation' spectrum for
// a given 'heat' level.  This is useful for animations of 'fire'.
// Heat is specified as an arbitrary scale from 0 (cool) to 255 (hot).
// This is NOT a chromatically correct 'black body radiation'
// spectrum, but it's surprisingly close, and it's extremely fast and small.
//
// On AVR/Arduino, this typically takes around 70 bytes of program memory,
// versus 768 bytes for a full 256-entry RGB lookup table.

CRGB HeatColor( uint8_t temperature)
{
  CRGB heatcolor;

  // Scale 'heat' down from 0-255 to 0-191,
  // which can then be easily divided into three
  // equal 'thirds' of 64 units each.
  uint8_t t192 = scale8_video( temperature, 192);

  // calculate a value that ramps up from
  // zero to 255 in each 'third' of the scale.
  uint8_t heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // now figure out which third of the spectrum we're in:
  if( t192 & 0x80) {
    // we're in the hottest third
    heatcolor.r = 255; // full red
    heatcolor.g = 255; // full green
    heatcolor.b = heatramp; // ramp up blue

  } else if( t192 & 0x40 ) {
    // we're in the middle third
    heatcolor.r = 255; // full red
    heatcolor.g = heatramp; // ramp up green
    heatcolor.b = 0; // no blue

  } else {
    // we're in the coolest third
    heatcolor.r = heatramp; // ramp up red
    heatcolor.g = 0; // no green
    heatcolor.b = 0; // no blue
  }

  return heatcolor;
}
