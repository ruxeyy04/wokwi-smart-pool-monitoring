#include <Preferences.h>
#include "HX711.h"
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define LOADCELL_DOUT_PIN 26
#define LOADCELL_SCK_PIN 12

HX711 scale;
Preferences preferences;
float calibration_factor = 210.000;  // Adjust this to your calibration factor

long storedOffset = 0;

float weight;

void initPrefrences() {
  preferences.begin("weight-store", false);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);

  storedOffset = preferences.getLong("storedOffset", -1);

  if (storedOffset != -1) {
    scale.set_offset(storedOffset);
    Serial.println("Stored offset retrieved.");
  } else {
    scale.tare();
    storedOffset = scale.get_offset();
    preferences.putLong("storedOffset", storedOffset);
    Serial.println("No valid stored offset found, taring the scale.");
  }
}

void processWeight() {
  if (!scale.is_ready()) {
    Serial.println("HX711 not found.");
    return;
  }

  weight = scale.get_units(10);
  weight = weight < 0 ? 0 : weight;

  if (abs(weight - storedOffset) > 0.001) {
    storedOffset = scale.get_offset();
    preferences.putLong("storedOffset", storedOffset);
    // Serial.println("New offset stored: " + String(storedOffset));
  }
  display.setCursor(0, 48);
  display.print("Weight: ");
  display.print(weight, 3);
  display.println(" g");
  // Serial.println("Weight: " + String(weight, 3) + " kg");
}


