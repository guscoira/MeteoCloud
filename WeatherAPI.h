/**
 * WeatherAPI.h - Weather API Handler
 *
 * Handles fetching and parsing weather forecast data from external API
 */

#ifndef WEATHER_API_H
#define WEATHER_API_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

class WeatherAPI {
  private:
    WeatherCondition currentCondition;
    float temperature;
    int humidity;
    String description;
    unsigned long lastFetchTime;
    bool dataValid;

    // Helper function to parse API response and determine weather condition
    WeatherCondition parseCondition(const String& apiCondition);

  public:
    WeatherAPI();

    // Initialize the weather API client
    void begin();

    // Fetch weather forecast for next 3 hours
    bool fetchForecast();

    // Get current weather condition
    WeatherCondition getCurrentCondition();

    // Get temperature
    float getTemperature();

    // Get humidity
    int getHumidity();

    // Get weather description
    String getDescription();

    // Check if data is valid
    bool isDataValid();

    // Convert condition enum to readable string
    String getConditionName(WeatherCondition condition);
};

#endif // WEATHER_API_H
