/**
 * WeatherAPI.cpp - Weather API Handler Implementation
 */

#include "WeatherAPI.h"

WeatherAPI::WeatherAPI() {
  currentCondition = UNKNOWN;
  temperature = 0.0;
  humidity = 0;
  description = "";
  lastFetchTime = 0;
  dataValid = false;
}

void WeatherAPI::begin() {
  DEBUG_PRINTLN("Weather API initialized");
}

bool WeatherAPI::fetchForecast() {
  if (WiFi.status() != WL_CONNECTED) {
    DEBUG_PRINTLN("WiFi not connected, cannot fetch weather");
    dataValid = false;
    return false;
  }

  HTTPClient http;

  // TODO: Construct proper API URL based on chosen weather service
  // Example for OpenWeatherMap:
  // String url = String(WEATHER_API_URL) + "?lat=" + String(LATITUDE) +
  //              "&lon=" + String(LONGITUDE) + "&appid=" + WEATHER_API_KEY;

  String url = String(WEATHER_API_URL);
  DEBUG_PRINT("Fetching from: ");
  DEBUG_PRINTLN(url);

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DEBUG_PRINTLN("Weather data received");

    // Parse JSON response
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      DEBUG_PRINT("JSON parsing failed: ");
      DEBUG_PRINTLN(error.c_str());
      http.end();
      dataValid = false;
      return false;
    }

    // TODO: Parse actual API response structure
    // This is a placeholder - adapt to your chosen weather API
    /*
    // Example for OpenWeatherMap:
    temperature = doc["main"]["temp"];
    humidity = doc["main"]["humidity"];
    String weatherMain = doc["weather"][0]["main"];
    description = doc["weather"][0]["description"];
    currentCondition = parseCondition(weatherMain);
    */

    // For now, set to unknown until API is configured
    currentCondition = UNKNOWN;
    dataValid = true;
    lastFetchTime = millis();

    http.end();
    return true;

  } else {
    DEBUG_PRINT("HTTP request failed, code: ");
    DEBUG_PRINTLN(httpCode);
    http.end();
    dataValid = false;
    return false;
  }
}

WeatherCondition WeatherAPI::parseCondition(const String& apiCondition) {
  // TODO: Map API-specific condition codes to our enum
  // This example shows OpenWeatherMap mapping:

  String condition = apiCondition;
  condition.toLowerCase();

  if (condition.indexOf("clear") >= 0) {
    return CLEAR;
  } else if (condition.indexOf("cloud") >= 0) {
    if (condition.indexOf("few") >= 0 || condition.indexOf("scatter") >= 0) {
      return PARTLY_CLOUDY;
    }
    return CLOUDY;
  } else if (condition.indexOf("thunder") >= 0 || condition.indexOf("storm") >= 0) {
    return STORM;
  } else if (condition.indexOf("rain") >= 0 || condition.indexOf("drizzle") >= 0) {
    return RAIN;
  } else if (condition.indexOf("snow") >= 0) {
    return SNOW;
  } else if (condition.indexOf("fog") >= 0 || condition.indexOf("mist") >= 0) {
    return FOG;
  }

  return UNKNOWN;
}

WeatherCondition WeatherAPI::getCurrentCondition() {
  return currentCondition;
}

float WeatherAPI::getTemperature() {
  return temperature;
}

int WeatherAPI::getHumidity() {
  return humidity;
}

String WeatherAPI::getDescription() {
  return description;
}

bool WeatherAPI::isDataValid() {
  return dataValid;
}

String WeatherAPI::getConditionName(WeatherCondition condition) {
  switch (condition) {
    case CLEAR: return "Clear";
    case CLOUDY: return "Cloudy";
    case PARTLY_CLOUDY: return "Partly Cloudy";
    case RAIN: return "Rain";
    case STORM: return "Storm";
    case SNOW: return "Snow";
    case FOG: return "Fog";
    default: return "Unknown";
  }
}
