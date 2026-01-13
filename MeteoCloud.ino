/**
 * MeteoCloud - Weather Forecast LED Display
 *
 * An Arduino-based system that visualizes 3-hour weather forecasts
 * using an addressable LED strip with dynamic color patterns.
 *
 * Hardware: ESP32/ESP8266 with WS2812B LED strip
 */

#include "config.h"
#include "WeatherAPI.h"
#include "LEDEffects.h"
#include "TimeManager.h"

// Global objects
WeatherAPI weatherAPI;
LEDEffects ledEffects;
TimeManager timeManager;

// Timing variables
unsigned long lastWeatherUpdate = 0;
unsigned long lastEffectUpdate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== MeteoCloud Starting ===");

  // Initialize LED strip
  ledEffects.begin();
  Serial.println("LED strip initialized");

  // Connect to WiFi
  connectWiFi();

  // Initialize time management
  timeManager.begin();
  Serial.println("Time manager initialized");

  // Initialize weather API
  weatherAPI.begin();
  Serial.println("Weather API initialized");

  // Initial weather fetch
  updateWeather();

  Serial.println("=== Setup Complete ===\n");
}

void loop() {
  unsigned long currentMillis = millis();

  // Update weather data periodically (every WEATHER_UPDATE_INTERVAL)
  if (currentMillis - lastWeatherUpdate >= WEATHER_UPDATE_INTERVAL) {
    updateWeather();
    lastWeatherUpdate = currentMillis;
  }

  // Update LED effects (runs at ~60 FPS for smooth animations)
  if (currentMillis - lastEffectUpdate >= EFFECT_UPDATE_INTERVAL) {
    ledEffects.update();
    lastEffectUpdate = currentMillis;
  }

  // Update time (for sunrise/sunset calculations)
  timeManager.update();
}

void connectWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed!");
  }
}

void updateWeather() {
  Serial.println("Fetching weather data...");

  if (weatherAPI.fetchForecast()) {
    WeatherCondition condition = weatherAPI.getCurrentCondition();
    String conditionName = weatherAPI.getConditionName(condition);

    Serial.print("Current weather: ");
    Serial.println(conditionName);

    // Update LED effect based on weather condition and time of day
    TimeOfDay tod = timeManager.getTimeOfDay();
    ledEffects.setWeatherEffect(condition, tod);
  } else {
    Serial.println("Failed to fetch weather data");
    // Show error pattern on LEDs
    ledEffects.showError();
  }
}
