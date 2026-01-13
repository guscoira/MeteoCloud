/**
 * LEDEffects.cpp - LED Strip Effects Implementation
 */

#include "LEDEffects.h"

LEDEffects::LEDEffects() {
  currentWeather = UNKNOWN;
  currentTimeOfDay = DAY;
  animationStep = 0;
}

void LEDEffects::begin() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  clear();
  FastLED.show();
  DEBUG_PRINTLN("LED strip initialized");
}

void LEDEffects::setWeatherEffect(WeatherCondition weather, TimeOfDay tod) {
  currentWeather = weather;
  currentTimeOfDay = tod;
  animationStep = 0;  // Reset animation
}

void LEDEffects::update() {
  animationStep++;

  switch (currentWeather) {
    case CLEAR:
      effectClear();
      break;
    case CLOUDY:
      effectCloudy();
      break;
    case PARTLY_CLOUDY:
      effectPartlyCloudy();
      break;
    case RAIN:
      effectRain();
      break;
    case STORM:
      effectStorm();
      break;
    case SNOW:
      effectSnow();
      break;
    case FOG:
      effectFog();
      break;
    default:
      effectError();
      break;
  }

  FastLED.show();
}

void LEDEffects::effectClear() {
  // Solid sun color based on time of day
  CRGB sunColor = getSunColor();
  fill_solid(leds, NUM_LEDS, sunColor);
}

void LEDEffects::effectCloudy() {
  // White/gray illumination with intensity based on time of day
  CRGB cloudColor = getCloudColor();

  // Gentle brightness variation to simulate cloud movement
  uint8_t wave = beatsin8(10, 200, 255);  // Slow wave between 200-255
  cloudColor.nscale8(wave);

  fill_solid(leds, NUM_LEDS, cloudColor);
}

void LEDEffects::effectPartlyCloudy() {
  // Mix of sun and cloud colors
  CRGB sunColor = getSunColor();
  CRGB cloudColor = getCloudColor();

  // Alternate sections between sun and cloud
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((i / 10 + animationStep / 50) % 2 == 0) {
      leds[i] = sunColor;
    } else {
      leds[i] = cloudColor;
    }
  }
}

void LEDEffects::effectRain() {
  // Blue falling droplets
  fadeToColor(CRGB(0, 0, 50), 10);  // Fade to dark blue

  // Create falling droplets every few frames
  if (animationStep % 3 == 0) {
    int pos = random(NUM_LEDS);
    leds[pos] = CRGB(50, 50, 255);  // Bright blue droplet
  }
}

void LEDEffects::effectStorm() {
  // Lightning flashes
  fadeToColor(CRGB(10, 10, 30), 20);  // Dark stormy blue

  // Random lightning strikes
  if (random(100) < 5) {  // 5% chance each frame
    // Flash all white
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
  } else if (random(100) < 3) {  // 3% chance for partial flash
    // Flash random section
    int start = random(NUM_LEDS - 10);
    for (int i = start; i < start + 10; i++) {
      leds[i] = CRGB(200, 200, 255);
    }
  }
}

void LEDEffects::effectSnow() {
  // Snowflakes falling - white sparkles moving down
  fadeToColor(CRGB(200, 200, 255), 15);  // Fade to light blue-white

  // Create falling snowflakes
  if (animationStep % 5 == 0) {
    int pos = random(NUM_LEDS);
    leds[pos] = CRGB(255, 255, 255);  // White snowflake
  }

  // Make some sparkle
  twinkle(CRGB(230, 230, 255), 2);
}

void LEDEffects::effectFog() {
  // Soft gray/white with slow wave
  uint8_t wave = beatsin8(5, 150, 230);  // Very slow wave
  CRGB fogColor = CRGB(wave, wave, wave);

  fill_solid(leds, NUM_LEDS, fogColor);
}

void LEDEffects::effectError() {
  // Red pulsing pattern to indicate error
  uint8_t pulse = beatsin8(30, 50, 200);
  fill_solid(leds, NUM_LEDS, CRGB(pulse, 0, 0));
}

CRGB LEDEffects::getSunColor() {
  // Return sun color based on time of day
  switch (currentTimeOfDay) {
    case NIGHT:
      return CRGB(0, 0, 0);  // No sun at night

    case DAWN:
      // Deep purple/blue transitioning to orange
      return CRGB(100, 50, 150);  // Purple-ish dawn

    case SUNRISE:
      // Orange/pink sunrise colors
      return CRGB(255, 100, 50);  // Orange-red

    case DAY:
      // Bright yellow sun
      return CRGB(255, 220, 100);  // Bright warm yellow

    case SUNSET:
      // Red/orange sunset colors
      return CRGB(255, 80, 20);  // Deep orange-red

    case DUSK:
      // Purple/pink dusk colors
      return CRGB(150, 50, 100);  // Purple-pink

    default:
      return CRGB(255, 255, 255);
  }
}

CRGB LEDEffects::getCloudColor() {
  // Return cloud color based on time of day (white with varying intensity)
  uint8_t brightness = getAmbientBrightness();
  return CRGB(brightness, brightness, brightness);
}

uint8_t LEDEffects::getAmbientBrightness() {
  // Return ambient brightness based on time of day
  switch (currentTimeOfDay) {
    case NIGHT:
      return 30;   // Very dim at night
    case DAWN:
      return 80;   // Low light during dawn
    case SUNRISE:
      return 150;  // Increasing light
    case DAY:
      return 255;  // Full brightness during day
    case SUNSET:
      return 150;  // Decreasing light
    case DUSK:
      return 80;   // Low light during dusk
    default:
      return 128;
  }
}

void LEDEffects::fadeToColor(CRGB color, uint8_t fadeAmount) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(fadeAmount);
    leds[i] += color;
  }
}

void LEDEffects::twinkle(CRGB baseColor, int numSparkles) {
  for (int i = 0; i < numSparkles; i++) {
    int pos = random(NUM_LEDS);
    leds[pos] = baseColor;
  }
}

void LEDEffects::showError() {
  currentWeather = UNKNOWN;  // Triggers error effect
}

void LEDEffects::clear() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
