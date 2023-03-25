# pip3 install websocket-client

import websocket
import json
from websocket import create_connection

class subscriber:
    def listenForever(self):
        try:
            ws = create_connection("ws://192.168.0.32:8000")
            # ws = create_connection("ws://nbtstaging.westeurope.cloudapp.azure.com:9090/websocket")
            ws.send("test message")
            while True:
                result = ws.recv()
                result = json.loads(result)
                print("Received '%s'" % result)
                ws.close()
        except Exception as ex:
            print("exception: ", format(ex))

try:
    subscriber().listenForever()
except:
    print("Exception occured: ")
