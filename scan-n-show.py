# https://docs.micropython.org/en/latest/esp32/quickref.html#wlan

from hwconfig import WLAN_STA, OLED
import time

wlan = WLAN_STA()
oled = OLED()
txt = "{:<9} {:>2} {:>3}"

while True:

    res = wlan.sta.scan()

    oled.fill(0)

    apcount = 0

    for ap in res:
        if ap[0] == b'':
            continue
        oled.text(txt.format(ap[0].decode('utf-8')[:9], ap[2], ap[3]), 0, apcount * 9)
        apcount += 1
        if apcount >= 7:
            break

    oled.show()

    time.sleep(5)
