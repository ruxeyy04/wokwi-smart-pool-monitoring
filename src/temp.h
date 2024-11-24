#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define TEMP_PIN 16 

OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);
float celsius = 0;

void initTemperatureSensor() {
  tempSensor.begin();
}

float getTemperatureCelsius() {
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}

void readTemp() {

  celsius = getTemperatureCelsius();

  // Display temperature
  // Serial.print(celsius);
  // Serial.println(" C");
  display.setCursor(0, 24);
  display.print("Temperature: ");
  display.print(celsius, 1);
  display.println(" C");
}