// Demo configuration file for ESP32-C3 OLED Clock
// Copy this file to config.h and update with your actual WiFi credentials

#ifndef DEMO_CONFIG_H
#define DEMO_CONFIG_H

// WiFi credentials - UPDATE THESE FOR YOUR NETWORK
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// NTP Server configuration
const char* NTP_SERVER = "pool.ntp.org";

// Timezone configuration (POSIX timezone string for auto DST)
// Examples:
// Europe/Berlin: "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00"
// London: "GMT0BST,M3.5.0/01:00:00,M10.5.0/02:00:00"
// US Eastern: "EST5EDT,M3.2.0/02:00:00,M11.1.0/02:00:00"
const char* TZ_INFO = "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00";  // Europe/Berlin (auto DST)

// Legacy timezone config (kept for compatibility, not used with auto DST)
// const long GMT_OFFSET_SEC = 3600;  // UTC+1 (change this for your timezone)
// const int DAYLIGHT_OFFSET_SEC = 3600;  // DST offset

// TFT Display configuration for LilyGO T-Display-S3
#define TFT_BL 38  // Backlight pin (GPIO38 for T-Display-S3)

// Color cycling configuration
#define COLOR_CLOCK true  // Set to true to enable color cycling, false to disable
#define COLOR_CLOCK_INTERVAL 60000  // Interval in milliseconds (60000 = 1 minute, 3600000 = 1 hour)

#endif // DEMO_CONFIG_H
