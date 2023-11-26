/*
  web_server.ino creates a WiFi access point and provides a web server on it, and logs client requests to OLED.

  Steps:
  1. Connect to the access point "esp32wifi"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Based on https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/0.0.9/esp32/libraries/WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
  Which was created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)

  And based on https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/0.0.9/esp32/libraries/WebServer/examples/HelloServer/HelloServer.ino

*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <heltec.h>

// TODO: Do we need these?
#define DEMO_DURATION 3000
typedef void (*Demo)(void);
int demoMode = 0;
int counter = 1;

// Set these to your desired credentials.
const char *ssid = "esp32wifi";

// Want to set a password on the WiFi? Try this:
//   const char *password = "yourPassword";

WebServer server(80);


void handleRoot() {
  digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(LED_BUILTIN, 0);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 0);
}

void logThisRequest() {
  String message = server.client().remoteIP().toString();
  message += " ";
  message += server.method() == HTTP_GET ? "GET" : "POST";
  message += " ";
  message += server.uri();

  Serial.println(message);

  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawStringMaxWidth(0, 0, 128, message);
  Heltec.display->display();
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->fillRect(0, 0, 128, 64);
  Heltec.display->display();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  Serial.begin(115200);

  Serial.println();
  Serial.println("Configuring access point...");

  // Want to set a password on the WiFi? Try this:
  //   WiFi.softAP(ssid, password);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("");

  server.on("/", handleRoot);
  server.on("/H", []() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/plain", "Lights on");
    logThisRequest();
  });
  server.on("/L", []() {
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/plain", "Lights off");
    logThisRequest();
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
