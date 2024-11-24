#define BUTTON_RELAY_2 33
#define BUTTON_RELAY 25
#include <Arduino.h>
#define RELAY_PIN 27 // main dynamo

#define RELAY_PIN_2 14 // loadcell dynamo

#define PUMP 23                      // in pump
#define PUMP2 17                     // out pump
volatile bool relayState = false;    // Tracks the relay state (ON or OFF)
volatile bool loadCellState = false; // Tracks loadcell relay state
// Interrupt Service Routine (ISR) for BUTTON_RELAY
volatile unsigned long buttonPressTime1 = 0;
volatile unsigned long buttonPressTime2 = 0;

volatile unsigned long buttonCooldown1 = 0;
volatile unsigned long buttonCooldownTime1 = 1000; // 1 second cooldown period

volatile unsigned long buttonCooldown2 = 0;
volatile unsigned long buttonCooldownTime2 = 1000; // 1 second cooldown period

void mainDispenseManual()
{
  if (digitalRead(RELAY_PIN_2) != HIGH) // Ensure RELAY_PIN_2 is not active
  {
    unsigned long currentMillis = millis();
    if (currentMillis - buttonPressTime1 > 50)
    {
      buttonPressTime1 = currentMillis;
      if (digitalRead(BUTTON_RELAY) == LOW && currentMillis - buttonCooldown1 > buttonCooldownTime1)
      {
        relayState = !relayState;                         // Toggle relay state
        digitalWrite(RELAY_PIN, relayState ? LOW : HIGH); // Set relay state
        buttonCooldown1 = currentMillis;
      }
    }
  }
}

void loadcellManual()
{
  if (digitalRead(RELAY_PIN) != HIGH) // Ensure RELAY_PIN is not active
  {
    unsigned long currentMillis = millis();
    if (currentMillis - buttonPressTime2 > 50)
    {
      buttonPressTime2 = currentMillis;
      if (digitalRead(BUTTON_RELAY_2) == HIGH && currentMillis - buttonCooldown2 > buttonCooldownTime2)
      {
        loadCellState = !loadCellState; // Toggle loadcell state

        if (loadCellState)
        {
          digitalWrite(RELAY_PIN_2, HIGH); // Activate loadcell relay
        }
        else
        {
          digitalWrite(RELAY_PIN_2, LOW); // Deactivate loadcell relay
          digitalWrite(PUMP, LOW);         // Turn off PUMP
          digitalWrite(PUMP2, LOW);        // Turn off PUMP2
        }
        buttonCooldown2 = currentMillis;
      }
    }
  }
}

void initDispenseManualButton()
{
  pinMode(BUTTON_RELAY, INPUT_PULLUP);
  pinMode(BUTTON_RELAY_2, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_RELAY), mainDispenseManual, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RELAY_2), loadcellManual, FALLING);
}
