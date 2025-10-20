#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <TFT_eSPI.h>  // Graphics and font library for ST7789 driver chip
#include "config.h"   // Demo configuration file (copy to config.h with your settings)

// Configuration is now handled in config.h file

TFT_eSPI tft = TFT_eSPI();  // TFT object

// WiFi reconnection function
void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Reconnecting to WiFi");
    WiFi.reconnect();
    unsigned long startAttemptTime = millis();
    const unsigned long wifiTimeout = 10000; // 10 seconds timeout for reconnection

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(" OK!");
    } else {
      Serial.println(" FAILED!");
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize TFT
  tft.init();
  tft.setRotation(1);  // Portrait mode: 320x170
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);  // Center text

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  unsigned long startAttemptTime = millis();
  const unsigned long wifiTimeout = 15000; // 15 seconds timeout

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(" FAILED!");
    tft.drawString("WiFi connection failed", 160, 85, 2);
    return;
  }
  Serial.println(" OK!");

  // Init and get time
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

  // Wait for time to be set with retry mechanism
  struct tm timeinfo;
  int retryCount = 0;
  const int maxRetries = 5;

  while (!getLocalTime(&timeinfo) && retryCount < maxRetries) {
    Serial.print("Failed to obtain time, retrying...");
    retryCount++;
    delay(2000);  // Wait 2 seconds before retry
    Serial.print(" attempt ");
    Serial.println(retryCount);
  }

  if (retryCount >= maxRetries) {
    Serial.println("Failed to obtain time after all retries");
    tft.drawString("Time sync failed", 160, 85, 2);  // Fallback message
    return;
  }
  Serial.print("Time synced after ");
  Serial.print(retryCount);
  Serial.println(" attempts!");

  // Enable backlight (GPIO15 for T-Display-S3)
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
}

void loop() {
  // Check WiFi connection and reconnect if needed
  static unsigned long lastWiFiCheck = 0;
  if (millis() - lastWiFiCheck > 30000) {  // Check every 30 seconds
    reconnectWiFi();
    lastWiFiCheck = millis();
  }

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    // Format time as HH:MM (24-hour) - update only when minutes change
    char timeString[6];
    strftime(timeString, sizeof(timeString), "%H:%M", &timeinfo);

    // Only update display when minutes change (eliminates flickering completely)
    static char lastTimeString[6] = "";
    static unsigned long lastUpdateTime = 0;

    // Extract current minute for comparison
    char currentMinute[3];
    strftime(currentMinute, sizeof(currentMinute), "%M", &timeinfo);

    static char lastMinute[3] = "";

    // Only update when minute changes (not every second)
    if (strcmp(currentMinute, lastMinute) != 0) {
      strcpy(lastMinute, currentMinute);
      strcpy(lastTimeString, timeString);
      lastUpdateTime = millis();

      // Use font 8 for maximum size (75px height) - largest possible font
      // Font 8 character width is approximately 45px per digit
      int textWidth = 45 * 5;  // 5 characters (HH:MM + null terminator space)
      int textHeight = 80;     // Font 8 height (75px + padding)
      int x = 160 - (textWidth / 2);  // Center the clearing rectangle
      int y = 85 - 40;  // Adjust Y to cover the larger text area

      // Batch display operations for smoother updates
      tft.startWrite();

      // Clear only the exact text area
      tft.fillRect(x, y, textWidth, textHeight, TFT_BLACK);

      // Set text color for better contrast
      tft.setTextColor(TFT_WHITE, TFT_BLACK);

      // Draw time centered (font 8: ~75px height - maximum size)
      tft.drawString(timeString, 160, 85, 8);

      // Complete the write operation
      tft.endWrite();
    }
  } else {
    Serial.println("Failed to obtain time");
    // Try to resync time if WiFi is connected
    if (WiFi.status() == WL_CONNECTED) {
      static int timeSyncRetries = 0;
      const int maxTimeSyncRetries = 3;

      if (timeSyncRetries < maxTimeSyncRetries) {
        Serial.print("Attempting to resync time...");
        configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
        timeSyncRetries++;
        Serial.print(" attempt ");
        Serial.println(timeSyncRetries);
      } else {
        // Show error message on display after max retries
        static char lastErrorString[20] = "";
        static unsigned long lastErrorUpdate = 0;
        if (strcmp("Time sync error", lastErrorString) != 0 && millis() - lastErrorUpdate > 5000) {
          strcpy(lastErrorString, "Time sync error");
          lastErrorUpdate = millis();
          tft.startWrite();
          tft.fillRect(0, 70, 320, 30, TFT_BLACK);
          tft.drawString("Time sync error", 160, 85, 2);
          tft.endWrite();
          Serial.println("Max time sync retries reached");
        }
      }
    } else {
      // WiFi not connected, show appropriate message
      static char lastErrorString[20] = "";
      static unsigned long lastErrorUpdate = 0;
      if (strcmp("No WiFi", lastErrorString) != 0 && millis() - lastErrorUpdate > 5000) {
        strcpy(lastErrorString, "No WiFi");
        lastErrorUpdate = millis();
        tft.startWrite();
        tft.fillRect(0, 70, 320, 30, TFT_BLACK);
        tft.drawString("No WiFi", 160, 85, 2);
        tft.endWrite();
      }
    }
  }

  delay(200);  // Moderate delay for stability
}
