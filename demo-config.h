// Demo configuration file for ESP32-C3 OLED Clock
// Copy this file to config.h and update with your actual WiFi credentials

#ifndef DEMO_CONFIG_H
#define DEMO_CONFIG_H

// WiFi credentials - UPDATE THESE FOR YOUR NETWORK
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// NTP Server configuration
const char* NTP_SERVER = "pool.ntp.org";

// Timezone configuration (offset in seconds)
// Examples:
// UTC+1 (Central Europe): 3600
// UTC+2 (Eastern Europe): 7200
// UTC-5 (Eastern US): -18000
// UTC-8 (Pacific US): -28800
const long GMT_OFFSET_SEC = 3600;  // UTC+1 (change this for your timezone)
const int DAYLIGHT_OFFSET_SEC = 3600;  // DST offset (1 hour, set to 0 if not using DST)

// TFT Display configuration for LilyGO T-Display-S3
#define TFT_BL 38  // Backlight pin (GPIO38 for T-Display-S3)

// Color cycling configuration
#define COLOR_CLOCK true  // Set to true to enable color cycling, false to disable
#define COLOR_CLOCK_INTERVAL 60000  // Interval in milliseconds (60000 = 1 minute, 3600000 = 1 hour)

#endif // DEMO_CONFIG_H
