#include <Bounce2.h>
#include <FastLED.h>

#include "colors.h"

#define PIN_SWITCH 9
#define PIN_RT_DT 2
#define PIN_RT_CLK 3
#define PIN_LED 5
#define LED_COUNT 12
#define MODE_RAINBOW 1
#define MODE_ONE_COLOR 2

Bounce button = Bounce();
CRGB leds[LED_COUNT];

volatile uint8_t clk_current = 0;
volatile uint8_t clk_last = 0;
volatile uint8_t led_brightness = 60;
volatile uint8_t color_index = 0;
volatile uint8_t rainbow_speed = 20;
static uint8_t hue = 0;

volatile uint8_t active_mode = MODE_RAINBOW;
unsigned long last_time_update = 0;


void rt_int_clk() {
  clk_last = clk_current;
  clk_current = digitalRead(PIN_RT_CLK);

  if (clk_last != clk_current) {
    if (digitalRead(PIN_RT_DT) != clk_current) {
      if (active_mode == MODE_ONE_COLOR) {
        color_index += 1;
        if (color_index > 34) {
          color_index = 0;
        }
      }
      else {
        rainbow_speed += 3;
        if (rainbow_speed > 70) {
          rainbow_speed = 20;
        }
      }
    }
    else {
      led_brightness += 5;
      if (led_brightness < 10) {
        led_brightness = 240;
      }
      if (led_brightness > 240) {
        led_brightness = 10;
      }
      FastLED.setBrightness(led_brightness);
    }
  }
}


void setup() {
  Serial.begin(9600);

  pinMode(PIN_SWITCH, INPUT_PULLUP);
  button.attach(PIN_SWITCH);
  button.interval(25);

  pinMode(PIN_RT_CLK, INPUT);
  pinMode(PIN_RT_DT, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_RT_CLK), rt_int_clk, CHANGE);

  FastLED.addLeds<NEOPIXEL, PIN_LED>(leds, LED_COUNT);
  FastLED.setBrightness(led_brightness);
}

void loop() {
  button.update();

  if (button.fell()) {
    Serial.println("Button pressed");
    if (active_mode == MODE_RAINBOW) {
      active_mode = MODE_ONE_COLOR;
    }
    else {
      active_mode = MODE_RAINBOW;
    }
  }

  if (active_mode == MODE_RAINBOW) {
    if (millis() - last_time_update >= rainbow_speed) {
      last_time_update = millis();
      fill_rainbow(leds, LED_COUNT, hue++, 5);
    }
  }
  else {
    fill_solid(leds, LED_COUNT, colors[color_index]);
  }
  FastLED.show();
}
