# ESP32-C3 OLED Clock

A beautiful, flicker-free digital clock for the LilyGo T-Display S3 (ESP32-S3) with large 75px font display, WiFi connectivity, and robust error handling.

## Features

- **Large 75px Display Font** - Maximum size for excellent readability
- **Flicker-Free Updates** - Only updates when minutes change (not every second)
- **WiFi Connectivity** - Automatic time synchronization via NTP
- **Robust Error Handling** - Graceful handling of WiFi disconnections and time sync failures
- **Visual Error Messages** - Clear on-screen feedback for connection issues
- **Timezone Support** - Configurable timezone offset (currently set for Europe/Amsterdam)
- **Power Efficient** - Minimal display updates for longer battery life

## Hardware Requirements

- **LilyGo T-Display S3** - ESP32-S3 based board with integrated 170×320 ST7789 display
- **USB-C Cable** - For power and programming
- **WiFi Network** - For time synchronization

## Software Requirements

- **PlatformIO** - For building and uploading the firmware
- **ESP32 Arduino Framework** - Automatically installed via PlatformIO

## Installation

### 1. Clone or Download
```bash
git clone <your-repo-url>
cd esp32-c3-oled-clock
```

### 2. Install PlatformIO
If you don't have PlatformIO installed:
```bash
# Using PlatformIO Core CLI
pip install -g platformio

# Or using VS Code extension
# Install "PlatformIO IDE" extension from VS Code marketplace
```

### 3. Configure WiFi
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

### 4. Build and Upload
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
The clock is currently configured for **Europe/Amsterdam (UTC+2)**. To change the timezone, modify these values in `src/main.cpp`:

```cpp
const long gmtOffset_sec = 3600;  // Offset in seconds (3600 = 1 hour)
const int daylightOffset_sec = 3600;  // DST offset (set to 0 if not using DST)
```

**Common timezone offsets:**
- UTC+1 (Central Europe): `3600`
- UTC+2 (Eastern Europe): `7200`
- UTC-5 (Eastern US): `-18000`
- UTC-8 (Pacific US): `-28800`

### Display Settings
The display is optimized for the LilyGo T-Display S3 with:
- **Resolution**: 170×320 pixels
- **Driver**: ST7789
- **Font Size**: 8 (75px height)
- **Update Frequency**: Once per minute (flicker-free)

## Usage

1. **Power On**: Connect the board via USB-C
2. **Automatic Setup**: The clock will automatically connect to WiFi and sync time
3. **Display**: Shows current time in HH:MM format with large 75px digits
4. **Error Handling**: If WiFi fails, displays "No WiFi" or "Time sync error"

### LED Status
- **Green LED**: Indicates the board is powered on
- **Display**: Shows time when working, error messages when issues occur

## Troubleshooting

### Display Shows "No WiFi"
- Check WiFi credentials in `src/config.h` (make sure you copied from demo-config.h)
- Ensure your WiFi network is 2.4GHz (ESP32-S3 WiFi limitation)
- Verify the board is in range of your WiFi router

### Missing config.h File
- Copy `demo-config.h` to `src/config.h`
- Edit the new config.h file with your actual WiFi credentials

### Display Shows "Time sync error"
- Usually resolves automatically once WiFi connection is restored
- Check internet connectivity of your WiFi network
- NTP server `pool.ntp.org` should be accessible

### Black Screen
- Verify the board is powered (green LED should be on)
- Check USB connection and try a different cable
- Re-upload the firmware

### Flickering Display
- This firmware is designed to be flicker-free (updates only when minutes change)
- If flickering occurs, it may indicate electrical issues or display problems

### Build Errors
- Ensure PlatformIO is properly installed
- Try `platformio run --target clean` to clean build files
- Check that all dependencies are properly installed

## Technical Details

### Architecture
- **Microcontroller**: ESP32-S3 (240MHz dual-core)
- **Display**: ST7789 170×320 TFT LCD
- **Connectivity**: WiFi 802.11 b/g/n
- **Time Sync**: NTP via `pool.ntp.org`

### Memory Usage
- **Flash**: ~23% used (746KB of 3.1MB)
- **RAM**: ~14% used (46KB of 320KB)
- **PSRAM**: Not utilized (display uses internal RAM)

### Power Consumption
- **Active**: ~150mA (with WiFi and display)
- **Display Off**: ~50mA (WiFi only)
- **Deep Sleep**: Not implemented (continuous operation)

### Display Specifications
- **Technology**: TFT LCD with ST7789 controller
- **Resolution**: 170×320 pixels (portrait orientation)
- **Colors**: 65K colors (RGB565)
- **Interface**: SPI (4-wire serial)
- **Backlight**: LED (GPIO15 control)

## File Structure

```
esp32-c3-oled-clock/
├── src/
│   ├── main.cpp          # Main application code
│   ├── demo-config.h     # Template configuration file (safe to share)
│   └── config.h          # Your personal config (not in git - add your WiFi credentials)
├── .pio/                 # PlatformIO build files (auto-generated)
├── platformio.ini        # Project configuration
├── README.md            # This file
└── .gitignore           # Git ignore patterns (includes config.h)
```

## Performance Optimizations

- **Smart Updates**: Only redraws when time actually changes
- **Batched Operations**: Uses `startWrite()`/`endWrite()` for smooth updates
- **Optimized Clearing**: Precise rectangle clearing to minimize operations
- **Efficient Fonts**: Uses font 8 (75px) for maximum readability
- **Memory Management**: Minimal RAM usage for stability

## Development

### Adding New Features
The codebase is structured for easy extension:
- Error handling functions in `loop()`
- WiFi management in `reconnectWiFi()`
- Display functions use TFT_eSPI library

### Customization
- **Font Size**: Change font number in `tft.drawString()` call
- **Colors**: Modify `TFT_WHITE` and `TFT_BLACK` color definitions
- **Layout**: Adjust positioning coordinates for different display layouts

## License

This project is open source. Feel free to modify and distribute according to your needs.

## Support

For issues or questions:
1. Check the troubleshooting section above
2. Verify your hardware setup matches the requirements
3. Ensure WiFi credentials are correct
4. Try re-uploading the firmware

---

**Created for LilyGo T-Display S3** |
**Version**: 1.0 |
**Last Updated**: 2024