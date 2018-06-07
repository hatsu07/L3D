import os
import sys
import socket
import json


# 受信データをdict型に加工
def preprocessing(data):
    lists = data.split()
    lists.pop(0)
    s = ''.join(lists)
    js = json.loads(s)
    return js

def writeValue():
    sys.path.insert(0, '/usr/lib/python2.7/bridge')

    from bridgeclient import BridgeClient as bc
    value = bc()

    host = '192.168.11.192'
    port = 5000

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((host, port))

    while True:
        data, addr = sock.recvfrom(1024)        # データ受信
        js = preprocessing(data)

        if 'recog' in js:
            value.put('v', str(js['recog']))    # 領域'v'に値str(js['recog'])を保存
        if 'val' in js:
            value.put('v', str(js['val']))      # 保存できる値は文字列のみの仕様らしい
        if 'num' in js:
            value.put('n', str(js['num']))

def fork():
    pid = os.fork()

    if pid > 0:
        f = open('/var/run/gpio_fan_controld.pid','w')
        f.write(str(pid)+"\n")
        f.close()
        sys.exit()

    if pid == 0:
        writeValue()

if __name__ == '__main__':
    fork()
    # writeValue()
