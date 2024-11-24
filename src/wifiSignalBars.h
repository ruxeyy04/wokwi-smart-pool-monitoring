#include <WiFi.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

void displayWifiSignalStrength() {
  int32_t rssi = WiFi.RSSI(); // Get RSSI value
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi Signal:");

  int numBars = map(rssi, -100, -50, 0, 5); // Map RSSI to number of bars (0-5)

  int arcWidth = 12; // Width of each arc segment
  int arcHeight = 5; // Height difference between arcs

  // Draw Wi-Fi signal bars based on the number of arcs
  for (int i = 0; i < 5; i++) {
    if (i < numBars) {
      display.fillRect(i * 14, 40 - (i * arcHeight), arcWidth, 4 + (i * arcHeight), WHITE); // Filled arc-like bar
    } else {
      display.drawRect(i * 14, 40 - (i * arcHeight), arcWidth, 4 + (i * arcHeight), WHITE); // Empty arc-like bar
    }
  }

  // Display RSSI value
  display.setCursor(0, 50);
  display.print("RSSI: ");
  display.print(rssi);
  display.print(" dBm");
  display.display();
}