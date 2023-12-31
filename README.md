# Arduino Sketches Repository

This repository contains several Arduino sketches, written for Heltec's Wifi kit 32 ESP32 microcontroller. Each sketch is organized in its own directory, along with its corresponding documentation.

## Sketches

### esp32_hello

**esp3_hello.ino** is a Hello World sketch for [Heltec WiFi kit 32](https://github.com/HelTecAutomation/Heltec_ESP32). Not much to look at, just a first program to learn about the tools and board.

### web_server

**web_server.ino** hosts a WiFi access point and simple web server that responds to a few GET requests. Get `/H` to turn on the built-in LED, and get `/L` to turn it off. Requests are logged to serial console and OLED display.

### scan-n-show

**scan-n-show.ino** scans for WiFi networks and displays them on the OLED display. It also logs the scan results to the serial console.

### ble_server

TODO: Add a write-able characteristic to set built-in LED on/off.

**ble_server.ino** hosts a BLE server that advertises an attribute with a read/write characteristic. Use nRF Connect or similar app to connect, read, and write to the characteristic.

## Resources

- [Heltec ESP32 Documentation](https://docs.heltec.org)
- [Heltec ESP32 Quick Start Guide](https://docs.heltec.org/en/node/esp32/esp32_general_docs/quick_start.html)
- [Heltec WiFi Kit 32 PDF](https://resource.heltec.cn/download/WiFi_Kit_32/WiFi%20Kit32.pdf)
- [Heltec Community](http://community.heltec.cn)
- [Heltec WiFi Kit 32 Library](https://github.com/HelTecAutomation/Heltec_ESP32)
- [Heltec Framework](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/README.md)
- [Heltec Framework Pre-v3](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/0aaf0d08b20c2d67aab416ae632320ac11ca7ea6/README.md)
- [ESP Exception Decoder](https://github.com/me-no-dev/EspExceptionDecoder)

## Getting Started

To get started, clone this repository and open the sketches in your Arduino IDE. Each sketch directory contains a .ino file that can be directly opened in the Arduino IDE.

If you'd like to use `arduino-cli` and a different IDE, you can use **./script/bootstrap.sh** to install the board and libraries. The scripts in **./script** have been tested manually in MacOS 14; They assume you already have `arduino-cli` installed.

## Contributing

Contributions are welcome! Please phrase feedback and suggestions as issues or pull requests :bow:

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.