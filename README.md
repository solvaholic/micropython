# MicroPython Scripts Repository

This repository contains several Python scripts, written for ESP32 boards running MicroPython.

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

* MicroPython _Quick reference_ for [ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html)
* MicroPython firmware downloads for [ESP32](https://micropython.org/download/ESP32_GENERIC/) and [ESP32-S3](https://micropython.org/download/ESP32_GENERIC_S3/)
* MicroPython libraries and examples on GitHub: [**micropython/micropython**](https://github.com/micropython/micropython) and [**micropython/micropython-lib**](https://github.com/micropython/micropython-lib)
* Heltec Wifi Kit 32 v2 [PDF](https://resource.heltec.cn/download/WiFi_Kit_32/WiFi%20Kit32.pdf), [library](https://github.com/HelTecAutomation/Heltec_ESP32), and [framework](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/0aaf0d08b20c2d67aab416ae632320ac11ca7ea6/README.md)
* Seeed Studio XIAO ESP32S3 guides [_Getting Started_](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/) and [_MicroPython_](https://wiki.seeedstudio.com/XIAO_ESP32S3_Micropython/)

## Getting Started

To get started, clone this repository and open it in your favorite IDE. Create and/or activate a virtual environment, then run **./script/bootstrap.sh** to install required packages.

[**get_started.md**](get_started.md) describes where to download MicroPython and how to install it on a board and begin using it. See [**docs/boards.md**](docs/boards.md) for notes about different boards.

TODO: What about :hwconfig.py?
TODO: And what else?

## Contributing

Contributions are welcome! Please phrase feedback and suggestions as issues or pull requests :bow:

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.