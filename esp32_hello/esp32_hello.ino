/*
 * @solvaholic's first sketch for the Wifi kit 32, maybe.
 * It's a modified copy of this example from Heltec's example:
 * https://github.com/HelTecAutomation/Heltec_ESP32/tree/master/examples/OLED/SSD1306SimpleDemo
*/

#include "Arduino.h"
#include "heltec.h"

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  // TODO: Fix artifact top right corner
  // Heltec.display->fillRect(0, 0, 128, 64);
  // delay(10);
}

void helloWorldDemo() {
    // Display is 128x64
    // TEXT_ALIGN_CENTER: Coordinates define the center of the text
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(64, 20, "Hello world");
}

void drawTextFlowDemo() {
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

Demo demos[] = {helloWorldDemo, drawTextFlowDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void loop() {
  // clear the display
  Heltec.display->clear();
  // draw the current demo method
  demos[demoMode]();

  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(10, 128, String(millis()));
  // write the buffer to the display
  Heltec.display->display();

  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  delay(10);
}
