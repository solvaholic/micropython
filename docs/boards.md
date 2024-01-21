Information about boards used in this repo.

## Heltec WiFi Kit 32 v2

* https://micropython.org/download/?mcu=esp32 ("generic")
* https://docs.micropython.org/en/latest/esp32/quickref.html
* [Heltec WiFi Kit 32 PDF](https://resource.heltec.cn/download/WiFi_Kit_32/WiFi%20Kit32.pdf)
* [Heltec ESP32 Documentation](https://docs.heltec.org)
* [Heltec ESP32 Quick Start Guide](https://docs.heltec.org/en/node/esp32/esp32_general_docs/quick_start.html)
* [Heltec Community](http://community.heltec.cn)
* [Heltec WiFi Kit 32 Library](https://github.com/HelTecAutomation/Heltec_ESP32)
* [Heltec Framework](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/README.md)
* [Heltec Framework Pre-v3](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/0aaf0d08b20c2d67aab416ae632320ac11ca7ea6/README.md)

## Seeed Studio XIAO ESP32S3 (Sense)

* https://micropython.org/download/?mcu=esp32s3 ("generic_s3")
* https://docs.micropython.org/en/latest/esp32/quickref.html
* https://wiki.seeedstudio.com/XIAO_ESP32S3_Micropython/
* https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/

Follow [**get_started.md**](get_started.md), except...

### Write the board's firmware

```shell
# Install firmware
_bin=ESP32_GENERIC_S3-20240105-v1.22.1.bin # Use the latest
_port=/dev/tty.usbmodem3301                # The port will change
esptool.py \
--chip esp32s3 --baud 460800 --port $_port \
--before default_reset --after hard_reset \
write_flash --flash_mode dio --flash_size detect --flash_freq 80m \
0x0 $_bin
```
