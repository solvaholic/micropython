from hwconfig import OLED

oled = OLED()

oled.fill(0)
oled.text('Hello, World!', 12, 20)
oled.show()
