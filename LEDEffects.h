/**
 * LEDEffects.h - LED Strip Effects Manager
 *
 * Manages LED strip animations for different weather conditions
 */

#ifndef LED_EFFECTS_H
#define LED_EFFECTS_H

#include <Arduino.h>
#include <FastLED.h>
#include "config.h"

class LEDEffects {
  private:
    CRGB leds[NUM_LEDS];
    WeatherCondition currentWeather;
    TimeOfDay currentTimeOfDay;
    unsigned long animationStep;

    // Effect functions for each weather type
    void effectClear();
    void effectCloudy();
    void effectPartlyCloudy();
    void effectRain();
    void effectStorm();
    void effectSnow();
    void effectFog();
    void effectError();

    // Helper functions for color calculation
    CRGB getSunColor();          // Get sun color based on time of day
    CRGB getCloudColor();        // Get cloud color based on time of day
    uint8_t getAmbientBrightness();  // Get brightness based on time of day

    // Animation helpers
    void fadeToColor(CRGB color, uint8_t fadeAmount);
    void twinkle(CRGB baseColor, int numSparkles);

  public:
    LEDEffects();

    // Initialize LED strip
    void begin();

    // Set weather effect based on condition and time of day
    void setWeatherEffect(WeatherCondition weather, TimeOfDay tod);

    // Update animation (call regularly for smooth animations)
    void update();

    // Show error pattern
    void showError();

    // Clear all LEDs
    void clear();
};

#endif // LED_EFFECTS_H
