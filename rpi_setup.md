Set up a Raspberry Pi 3 to collect data from sensors via Bluetooth Low Energy (BLE).

## Prerequisites

The `bluez` package is already installed on the Pi I'm using. Did I put it there? Did I add a package source? I don't remember. Need to verify next time I set up a Pi.

This one's running Raspbian Lite Bullseye. Seems like `bluez` is either built in or readily available with `apt get`:

> ```text
> $ cat /etc/apt/sources.list /etc/apt/sources.list.d/*
> deb http://deb.debian.org/debian bullseye main contrib non-free
> deb http://security.debian.org/debian-security bullseye-security main contrib non-free
> deb http://deb.debian.org/debian bullseye-updates main contrib non-free
> # Uncomment deb-src lines below then 'apt-get update' to enable 'apt-get source'
> #deb-src http://deb.debian.org/debian bullseye main contrib non-free
> #deb-src http://security.debian.org/debian-security bullseye-security main contrib non-free
> #deb-src http://deb.debian.org/debian bullseye-updates main contrib non-free
> deb http://archive.raspberrypi.org/debian/ bullseye main
> # Uncomment line below then 'apt-get update' to enable 'apt-get source'
> #deb-src http://archive.raspberrypi.org/debian/ bullseye main
> ```

## Basics

### Get your Bluetooth device name

Use `hciconfig` to learn about the Bluetooth device on your Raspberry Pi. In this document the device is called **hci0**.

### Reset your Bluetooth device

Want to reset the device? Close and open the device? Use `hciconfig` for those, too:

```shell
sudo hciconfig hci0 reset
sudo hciconfig hci0 down
sudo hciconfig hci0 up
```

### Scan for nearby BLE devices

Scan for nearby BLE devices. Check out `hcitool --help` for more options. This runs until you stop it with `Ctrl-C`:

```shell
sudo hcitool -i hci0 lescan
```

### Connect to a nearby BLE device

Run **ble_server.ino** on an ESP32, run :point_up: that scan, and grab the ESP32's MAC address. It's the first column of the output. For example:

> ```text
> 85:DC:C8:4A:EF:C6 ESP32 BLE Server Demo
> ```

Connect to the device and ask it what it does. If you have trouble connecting, try resetting your local device (see above) and your ESP32 (with the "RST" button). See `gatttool --help-all` for more options.

Here's some example output using the `connect`, `primary`, and `characteristics` commands in an interactive shell (`-I`):

> ```text
> $ sudo gatttool -i hci0 -t random -I -b 85:DC:C8:4A:EF:C6
> [85:DC:C8:4A:EF:C6][LE]> connect 85:DC:C8:4A:EF:C6
> Attempting to connect to 85:DC:C8:4A:EF:C6
> Connection successful
> 
> [85:DC:C8:4A:EF:C6][LE]> primary
> attr handle: 0x0001, end grp handle: 0x0005 uuid: 6f3bef01-0000-11ee-8be6-e3f5ee02cea1
> attr handle: 0x0014, end grp handle: 0x001c uuid: 6f3bef00-0000-11ee-8be6-e3f5ee02cea1
> attr handle: 0x0028, end grp handle: 0xffff uuid: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
> 
> [85:DC:C8:4A:EF:C6][LE]> characteristics 
> handle: 0x0002, char properties: 0x20, char value handle: 0x0003, uuid: 00002a05-0000-11ee-8be6-e3f5ee02cea1
> handle: 0x0015, char properties: 0x02, char value handle: 0x0016, uuid: 00002a00-0000-11ee-8be6-e3f5ee02cea1
> handle: 0x0017, char properties: 0x02, char value handle: 0x0018, uuid: 00002a01-0000-11ee-8be6-e3f5ee02cea1
> handle: 0x0019, char properties: 0x02, char value handle: 0x001a, uuid: 00002aa6-0000-11ee-8be6-e3f5ee02cea1
> handle: 0x0029, char properties: 0x0a, char value handle: 0x002a, uuid: beb5483e-36e1-4688-b7f5-ea07361b26a8
> ```

### Read and write to the connected device

Read some data, write it, and read it back. Here's some example output using the `char-read-hnd` and `char-write-req` commands in the same shell as above:

> ```text
> [85:DC:C8:4A:EF:C6][LE]> char-read-hnd 0x002a
> Characteristic value/descriptor: 48 65 6c 6c 6f 20 57 6f 72 6c 64 21 
> ```

Do those numbers look familiar? They're the [ASCII](https://en.wikipedia.org/wiki/ASCII) codes for "Hello World!".

> ```text
> [85:DC:C8:4A:EF:C6][LE]> char-write-req 0x002a 576f6f686f6f21
> Characteristic value was written successfully
> 
> [85:DC:C8:4A:EF:C6][LE]> char-read-hnd 0x002a
> Characteristic value/descriptor: 57 6f 6f 68 6f 6f 21 
> ```

## What next?

Now you have a Raspberry Pi that can connect to your ESP32 via BLE and read and write data. Using `gatttool` this way is probably cumbersome, for whatever you're trying to do.

Probably you'll want to read data from devices, write it to a database, and then do something with it. Maybe present a web page with a dashboard, forward the data to another service, or send an alert when certain criteria are met.
