#include <Arduino.h>
#include <Wire.h>

#include "welcome.h"
#include "wifisetup.h"
#include "wifiSignalBars.h"
#include "relay.h"
#include "ultrasonic.h"
#include "ph.h"
#include "tds.h"
#include "temp.h"
#include "loadcell.h"
#include "manualDispense.h"
// #include "calibLoadCell.h"
#define Button 0

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile unsigned long buttonPressTime = 0;
volatile bool buttonClicked = false;
int displayMode = 0;
unsigned long lastDataDisplayTime = 0;

// Cooldown timer for button press detection
volatile unsigned long buttonCooldown = 0;
volatile unsigned long buttonCooldownTime = 1000; // 1 second cooldown period

void IRAM_ATTR handleButtonPress()
{
  unsigned long currentMillis = millis();

  // Debounce check
  if (currentMillis - buttonPressTime > 50)
  {
    buttonPressTime = currentMillis;

    // Check if the button is pressed (LOW) and cooldown has passed
    if (digitalRead(Button) == LOW && currentMillis - buttonCooldown > buttonCooldownTime)
    {
      buttonClicked = true;           // Register button click
      buttonCooldown = currentMillis; // Reset the cooldown timer
    }
  }
}

void setup()
{
  Serial.begin(115200);
  initPrefrences();

  welcome();
  while (!Serial)
    ;
  wifiSetup();
  initDispensePump();
  initDispenseManualButton();
  initTDS();
  pinMode(Button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Button), handleButtonPress, FALLING);
}

void loop()
{
  if (buttonClicked)
  {
    displayMode = (displayMode + 1) % 2;
    Serial.print("Display mode changed to: ");
    Serial.println(displayMode == 0 ? "Data" : displayMode == 1 ? "Wi-Fi"
                                                                : "");
    delay(500);

    buttonClicked = false;
  }

  switch (displayMode)
  {
  case 0:
    if (millis() - lastDataDisplayTime >= 500)
    {
      display.clearDisplay();
      turbidity();
      ph_Sensor();
      readTemp();
      storageLevel();
      processWeight();
    }
    break;
  case 1:
    displayWifiSignalStrength();
    break;
  // case 2:
  //   calibrateLoadCell();
  //   break;
  }
  display.display();
  delay(200);
}
