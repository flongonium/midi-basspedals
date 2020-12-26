# Midi Controller with Raspberry Pi and Arduino
This project is based on the idea and codes of vanceg:
https://www.instructables.com/id/Build-MIDI-Bass-Pedals-for-About-150/

The idea is to build your own midi controller for live usage.
This project is extended with a Raspberry Pi as an interface for different midi sources and because the midi device (Moog Minitaur) could not understand the commands.

## Files
**USED:**
  * autoStartButtonExtended.py  --> simple code to shut down raspi properly
  * autoStartTtymidi.py         --> starts ttymidi automatically and sets up all connections 
  * setup_raspi.txt             --> some instructions to follow. 

**NOT USED:**
  * bassPedalsRaspi.c
  * bassPedals.Raspi.py
    * These have the same function as the .ino files, but are intended to run on the Raspy with its GPIO pins. In this way, no Arduino is needed
    It has not been tested, no functionality guaranteed.
  * Some .h files are not used and were just some ideas.

## Hardware
**Stuff used:**
* Arduino Mega2560
* Raspberry Pi 4
* Old Wurtlizer organ pedals
* Adressable RGB leds
* Standard leds
* Push buttons and faders


## Connections

MIDI Device   <-->   Rapsberry PI   <-- Arduino
