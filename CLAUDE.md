# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

MeteoCloud is an Arduino-based weather forecast visualization system that displays upcoming weather conditions using an LED strip. The system fetches weather data from an API and illuminates the LEDs with color patterns representing the 3-hour forecast.

## System Architecture

### Hardware Components
- **Arduino microcontroller** - Main control unit
- **LED strip** - Visual display (likely addressable LEDs such as WS2812B/NeoPixel)
- **Network connectivity** - WiFi module (ESP8266/ESP32) or Ethernet shield for API communication

### Software Components
1. **Weather API Integration** - Fetches forecast data (API provider TBD)
2. **LED Control System** - Drives the LED strip with weather-specific animations
3. **Effect Engine** - Renders different visual patterns based on weather conditions
4. **Time Management** - Tracks time of day for sunrise/sunset-aware effects

### Weather Effect Patterns

The system maps weather conditions to visual effects:

- **Storm**: Lightning effect - flickering bright flashes with random strikes
- **Clear**: Sun colors - warm tones that vary based on time of day
- **Cloudy**: White illumination with gentle brightness variations - intensity varies by time of day
- **Partly Cloudy**: Mix of sun and cloud colors in alternating patterns
- **Rain**: Blue falling droplets animation
- **Snow**: Snowflake falling animation - descending white sparkles
- **Fog**: Soft gray/white with slow wave pattern

### Time of Day Periods

The system recognizes six distinct time periods that affect LED colors and intensity:

- **NIGHT**: Nighttime (after dusk, before dawn) - minimal/no lighting
- **DAWN**: Morning twilight (~30 min before sunrise) - deep purple/blue tones
- **SUNRISE**: Sunrise period (~20 min) - orange/pink colors
- **DAY**: Daytime - full brightness with bright colors
- **SUNSET**: Sunset period (~20 min) - deep orange/red colors
- **DUSK**: Evening twilight (~30 min after sunset) - purple/pink tones

### Key Features
- **3-hour forecast display** - Shows upcoming weather within the next 3 hours
- **Time-aware effects** - Adjusts colors and intensity based on sunrise/sunset times with dawn and dusk transitions
- **Dynamic animations** - Each weather type has a distinct visual behavior at ~60 FPS

## Architecture Diagram

Refer to the `Untitled Diagram.drawio` file for the system architecture flowchart. This can be viewed/edited using diagrams.net (draw.io).

## Code Structure

### Main Files

- **MeteoCloud.ino** - Main sketch with setup() and loop(), handles WiFi connection and orchestrates all modules
- **config.h** - Configuration file with WiFi credentials, API keys, pin assignments, and enums

### Module Files

- **WeatherAPI.h/cpp** - Weather API client for fetching and parsing forecast data
- **LEDEffects.h/cpp** - LED strip animation engine with all weather-specific effects
- **TimeManager.h/cpp** - Time synchronization and sunrise/sunset calculation

### Configuration

1. Copy `config.h` and update the following:
   - `WIFI_SSID` and `WIFI_PASSWORD` - Your WiFi credentials
   - `WEATHER_API_KEY` and `WEATHER_API_URL` - Weather API configuration (provider TBD)
   - `LATITUDE` and `LONGITUDE` - Your location for accurate sunrise/sunset times
   - `LED_PIN` - GPIO pin connected to LED strip data line
   - `NUM_LEDS` - Number of LEDs in your strip
   - `GMT_OFFSET_SEC` - Your timezone offset in seconds

## Required Libraries

Install these libraries via Arduino IDE Library Manager or PlatformIO:

- **FastLED** - LED strip control (for WS2812B/NeoPixel)
- **ArduinoJson** - JSON parsing for weather API responses
- **HTTPClient** - Built-in ESP32/ESP8266 library for HTTP requests
- **WiFi** - Built-in ESP32/ESP8266 library for network connectivity

Optional libraries for accurate sunrise/sunset:
- **sunset** (https://github.com/buelowp/sunset) - Solar position calculations
- **SolarCalculator** (https://github.com/jpb10/SolarCalculator) - Alternative solar calculator

## Development Commands

### Arduino IDE

1. **Open project**: Open `MeteoCloud.ino` in Arduino IDE
2. **Select board**: Tools > Board > ESP32 Dev Module (or ESP8266 board)
3. **Select port**: Tools > Port > (your device port)
4. **Compile**: Sketch > Verify/Compile (Ctrl+R)
5. **Upload**: Sketch > Upload (Ctrl+U)
6. **Monitor**: Tools > Serial Monitor (Ctrl+Shift+M) - Set baud rate to 115200

### PlatformIO (if used)

```bash
# Build the project
pio run

# Upload to device
pio run --target upload

# Open serial monitor
pio device monitor
```

## Development Notes

### Weather API Integration

The `WeatherAPI.cpp` file contains placeholder code for API integration. To complete the implementation:

1. Choose a weather API provider (OpenWeatherMap, WeatherAPI, etc.)
2. Update `WEATHER_API_URL` and `WEATHER_API_KEY` in `config.h`
3. Modify the JSON parsing in `WeatherAPI::fetchForecast()` to match your API's response structure
4. Update `parseCondition()` to map your API's weather codes to the `WeatherCondition` enum

### Sunrise/Sunset Calculation

The `TimeManager.cpp` currently uses fixed times (6:00 AM / 6:00 PM). For accurate times:

1. Install a solar calculation library (sunset.h or SolarCalculator)
2. Update `calculateSunTimes()` in `TimeManager.cpp` with proper solar position calculations
3. The code includes commented examples for integration

### Testing LED Effects

To test individual effects without waiting for weather updates:
1. In `MeteoCloud.ino`, manually call `ledEffects.setWeatherEffect(STORM, DAY)` in `setup()`
2. Comment out the `updateWeather()` call in `loop()`
3. Upload and observe the effect
