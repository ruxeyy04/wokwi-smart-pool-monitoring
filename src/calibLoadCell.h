#include "HX711.h"
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define LOADCELL_DOUT_PIN 26
#define LOADCELL_SCK_PIN 12

// Enter the known weight in kilograms that you'll place on the load cell for calibration
const float known_weight_kg = 0.2;  // Example: 0.1 kg (100 grams)
bool calibrateDone = false;
HX711 scale;
float calib_test;
void initcalibLoad() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Step 1: Tare the scale
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Taring the scale...");
  display.setCursor(0, 10);
  display.print("Ensure it's empty.");
  display.display();

  scale.tare();  // Reset scale to zero
  delay(5000);

  // Step 2: Place known weight for calibration
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Place known weight");
  display.setCursor(0, 10);
  display.print("on the scale.");
  display.display();
  delay(10000);

  // Step 3: Calculate the calibration factor
  float reading = scale.get_units(10);             // Average of 10 readings for stability
  float calibration_factor_test = reading / known_weight_kg;  // Calculate factor
  scale.set_scale(calibration_factor_test);

  // Step 4: Display the calibration factor
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibration complete!");
  display.setCursor(0, 10);
  display.print("Factor:");
  display.setCursor(0, 20);
  display.print(calibration_factor_test, 3);
  display.display();
  calib_test = calibration_factor_test;
  delay(5000);  // Delay to show calibration info
  calibrateDone = true;
}

void calibrateLoadCell() {
  if (!calibrateDone) {
    initcalibLoad();  // Run calibration if not done
  }

  float weight_kg = scale.get_units();  // Get the weight in kilograms

  // Display current weight and calibration factor
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Weight: ");
  display.print(weight_kg, 3);
  display.println(" kg");

  display.setCursor(0, 10);
  display.print("Factor:");
  display.print(calib_test, 3);
  display.display();

  delay(1000);  // Update every second
}

float getCalibrationFactor() {
  return calib_test;
}