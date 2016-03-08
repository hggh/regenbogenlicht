/*
 * Copyright: 2016 Jonas Genannt <genannt@debian.org>
 */
#include "FastLED.h"

#define LED_COUNT 12
#define LED_PIN 6

CRGB leds[LED_COUNT];
uint8_t led_brightness = 60;
static uint8_t hue = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Regenbogen");
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(led_brightness);
  for (uint8_t i = 0; i < 1; i++) {
    for (uint8_t dot = 0; dot < LED_COUNT; dot++) {
      leds[dot] = CRGB::Blue;
      FastLED.show();
      delay(20);
      leds[dot + 1] = CRGB::Red;
      FastLED.show();
      delay(20);
    }
  }
}

void loop() {
  randomSeed(millis());
  int wait = random(40, 60);
  
  fill_rainbow( leds, LED_COUNT,hue++, 5);
  FastLED.show();
  delay(wait);
}
