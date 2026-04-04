# ESP32-C3 OLED Clock

A beautiful, flicker-free digital clock for the LilyGo T-Display S3 (ESP32-S3) with large 75px font display, WiFi connectivity, and automatic Daylight Saving Time (DST) handling.

- **Auto DST Support:** Uses POSIX timezone strings for automatic Daylight Saving Time transitions — no manual offset changes needed.
- **Fixed Blank Screen Issue:** Corrected the `TFT_eSPI` library setup to properly initialize the display.
- **Centered Text:** The clock text is centered in landscape mode.
- **Self-Contained Project:** The `TFT_eSPI` configuration files are now included in the `src` directory, making the project easier to build.
- **Dynamic Color Cycling:** Font color changes at configurable intervals (testing: every minute, production: every hour).

## Features

- **Large 75px Display Font** - Maximum size for excellent readability
- **Flicker-Free Updates** - Only updates when minutes change (not every second)
- **WiFi Connectivity** - Automatic time synchronization via NTP
- **Automatic DST** - POSIX timezone strings handle Daylight Saving Time transitions automatically
- **Robust Error Handling** - Graceful handling of WiFi disconnections and time sync failures
- **Visual Error Messages** - Clear on-screen feedback for connection issues
- **Power Efficient** - Minimal display updates for longer battery life
- **Dynamic Color Cycling** - Font color cycles through a palette at configurable intervals

## Hardware Requirements

- **LilyGo T-Display S3** - ESP32-S3 based board with integrated 320x170 ST7789 display
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

### 2. Configure WiFi and Timezone
Copy the demo configuration and update with your settings:
```bash
# Copy the demo file to create your personal config
cp demo-config.h src/config.h

# Edit the new config file with your WiFi credentials and timezone
nano src/config.h
```

Update the values in `src/config.h`:
```cpp
const char* WIFI_SSID = "YOUR_ACTUAL_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_ACTUAL_WIFI_PASSWORD";

// Timezone configuration (POSIX timezone string for auto DST)
// Europe/Berlin: "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00"
// London:        "GMT0BST,M3.5.0/01:00:00,M10.5.0/02:00:00"
// US Eastern:    "EST5EDT,M3.2.0/02:00:00,M11.1.0/02:00:00"
const char* TZ_INFO = "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00";  // Europe/Berlin (auto DST)

// Color cycling configuration
#define COLOR_CLOCK true  // Set to true to enable color cycling, false to disable
#define COLOR_CLOCK_INTERVAL 60000  // Interval in milliseconds (60000 = 1 minute, 3600000 = 1 hour)
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

### Timezone Settings (Auto DST)
The clock uses POSIX timezone strings to automatically handle Daylight Saving Time transitions. The default is configured for **Europe/Berlin (CET/CEST)**. To change the timezone, modify the `TZ_INFO` value in `src/config.h`:

```cpp
// Europe/Berlin (CET/CEST) - default
const char* TZ_INFO = "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00";

// London (GMT/BST)
const char* TZ_INFO = "GMT0BST,M3.5.0/01:00:00,M10.5.0/02:00:00";

// US Eastern (EST/EDT)
const char* TZ_INFO = "EST5EDT,M3.2.0/02:00:00,M11.1.0/02:00:00";
```

**POSIX timezone format explained:**
- `STD offset DST [start],[end]` — the ESP32 uses this format to calculate DST transitions automatically
- `CET-1` = Central European Time, 1 hour ahead of UTC
- `CEST` = Central European Summer Time (DST)
- `M3.5.0/02:00:00` = DST starts on the 5th day (Sunday) of March at 02:00
- `M10.5.0/03:00:00` = DST ends on the 5th day (Sunday) of October at 03:00

No manual clock changes are needed — the ESP32 handles DST transitions automatically based on the POSIX rule.

### Color Cycling Settings
Control the dynamic color cycling feature in `src/config.h`:

```cpp
// Enable or disable color cycling
#define COLOR_CLOCK true  // Set to true to enable, false to disable

// Set the interval for color changes
#define COLOR_CLOCK_INTERVAL 60000  // 60000 ms = 1 minute (testing)
                                     // 3600000 ms = 1 hour (production)
```

The color palette cycles through: White → Red → Green → Blue → Yellow → Cyan → Magenta

### Display Settings
The display is configured for the LilyGo T-Display S3 in **landscape orientation** (170×320).
- **Resolution**: 170×320 pixels (landscape)
- **Driver**: ST7789
- **Backlight**: GPIO 38

## Credits

- **Original Author:** This project is based on the work of the original author.
- **TFT_eSPI Library:** by Bodmer
