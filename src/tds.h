#ifndef TDS_H
#define TDS_H

#define TDS 34
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

int ntu;

void initTDS() {
  pinMode(TDS, INPUT);
}

void turbidity() {
  int totalValue = 0;
  int sampleCount = 50;

  for (int i = 0; i < sampleCount; i++) {
    totalValue += analogRead(TDS);
    delay(10); 
  }

  int averageValue = totalValue / sampleCount;

  ntu = map(averageValue, 0, 4096, 100, 0);
  ntu = constrain(ntu, 0, 100);

  // Serial.println("Analog Turbidity (Average): " + String(averageValue));
  display.setCursor(0, 0);
  display.print("Turbidity: ");
  display.print(ntu);
  display.println(" NTU");
}

#endif
