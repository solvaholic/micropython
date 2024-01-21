Get started with MicroPython on ESP32

## Downaload firmware

Download the latest appropriate .bin file for your board from **micropython.org**:
<https://micropython.org/download>

The examples in this document were developed with:

* [**ESP32_GENERIC-20240105-v1.22.1.bin**](https://micropython.org/resources/firmware/ESP32_GENERIC-20240105-v1.22.1.bin) on a [Heltec Wifi Kit 32 v2](https://resource.heltec.cn/download/WiFi_Kit_32/WiFi%20Kit32.pdf).
* [ESP32_GENERIC_S3-20240105-v1.22.1.bin](https://micropython.org/resources/firmware/ESP32_GENERIC_S3-20240105-v1.22.1.bin) on a [Seeed Studio XIAO ESP32S3](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)

## Activate virtual environment

If you don't already have a Python virtual environment, create one with `python3 -m venv .`.

Activate the virtual environment:

```bash
source bin/activate
```

## Install required packages

Run **script/bootstrap.sh** or use `pip` to install `esptool.py`, `mpremote`, and other required packages:

```bash
pip install -r requirements.txt
```

After installing packages, you may need to `deactivate` and `source bin/activate` the virtual environment again, to get new commands into your path.

## Flash firmware

Check out [the published instructions](https://docs.micropython.org/en/latest/esp32/tutorial/intro.html). If this is your first time using MicroPython, compare those instructions to a user-provided walk-through using a platform similar to yours, for example [_MicroPython on an ESP32 Board With Integrated SSD1306 OLED Display (WEMOS/Lolin)_](https://www.instructables.com/MicroPython-on-an-ESP32-Board-With-Integrated-SSD1/).

If there are notes for your board in [**docs/boards.md**](boards.md), check those now for any special instructions.

Note: Your actual `--port` will vary. It will usually look like **/dev/tty.usb\*** on macOS.

### Check the connection and board

Run `esptool.py` to get the `flash_id` details. For example:

```shell
esptool.py --port /dev/tty.usb* flash_id
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --port /dev/tty.usb* flash_id  
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting......
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting.......
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 30:ae:a4:bb:47:40
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
esptool.py --port /dev/tty.usb* erase_flash
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --port /dev/tty.usb* erase_flash
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting.........
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting.....
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 30:ae:a4:bb:47:40
Uploading stub...
Running stub...
Stub running...
Erasing flash (this may take a while)...
Chip erase completed successfully in 7.7s
Hard resetting via RTS pin...
```

</p>
</details>

### Write the board's firmware

**_Note: Commands shown here are one example, and different boards differ. See [**boards.md**](boards.md) for board-specific instructions._**

Run `esptool.py` to `write_flash` to the board's flash memory. For example:

```shell
esptool.py --chip esp32 --port /dev/tty.usb* --baud 460800 write_flash -z 0x1000 ESP32_GENERIC-20240105-v1.22.1.bin
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % esptool.py --chip esp32 --port /dev/tty.usb* --baud 460800 write_flash -z 0x1000 ESP32_GENERIC-20240105-v1.22.1.bin
esptool.py v4.7.0
Serial port /dev/tty.usbserial-0001
Connecting....
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 26MHz
MAC: 30:ae:a4:bb:47:40
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 460800
Changed.
Configuring flash size...
Flash will be erased from 0x00001000 to 0x001a9fff...
Compressed 1737664 bytes to 1143562...
Wrote 1737664 bytes (1143562 compressed) at 0x00001000 in 29.8 seconds (effective 467.0 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```

</p>
</details>

## Do Python :tada:

Use `mpremote` to connect to the REPL on the serial console. For example:

```shell
mpremote connect /dev/tty.usb* repl
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % mpremote connect list
/dev/cu.Bluetooth-Incoming-Port None 0000:0000 None None
/dev/cu.usbserial-0001 0001 10c4:ea60 Silicon Labs CP2102 USB to UART Bridge Controller

(micropython) % mpremote connect /dev/tty.usb* repl
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
mpremote connect /dev/tty.usb* mip install ssd1306 aioble
```

<details><summary>Expand to see example output.</summary>
<p>

```text
(micropython) % mpremote connect /dev/tty.usb* mip install ssd1306 aioble
Install ssd1306
Installing ssd1306 (latest) from https://micropython.org/pi/v2 to /lib
Installing: /lib/ssd1306.mpy
Done
Install aioble
Installing aioble (latest) from https://micropython.org/pi/v2 to /lib
Installing: /lib/aioble/__init__.mpy
Installing: /lib/aioble/core.mpy
Installing: /lib/aioble/device.mpy
Installing: /lib/aioble/peripheral.mpy      
Installing: /lib/aioble/server.mpy
Installing: /lib/aioble/central.mpy         
Installing: /lib/aioble/client.mpy          
Installing: /lib/aioble/l2cap.mpy           
Installing: /lib/aioble/security.mpy
Done
```

</p>
</details>

## Run local files on the board

### `mpremote run`

To run a script in your working directory _on the board_, use the **script/run.sh** wrapper:

```shell
./script/run.sh esp32_hello.py
```

Or run `mpremote` directly:

```shell
mpremote connect /dev/tty.usb* run esp32_hello.py
```

### `mpremote fs`

`mpremote` provides several `fs` commands, including `cp`. Use `mpremote fs cp` to copy files to and from the board. When specifying paths, use `:` to indicate the board's filesystem.

Upload **hwconfig.py** from working directory to board:

```shell
mpremote connect /dev/tty.usb* fs cp hwconfig.py :hwconfig.py
```

Download **boot.py** from board to working directory:

```shell
mpremote connect /dev/tty.usb* fs cp :boot.py boot.py
```

Other useful `mpremote fs` commands include `ls`, `cat`, and `rm`. See [`mpremote`'s README](https://github.com/micropython/micropython/blob/master/tools/mpremote/README.md) for more details.
