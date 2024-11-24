#include <Arduino.h>
#define RELAY_PIN 27  //main dynamo

#define RELAY_PIN_2 14  //loadcell dynamo


#define PUMP 23 //in pump
#define PUMP2 17 // out pump

void initDispensePump() {
  pinMode(PUMP, OUTPUT);
  pinMode(PUMP2, OUTPUT);

  digitalWrite(PUMP, LOW);
  digitalWrite(PUMP2, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, LOW);
}

void manualFunction () {}