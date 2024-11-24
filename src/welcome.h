#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

void welcome() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor((128 - (6 * 10)) / 2, 0);
  display.println("Welcome to");

  display.setCursor((128 - (6 * 17)) / 2, 12);
  display.println("IoT Powered Smart");

  display.setCursor((128 - (6 * 13)) / 2, 24);
  display.println("Water Quality");


  display.setCursor((128 - (6 * 19)) / 2, 36);
  display.println("Monitoring and Auto");


  display.setCursor((128 - (6 * 17)) / 2, 48);
  display.println("Dispense Chlorine");

  display.display();
  delay(5000);

  display.clearDisplay();
  display.display();
}