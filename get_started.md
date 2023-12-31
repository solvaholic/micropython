Get started with MicroPython

## Downaload firmware

Find the latest appropriate .bin file for your board in **micropython/micropython** on GitHub:
https://github.com/micropython/micropython/releases/latest

The examples in this document ran successfully with [**ESP32_GENERIC-20231227-v1.22.0.bin**](https://micropython.org/resources/firmware/ESP32_GENERIC-20231227-v1.22.0.bin) on a [Heltec Wifi Kit 32 v2]().

## Activate virtual environment

If you don't already have a virtual environment, create one with `python3 -m venv .`.

Activate the virtual environment:

```bash
source bin/activate
```

## Install required packages

Use `pip` to install `esptool.py` and `mpremote`. To install the versions of the packages used in this project, run:

```bash
pip install -r requirements.txt
```

After installing packages, you may need to `deactivate` and `source bin/activate` the virtual environment again, to get new commands into your path.

## Flash firmware

Check out [the published instructions](http://docs.micropython.org/en/v1.22.0/esp32/tutorial/intro.html). If this is your first time using MicroPython, compare those instructions to a user-provided walk-through using a platform similar to yours, for example [_MicroPython on an ESP32 Board With Integrated SSD1306 OLED Display (WEMOS/Lolin)_](https://www.instructables.com/MicroPython-on-an-ESP32-Board-With-Integrated-SSD1/).

### Check the connection and board

Run `esptool.py` to get the `flash_id` details. For example:

```shell
esptool.py --port /dev/tty.usbserial-0001 flash_id
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --port /dev/tty.usbserial-0001 flash_id
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting....
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 80:ce:f8:4a:ee:d4
Uploading stub...
Running stub...
Stub running...
Manufacturer: c8
Device: 4017
Detected flash size: 8MB
Hard resetting via RTS pin...
```

</p>
</details>

### Erase the board's flash

Run `espstool.py` to `erase_flash` on the board. For example:

```shell
esptool.py --port /dev/tty.usbserial-0001 erase_flash
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --port /dev/tty.usbserial-0001 erase_flash
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting.....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting......
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 80:ce:f8:4a:ee:d4
Uploading stub...
Running stub...
Stub running...
Erasing flash (this may take a while)...
Chip erase completed successfully in 13.3s
Hard resetting via RTS pin...
```

</p>
</details>

### Write the board's firmware

Run `esptool.py` to `write_flash` to the board's flash memory. For example:

```shell
esptool.py --chip esp32 --port /dev/tty.usbserial-0001 write_flash -z 0x1000 
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --chip esp32 --port /dev/tty.usbserial-0001 write_flash -z 0x1000 ESP32_GENERIC-20231227-v1.22.0.bin 
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting....
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 80:ce:f8:4a:ee:d4
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Flash will be erased from 0x00001000 to 0x001a9fff...
Compressed 1737664 bytes to 1143562...
Wrote 1737664 bytes (1143562 compressed) at 0x00001000 in 101.2 seconds (effective 137.3 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```

</p>
</details>

## Do Python :tada:

Use `mpremote` to connect to the REPL on the serial console. For example:

```shell
mpremote connect /dev/tty.usbserial-0001 repl
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % mpremote connect list                        
/dev/cu.Bluetooth-Incoming-Port None 0000:0000 None None
/dev/cu.usbserial-0001 0001 10c4:ea60 Silicon Labs CP2102 USB to UART Bridge Controller
(micropython) % mpremote connect /dev/tty.usbserial-0001 repl
Connected to MicroPython at /dev/tty.usbserial-0001
Use Ctrl-] or Ctrl-x to exit this shell

>>> print('Hello, World!')
Hello, World!
```

</p>
</details>

Now run some code! The esp8266 tutorial will walk you through some first steps. :
http://docs.micropython.org/en/v1.22.0/esp8266/tutorial/repl.html

Does it work? These were pretty exciting on the Wifi Kit 32 v2:

```python
import machine
pin = machine.Pin(25, machine.Pin.OUT)
pin.on()
pin.off()
```

### Install packages

The firmware you installed may include all the packages you need. If you need something else, check out what's available in **micropython/micropython-lib** on GitHub:
https://github.com/micropython/micropython-lib

In case you need a package that's not already installed, Micropython includes [a package manager called `mip`](https://docs.micropython.org/en/latest/reference/packages.html#installing-packages-with-mip). If you hook it up to a network, you can install packages via the REPL. And, if your device is not on a network, use `mpremote` to run `mip`. For example:

```shell
mpremote connect /dev/tty.usbserial-0001 mip install ssd1306
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % mpremote connect /dev/tty.usbserial-0001 mip install ssd1306
Install ssd1306
Installing ssd1306 (latest) from https://micropython.org/pi/v2 to /lib
Installing: /lib/ssd1306.mpy
Done
```

</p>
</details>

## Run local files on the board

### `mpremote run`

```shell
mpremote connect /dev/tty.usbserial-0001 run esp32_hello.py
```

### `mpremote cp`

`mpremote` provides several `fs` commands, including `cp`. When specifying paths, use `:` to indicate the board's filesystem.

Upload **hwconfig.py** from working directory to board:

```shell
mpremote connect /dev/tty.usbserial-0001 fs cp hwconfig.py :hwconfig.py
```

Download **boot.py** from board to working directory:

```shell
mpremote connect /dev/tty.usbserial-0001 fs cp :boot.py boot.py
```
