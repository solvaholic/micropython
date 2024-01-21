# https://github.com/micropython/micropython/blob/v1.22.0/examples/hwapi/README.md
#
# Seeed Studio esp32s3
#
from machine import SoftI2C, Pin, Signal
from network import WLAN, AP_IF, STA_IF

# Onboard LED
LED = Signal(21, Pin.OUT, invert=True)

# Use WLAN as a station
# https://docs.micropython.org/en/latest/esp32/quickref.html#wlan
# Usage: from hwconfig import WLAN_STA
#        wlan = WLAN_STA()
class WLAN_STA():
    def __init__(self, ssid='', key='', active=True):
        # Deactivate any active WLAN interface
        WLAN(STA_IF).active(False)
        WLAN(AP_IF).active(False)
        # create station interface
        self.sta = WLAN(STA_IF)
        # activate or deactivate the interface
        self.sta.active(active)
        # connect to an AP, if credentials provided
        if active and ssid and key:
            self.sta.connect(ssid, key)
            # TODO: wait for connection

# Host a WiFi access point
# https://docs.micropython.org/en/latest/esp32/quickref.html#wlan
# Usage: from hwconfig import WLAN_AP
#        wlan = WLAN_AP()
class WLAN_AP():
    def __init__(self, ssid='ESP-AP', max_clients=10, active=True):
        # Deactivate any active WLAN interface
        WLAN(STA_IF).active(False)
        WLAN(AP_IF).active(False)
        # create access-point interface
        self.ap = WLAN(AP_IF)
        # set the SSID of the access point
        self.ap.config(ssid=ssid)
        # set how many clients can connect to the network
        self.ap.config(max_clients=max_clients)
        # activate or deactivate the interface
        self.ap.active(active)
