/**
 * TimeManager.cpp - Time and Sunrise/Sunset Calculator Implementation
 */

#include "TimeManager.h"

TimeManager::TimeManager() {
  sunriseTime = 0;
  sunsetTime = 0;
  lastTimeUpdate = 0;
  timeInitialized = false;
}

void TimeManager::begin() {
  // Configure time with NTP
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

  DEBUG_PRINT("Waiting for time sync");
  int attempts = 0;
  while (!time(nullptr) && attempts < 20) {
    DEBUG_PRINT(".");
    delay(500);
    attempts++;
  }
  DEBUG_PRINTLN();

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    DEBUG_PRINTLN("Time synchronized!");
    DEBUG_PRINT("Current time: ");
    DEBUG_PRINTLN(getCurrentTimeString());
    timeInitialized = true;
    calculateSunTimes();
  } else {
    DEBUG_PRINTLN("Failed to obtain time");
    timeInitialized = false;
  }
}

void TimeManager::update() {
  time_t now = time(nullptr);

  // Recalculate sun times once per day (at midnight)
  if (now - lastTimeUpdate > 86400 || lastTimeUpdate == 0) {
    calculateSunTimes();
    lastTimeUpdate = now;
  }
}

TimeOfDay TimeManager::getTimeOfDay() {
  if (!timeInitialized) {
    return DAY;  // Default to day if time not initialized
  }

  time_t now = time(nullptr);

  // Calculate time boundaries for each period
  time_t dawnStart = sunriseTime - (DAWN_DURATION * 60);
  time_t sunriseEnd = sunriseTime + (SUNRISE_DURATION * 60);
  time_t sunsetEnd = sunsetTime + (SUNSET_DURATION * 60);
  time_t duskEnd = sunsetTime + ((SUNSET_DURATION + DUSK_DURATION) * 60);

  // Determine current time of day
  if (now >= dawnStart && now < sunriseTime) {
    return DAWN;
  } else if (now >= sunriseTime && now < sunriseEnd) {
    return SUNRISE;
  } else if (now >= sunriseEnd && now < sunsetTime) {
    return DAY;
  } else if (now >= sunsetTime && now < sunsetEnd) {
    return SUNSET;
  } else if (now >= sunsetEnd && now < duskEnd) {
    return DUSK;
  } else {
    return NIGHT;
  }
}

void TimeManager::calculateSunTimes() {
  // Simplified sunrise/sunset calculation
  // For more accuracy, consider using a library like sunset.h or daylightcalc
  //
  // This is a rough approximation based on location

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    DEBUG_PRINTLN("Failed to get local time for sun calculations");
    return;
  }

  // TODO: Implement proper sunrise/sunset calculation algorithm
  // For now, using approximate times (6:00 AM sunrise, 6:00 PM sunset)
  // Replace with actual solar position calculation

  // Create sunrise time for today at 6:00 AM
  struct tm sunrise = timeinfo;
  sunrise.tm_hour = 6;
  sunrise.tm_min = 0;
  sunrise.tm_sec = 0;
  sunriseTime = mktime(&sunrise);

  // Create sunset time for today at 6:00 PM
  struct tm sunset = timeinfo;
  sunset.tm_hour = 18;
  sunset.tm_min = 0;
  sunset.tm_sec = 0;
  sunsetTime = mktime(&sunset);

  DEBUG_PRINT("Calculated sunrise: ");
  timeToHourMin(sunriseTime, sunrise.tm_hour, sunrise.tm_min);
  DEBUG_PRINT(sunrise.tm_hour);
  DEBUG_PRINT(":");
  DEBUG_PRINTLN(sunrise.tm_min);

  DEBUG_PRINT("Calculated sunset: ");
  timeToHourMin(sunsetTime, sunset.tm_hour, sunset.tm_min);
  DEBUG_PRINT(sunset.tm_hour);
  DEBUG_PRINT(":");
  DEBUG_PRINTLN(sunset.tm_min);

  /*
   * NOTE: For accurate sunrise/sunset calculation, use a library like:
   * - sunset.h (https://github.com/buelowp/sunset)
   * - SolarCalculator (https://github.com/jpb10/SolarCalculator)
   *
   * Example with sunset.h:
   *
   * #include <sunset.h>
   * SunSet sun;
   * sun.setPosition(LATITUDE, LONGITUDE, GMT_OFFSET_SEC / 3600.0);
   * sun.setCurrentDate(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
   * double sunrise = sun.calcSunrise();
   * double sunset = sun.calcSunset();
   */
}

void TimeManager::timeToHourMin(time_t t, int &hour, int &minute) {
  struct tm *timeinfo = localtime(&t);
  hour = timeinfo->tm_hour;
  minute = timeinfo->tm_min;
}

time_t TimeManager::getSunriseTime() {
  return sunriseTime;
}

time_t TimeManager::getSunsetTime() {
  return sunsetTime;
}

String TimeManager::getCurrentTimeString() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Time not available";
  }

  char buffer[30];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buffer);
}

bool TimeManager::isTimeInitialized() {
  return timeInitialized;
}
