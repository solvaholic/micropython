# https://github.com/micropython/micropython/blob/v1.22.0/examples/hwapi/README.md
#
# Heltec Wifi Kit 32 v2
#
from ssd1306 import SSD1306_I2C
from machine import SoftI2C, Pin, Signal
from network import WLAN, AP_IF, STA_IF

# Onboard LED
LED = Signal(25, Pin.OUT, invert=False)

# Onboard OLED display
# https://forum.micropython.org/viewtopic.php?t=4002
class OLED(SSD1306_I2C):
    def __init__(self):
        # Set pin 16 to 1
        Pin(16, Pin.OUT).value(1)
        # Configure I2C
        oled_i2c = SoftI2C(scl=Pin(15), sda=Pin(4))
        # Call ss1306.SSD1306_I2C
        super(OLED, self).__init__(128, 64, oled_i2c)

# Host a WiFi access point
# https://docs.micropython.org/en/latest/esp32/quickref.html#wlan
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
