# @solvaholic pulled together a few references to make this work:
# * https://docs.micropython.org/en/latest/esp32/quickref.html#wlan
# * https://github.com/micropython/micropython/blob/v1.22.0/examples/network/http_server.py
# * https://electrocredible.com/micropython-web-server-tutorial-examples/
# 
# TODO: Use @route('/LED/on') and @route('/LED/off') handlers
# * https://github.com/orgs/micropython/discussions/12219

from hwconfig import WLAN_AP, LED
import socket

wlan = WLAN_AP(ssid='wifikit32ap', max_clients=10, active=True)

CONTENT = b"""\
HTTP/1.0 200 OK

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>web_server.py</title>
  <style>
    html {
      font-family: Tahoma, Helvetica, sans-serif;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    
    h1 {
      font-family: Tahoma, Helvetica, sans-serif;
      color: #2551cc;
    }
    
    .button1,
    .button2 {
      -webkit-border-radius: 10;
      -moz-border-radius: 10;
      border-radius: 10px;
      font-family: Tahoma, Helvetica, sans-serif;
      color: #ffffff;
      font-size: 30px;
      padding: 10px 20px 10px 20px;
      text-decoration: none;
      display: inline-block;
      margin: 5px;
    }
    
    .button1 {
      background: #339966;
    }
    
    .button2 {
      background: #993300;
    }
  </style>
</head>

<body>
  <h1>web_server.py</h1>
  <p>%s</p>
  <p>
    <a href="/LED/on"><button class="button1">LED ON</button></a>
    <a href="/LED/off"><button class="button2">LED OFF</button></a>
  </p>
</body>
</html>
"""

def main(micropython_optimize=False):
    s = socket.socket()

    # Binding to all interfaces - server will be accessible to other hosts!
    ai = socket.getaddrinfo("0.0.0.0", 8080)
    print("Bind address info:", ai)
    addr = ai[0][-1]

    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(addr)
    s.listen(5)
    print("Listening, connect your browser to http://<this_host>:8080/")

    while True:
        client_sock, client_addr = s.accept()
        # client_sock = res[0]
        # client_addr = res[1]
        print("Client address:", client_addr)
        print("Client socket:", client_sock)

        if not micropython_optimize:
            # To read line-oriented protocol (like HTTP) from a socket (and
            # avoid short read problem), it must be wrapped in a stream (aka
            # file-like) object. That's how you do it in CPython:
            client_stream = client_sock.makefile("rwb")
        else:
            # .. but MicroPython socket objects support stream interface
            # directly, so calling .makefile() method is not required. If
            # you develop application which will run only on MicroPython,
            # especially on a resource-constrained embedded device, you
            # may take this shortcut to save resources.
            client_stream = client_sock

        # Print the request
        print("Request:")
        req = client_stream.readline()
        print(req)
        while True:
            h = client_stream.readline()
            if h == b"" or h == b"\r\n":
                break
            print(h)
        
        # Handle requests '/LED/on' and '/LED/off'
        LED_on = req.find(b'/LED/on')
        LED_off = req.find(b'/LED/off')
        if LED_on > 0:
            print("LED is on")
            LED.value(1)
        if LED_off > 0:
            print("LED is off")
            LED.value(0)
        if LED.value() == 0:
            LED_state = "LED is OFF"
        else:
            LED_state = "LED is ON"

        client_stream.write(CONTENT % LED_state)

        client_stream.close()
        if not micropython_optimize:
            client_sock.close()

        print()

main(micropython_optimize=True)
