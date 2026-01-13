/**
 * TimeManager.h - Time and Sunrise/Sunset Calculator
 *
 * Manages time synchronization and calculates time of day periods
 * including dawn, sunrise, day, sunset, dusk, and night
 */

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include <time.h>
#include "config.h"

// Duration of transition periods in minutes
#define DAWN_DURATION 30      // Dawn lasts 30 minutes before sunrise
#define SUNRISE_DURATION 20   // Sunrise period lasts 20 minutes
#define SUNSET_DURATION 20    // Sunset period lasts 20 minutes
#define DUSK_DURATION 30      // Dusk lasts 30 minutes after sunset

class TimeManager {
  private:
    time_t sunriseTime;
    time_t sunsetTime;
    time_t lastTimeUpdate;
    bool timeInitialized;

    // Calculate sunrise and sunset times using solar position algorithm
    void calculateSunTimes();

    // Convert time_t to hour and minute
    void timeToHourMin(time_t t, int &hour, int &minute);

  public:
    TimeManager();

    // Initialize time sync with NTP server
    void begin();

    // Update time (call regularly)
    void update();

    // Get current time of day period
    TimeOfDay getTimeOfDay();

    // Get sunrise time (time_t)
    time_t getSunriseTime();

    // Get sunset time (time_t)
    time_t getSunsetTime();

    // Get current time string
    String getCurrentTimeString();

    // Check if time is initialized
    bool isTimeInitialized();
};

#endif // TIME_MANAGER_H
