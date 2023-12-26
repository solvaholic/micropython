/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "Arduino.h"
#include "WiFi.h"
#include "heltec.h"
#include "./font.h"

//rotate only for GEOMETRY_128_64
 SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED, RST_OLED);

#define OLED_UPDATE_INTERVAL 500

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}

void setup()
{
    Serial.begin(115200);

    VextON();
    delay(100);

    display.init();
    display.clear();
    display.display();
    display.setContrast(255);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
    display.drawString(0, 0, "Setup done");
    display.display();
}

void loop()
{
    Serial.println("Scan start");

    /*
    display.clear();
    display.display();
    display.screenRotate(ANGLE_90_DEGREE);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "TEXT");
    display.display();
    delay(2000);
    */

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");

    display.clear();
    display.display();
    display.screenRotate(ANGLE_90_DEGREE);
    display.setFont(Nimbus_Mono_L_Regular_12);

    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        display.drawString(0, 0, "Networks:");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            display.drawString(0, ((i + 1) * 12), WiFi.SSID(i));
        }
        display.display();
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
