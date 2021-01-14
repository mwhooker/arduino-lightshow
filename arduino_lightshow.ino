#include <FastLED.h>
#define DATA_PIN    11
#define CLOCK_PIN   10
#define NUM_LEDS    30 * 5
#define COLOR_ORDER GRB
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

void setup() {
    delay(1000);
    FastLED.setCorrection(TypicalSMD5050);
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
}


#define O_REV 0
#define O_FWD 1


void larson_scan() {
    static bool order = O_FWD;
    static int index = 0;
    memset(leds, 0, NUM_LEDS * 3);
    leds[index] = CRGB::Red;

    if (index == 0) {
        order = O_FWD;
    } else if (index == NUM_LEDS-1) {
        order = O_REV;
    }

    if (order == O_FWD) {
        index++;
    } else {
        index--;
    }

    blur1d(leds, NUM_LEDS, 127);
}

void loop() {
    larson_scan();

    FastLED.show(); // display this frame
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}
