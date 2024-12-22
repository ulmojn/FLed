#include <FastLED.h>

// Antal strips og antal LEDs per strip
#define NUM_STRIPS          12
#define NUM_LEDS_PER_STRIP  18

// Definér pins til de 12 strips (tilpas efter dine behov)
#define LED_PIN_STRIP_1   2
#define LED_PIN_STRIP_2   4
#define LED_PIN_STRIP_3   5
#define LED_PIN_STRIP_4   12
#define LED_PIN_STRIP_5   13
#define LED_PIN_STRIP_6   14
#define LED_PIN_STRIP_7   15
#define LED_PIN_STRIP_8   17
#define LED_PIN_STRIP_9   19
#define LED_PIN_STRIP_10  21
#define LED_PIN_STRIP_11  22
#define LED_PIN_STRIP_12  23

// Lysstyrke (0 - 255)
#define BRIGHTNESS 4

// Opret et todimensionelt array til dine LED-strips
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// Et array med de farver vi vil skifte imellem
CRGB colorCycle[] = {
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue
};

void setup() {
  // Initialiser hver enkelt strip
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_1 >(leds[0],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_2 >(leds[1],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_3 >(leds[2],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_4 >(leds[3],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_5 >(leds[4],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_6 >(leds[5],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_7 >(leds[6],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_8 >(leds[7],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_9 >(leds[8],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_10>(leds[9],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_11>(leds[10], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_12>(leds[11], NUM_LEDS_PER_STRIP);

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Holder styr på, hvilken farve i colorCycle der skal bruges
  static uint8_t colorIndex = 0;

  // Sæt alle LEDs på alle 12 strips til den aktuelle farve
  for(int strip = 0; strip < NUM_STRIPS; strip++) {
    fill_solid(leds[strip], NUM_LEDS_PER_STRIP, colorCycle[colorIndex]);
  }

  // Send farveopdatering til alle strips
  FastLED.show();

  // Vent 1 sekund
  delay(1000);

  // Skift til næste farve (rød -> grøn -> blå -> rød ...)
  colorIndex = (colorIndex + 1) % 3;
}