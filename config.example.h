/**
 * Configuration file for MeteoCloud
 *
 * Copy this file to config.h and update with your settings
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// WiFi Configuration
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// LED Strip Configuration
#define LED_PIN 5                    // GPIO pin connected to LED data line
#define NUM_LEDS 60                  // Number of LEDs in the strip
#define LED_TYPE WS2812B             // LED strip type (WS2812B, WS2811, etc.)
#define COLOR_ORDER GRB              // Color order (GRB for most WS2812B)
#define BRIGHTNESS 128               // Global brightness (0-255)

// Weather API Configuration
#define WEATHER_API_KEY "your_api_key_here"
#define WEATHER_API_URL "https://api.example.com/forecast"  // TBD: API provider
#define LATITUDE 40.7128             // Your location latitude
#define LONGITUDE -74.0060           // Your location longitude
#define WEATHER_UPDATE_INTERVAL 600000  // Update every 10 minutes (milliseconds)

// Effect Update Rate
#define EFFECT_UPDATE_INTERVAL 16    // ~60 FPS (16ms between frames)

// Time Configuration
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 0             // Your timezone offset in seconds
#define DAYLIGHT_OFFSET_SEC 3600     // Daylight saving time offset

// Weather Condition Enum
enum WeatherCondition {
  CLEAR,
  CLOUDY,
  PARTLY_CLOUDY,
  RAIN,
  STORM,
  SNOW,
  FOG,
  UNKNOWN
};

// Time of Day Enum
enum TimeOfDay {
  NIGHT,      // Nighttime (after dusk, before dawn)
  DAWN,       // Morning twilight (before sunrise)
  SUNRISE,    // Sunrise period
  DAY,        // Daytime
  SUNSET,     // Sunset period
  DUSK        // Evening twilight (after sunset)
};

// Debug Configuration
#define DEBUG true                   // Enable/disable debug output

#if DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

#endif // CONFIG_H
