#include <NewPing.h>

#include <Adafruit_SSD1306.h>
extern float weight;
extern Adafruit_SSD1306 display;

#define TRIG_PIN 4
#define ECHO_PIN 13

#define MAX_DISTANCE 400  // Define the max distance (in cm) for the sensor
#define EMPTY_LEVEL 400    // Distance in cm that represents 0% (empty)
#define FULL_LEVEL 2      // Distance in cm that represents 100% (full)


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned int distance;
unsigned int storageLevelPercent;

void storageLevel() {
  distance = sonar.ping_cm();
  // Serial.println("Ultrasonic: "+String(distance));
  storageLevelPercent = map(distance, EMPTY_LEVEL, FULL_LEVEL, 0, 100);
  storageLevelPercent = constrain(storageLevelPercent, 0, 100);


  if (digitalRead(RELAY_PIN_2) == HIGH) {
    digitalWrite(PUMP, LOW);  //pump1 on
    if (storageLevelPercent >= 96) {
      digitalWrite(PUMP, HIGH);  //pump1 off
      digitalWrite(PUMP2, LOW);  // pump2 on
    } else if (storageLevelPercent <= 5) {
      digitalWrite(PUMP, LOW);    //pump1 on
      digitalWrite(PUMP2, HIGH);  // pump2 off
    } else if (weight == 0.00 && storageLevelPercent != 0) {
      digitalWrite(PUMP, HIGH);  //pump1 off
      digitalWrite(PUMP2, LOW);  // pump2 on
    } else {
      digitalWrite(PUMP2, HIGH);
      digitalWrite(PUMP, HIGH);
    }
  }

  // Serial.print("Storage : ");
  // Serial.print(storageLevelPercent);
  // Serial.println(" %");

  display.setCursor(0, 36);
  display.print("Storage : ");
  display.print(storageLevelPercent);
  display.println(" %");
}
