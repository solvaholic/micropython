:construction: Work in progress to switch from Arduino to MicroPython, see [#5](https://github.com/solvaholic/arduino/issues/5) :construction:

# MicroPython Scripts Repository

This repository contains several Python scripts, written for Heltec's Wifi kit 32 ESP32 microcontroller running MicroPython.

## Scripts

### esp32_hello

**esp32_hello.py** writes "Hello, World!" to the onboard OLED. Not much to look at, just a first program to learn about the tools and board.

### web_server

**web_server.py** hosts a WiFi access point and simple web server that responds to a few GET requests. Get `/LED/on` to turn on the built-in LED, and get `/LED/off` to turn it off.

### scan-n-show

**scan-n-show.py** scans for WiFi networks and displays them on the OLED display.

### ble_server

TODO: Add a write-able characteristic to set built-in LED on/off.

**ble_server.py** hosts a BLE server that advertises an attribute with a read/write characteristic. Use nRF Connect or similar app to connect and read the characteristic.

## Resources

TODO: Link to MicroPython resources. Docs, libraries, well-maintained tutorials, etc.

## Getting Started

To get started, clone this repository and open it in your favorite IDE. Create and/or activate a virtual environment, then run **./script/bootstrap.sh** to install required packages.

[**get_started.md**](get_started.md) describes how to set up a board and flash the firmware. See [**docs/boards.md**](docs/boards.md) for notes about different boards.

TODO: How to get staretd _from scratch_?
TODO: What about :hwconfig.py?
TODO: And what else?

## Contributing

Contributions are welcome! Please phrase feedback and suggestions as issues or pull requests :bow:

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.