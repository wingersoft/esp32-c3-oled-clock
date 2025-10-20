# ESP32-C3 OLED Clock

A beautiful, flicker-free digital clock for the LilyGo T-Display S3 (ESP32-S3) with large 75px font display, WiFi connectivity, and robust error handling.

- **Fixed Blank Screen Issue:** Corrected the `TFT_eSPI` library setup to properly initialize the display.
- **Display Rotation:** Added the ability to rotate the display 90 degrees to portrait mode.
- **Centered Text:** The clock text is now correctly centered in portrait mode.
- **Self-Contained Project:** The `TFT_eSPI` configuration files are now included in the `src` directory, making the project easier to build.

## Features

- **Large 75px Display Font** - Maximum size for excellent readability
- **Flicker-Free Updates** - Only updates when minutes change (not every second)
- **WiFi Connectivity** - Automatic time synchronization via NTP
- **Robust Error Handling** - Graceful handling of WiFi disconnections and time sync failures
- **Visual Error Messages** - Clear on-screen feedback for connection issues
- **Timezone Support** - Configurable timezone offset
- **Power Efficient** - Minimal display updates for longer battery life

## Hardware Requirements

- **LilyGo T-Display S3** - ESP32-S3 based board with integrated 170×320 ST7789 display
- **USB-C Cable** - For power and programming
- **WiFi Network** - For time synchronization

## Software Requirements

- **PlatformIO** - For building and uploading the firmware

## Installation

### 1. Clone or Download
```bash
git clone <your-repo-url>
cd esp32-c3-oled-clock
```

### 2. Configure WiFi
Copy the demo configuration and update with your settings:
```bash
# Copy the demo file to create your personal config
cp demo-config.h src/config.h

# Edit the new config file with your WiFi credentials
nano src/config.h
```

Update the values in `src/config.h`:
```cpp
const char* WIFI_SSID = "YOUR_ACTUAL_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_ACTUAL_WIFI_PASSWORD";
```

### 3. Build and Upload
```bash
# Build the project
platformio run

# Upload to the board (make sure the board is connected)
platformio run --target upload

# Monitor serial output (optional)
platformio run --target monitor
```

## Configuration

### Timezone Settings
The clock is currently configured for **Europe/Amsterdam (UTC+2)**. To change the timezone, modify these values in `src/config.h`:

```cpp
const long GMT_OFFSET_SEC = 3600;  // Offset in seconds (3600 = 1 hour)
const int DAYLIGHT_OFFSET_SEC = 3600;  // DST offset (set to 0 if not using DST)
```

### Display Settings
The display is configured for the LilyGo T-Display S3 in portrait mode.
- **Resolution**: 320x170 pixels
- **Driver**: ST7789

## Credits

- **Original Author:** This project is based on the work of the original author.
- **TFT_eSPI Library:** by Bodmer
