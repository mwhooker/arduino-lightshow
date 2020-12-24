#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    144
/* #define NUM_LEDS    20 */
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define BRIGHTNESS  75
#define FRAMES_PER_SECOND 1

CRGB leds[NUM_LEDS];
#define NUM_COLORS 4
CRGB COLORS [] = {CRGB::Red, CRGB::White, CRGB::Green, CRGB::Indigo};
CRGB HeatColor( uint8_t temperature);

CRGBPalette16 myPalette;

void setup() {
    delay(1000);
    FastLED.setCorrection(TypicalSMD5050);
    FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = HeatColor(i);
        FastLED.show(); // display this frame
    }
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

void christmasA() {
    // R G R G
    for (int i = 0; i < NUM_LEDS; i += 2) {
        leds[i] = CRGB::Red;
        leds[i + 1 ] = CRGB::Green;
    }
}

void christmasB() {
    // G R G R
    for (int i = 0; i < NUM_LEDS; i += 2) {
        leds[i] = CRGB::Green;
        leds[i + 1 ] = CRGB::Red;
    }
}

void christmas_loop() {
    for (int i = 0; i < 10 * FRAMES_PER_SECOND; i++) {
        // Add entropy to random number generator; we use a lot of it.
        random16_add_entropy( random());

        static bool xmas_state = false;
        if (xmas_state) {
            christmasA();
        } else {
            christmasB();
        }
        xmas_state ^= 1;

        FastLED.show(); // display this frame
        FastLED.delay(1000 / FRAMES_PER_SECOND);
    }
}

void loop() {

}
