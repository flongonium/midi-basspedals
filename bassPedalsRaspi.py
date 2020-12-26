# With this file, the Raspi reads the pin's values

import RPi.GPIO as GPIO
import serial
import os


# pre-processing and set-up
GPIO.setmode(GPIO.BOARD)

keyVelocity = 127
DEBOUNCE = 1500


pin = (40, 38, 37, 36, 35, 33, 32, 31, 29, 26, 24, 23, 22)
midiKey = (24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12)

# pinMidiKey is a c-like structure approach:
# 40:[24, 0, 0]
# |   |   |  |
#pin  |   |  |
# midiKey |  |
#   debounce |
#        keySent

pinMidiKey = {
    40:[24, 0, 0],
    38:[23, 0, 0],
    37:[22, 0, 0],
    36:[21, 0, 0],
    35:[20, 0, 0],
    33:[19, 0, 0],
    32:[18, 0, 0],
    31:[17, 0, 0],
    29:[16, 0, 0],
    26:[15, 0, 0],
    24:[14, 0, 0],
    23:[13, 0, 0],
    22:[12, 0, 0]
}
debounce = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
keySent = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]


# Function definitions

def portSetup():
    ser = serial.Serial()
    #ser.baudrate

def pinSetup():
    for i in pin:
        GPIO.setup(i, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def midiSend(midiCommand, byte1, byte2):
    serial.write(midiCommand)
    serial.write(byte1)
    serial.write(byte2)

def noteOn(midiKey):
    midiSend(0x90, midiKey, keyVelocity)

def noteOff(midiKey):
    midiSend(0x80, midiKey, keyVelocity)

def keyEvents():
    while True:
        for i in pinMidiKey:
            
            val = GPIO.input(i)
            print(f'GPIO INPUT READ: {i}')

            if pinMidiKey[i][1] == 0:                      #Key has been off
                if val == 0:                               #Key is now on
                    # send note on to virtual usb
                    # noteOn(pinMidiKey[i][0])
                    pinMidiKey[i][2] = pinMidiKey[i][0]
                    pinMidiKey[i][1] = DEBOUNCE
                    print('NoteOn')
                    print(pinMidiKey[i][1])
                else:                                      #Key has been on
                    if val == 1:                           #Key has gone off
                        if pinMidiKey[i][1] == 0:
                            # send note off to virtual usb
                            # noteOff(pinMidiKey[i][0])
                            print('noteOff')
                        else:
                            pinMidiKey[i][1] = DEBOUNCE

pinSetup()
keyEvents()
