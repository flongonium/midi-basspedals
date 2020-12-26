import os
import time

def connection_setup():
    os.system('sudo ttymidi -s /dev/ttyACM0 -v &')

def connection_link():
    os.system('aconnect 128:0 20:0')

time.sleep(5)
connection_setup()
time.sleep(3)
connection_link()
