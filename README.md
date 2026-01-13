# MeteoCloud

An Arduino-based weather forecast visualization system that displays upcoming weather conditions using an LED strip with dynamic color patterns and animations.

## Features

- **Real-time weather visualization** - Fetches 3-hour weather forecasts from API
- **Time-aware lighting** - Adjusts colors based on time of day (dawn, sunrise, day, sunset, dusk, night)
- **Dynamic animations** - Each weather condition has unique visual effects:
  - Storm: Lightning flashes
  - Clear: Sun colors (varies by time of day)
  - Cloudy: Soft white waves
  - Rain: Falling blue droplets
  - Snow: Falling snowflakes
  - Fog: Misty gray waves
- **Smooth 60 FPS animations** - Using FastLED library

## Hardware Requirements

- ESP32 or ESP8266 microcontroller (with WiFi)
- WS2812B/NeoPixel LED strip
- 5V power supply (adequate for LED strip)
- Connecting wires

## Quick Start

1. **Install Arduino IDE** and ESP32/ESP8266 board support

2. **Install required libraries** via Library Manager:
   - FastLED
   - ArduinoJson

3. **Configure the project**:
   ```bash
   cp config.example.h config.h
   ```
   Edit `config.h` with your WiFi credentials, API key, and hardware settings

4. **Upload to board**:
   - Open `MeteoCloud.ino` in Arduino IDE
   - Select your board (ESP32 Dev Module or ESP8266)
   - Select the correct port
   - Click Upload

5. **Monitor via Serial** (115200 baud) to see debug output

## Configuration

See `config.h` for all configuration options:
- WiFi credentials
- Weather API settings
- LED strip configuration (pin, count, type)
- Location (latitude/longitude)
- Timezone settings

## Documentation

See [CLAUDE.md](CLAUDE.md) for detailed architecture, code structure, and development notes.

## License

MIT
