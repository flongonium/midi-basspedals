/*
 * keys.h
 *
 *  Created on: 08.01.2021
 *      Author: lucab
 */

#ifndef KEYS_H_
#define KEYS_H_
/* This code is the main function to detect key events and send the MIDI messages via USB / MIDI connectors.
/* ----------------------- Control of keys -------------------------*/
#include <Arduino.h>
const int keyVelocity         = 127; // default dec = 100, bin = 01100100

struct key
{
    int pin;
    int midiKey;
    int debounce;
    int keySent;
};


struct key keys[] =
{
  { 29, 24, 0, 0 }   // Db red
  ,{ 31, 23, 0, 0 }  // D  red
  ,{ 33, 22, 0, 0 }  // Eb orange
  ,{ 35, 21, 0, 0 }  // E  orange
  ,{ 37, 20, 0, 0 }  // F  yellow
  ,{ 39, 19, 0, 0 }  // Gb green
  ,{ 41, 18, 0, 0 }  // G  green
  ,{ 43, 17, 0, 0 }  // Ab blue
  ,{ 45, 16, 0, 0 }  // A  blue
  ,{ 47, 15, 0, 0 }  // Bb violet
  ,{ 49, 14, 0, 0 }  // B  violet
  ,{ 51, 13, 0, 0 }  // c  brown
  ,{ 53, 12, 0, 0 }  // C  brown
  ,{ 0, 0, 0, 0 }     // end of list marker
};


void Midi_Send(int midiCommand, byte byte1 , byte byte2)
{
  Serial.write(midiCommand);
  Serial.write(byte1);
  Serial.write(byte2);
}

void noteOn(int midiKey)
{
  Midi_Send(0x90, midiKey, keyVelocity); // Default statusByte: 0x90
}

void noteOff(int midiKey)
{
  Midi_Send(0x80, midiKey, keyVelocity); // Default statusByte: 0x80
}

void keySetup()
{
  for(int i = 0; keys[i].pin != 0; ++i)
  {
    pinMode(keys[i].pin, INPUT_PULLUP);
  }
}

// Code for keys

void keyEvents()
{
  byte byte1;
  byte byte2;
  byte byte3;
  int value;

  //*************** MIDI THRU ******************//
//  if(Serial.available() > 0)
//  {
//    byte1 = Serial.read();
//    byte2 = Serial.read();
//    byte3 = Serial.read();
//    Midi_Send(byte1, byte2, byte3);
//  }

  // Look for bass pedal key events
  for(int i = 0; keys[i].pin != 0; ++i)
  {
    value = digitalRead(keys[i].pin);

    if(keys[i].debounce == 0)
    {                        // Key has been off
      if(value == LOW)       // Key is now on
      {
        noteOn(keys[i].midiKey + keyOffset);           // Send the MIDI note on message
        keys[i].keySent = keys[i].midiKey + keyOffset;
        keys[i].debounce = DEBOUNCE;                   // Set the note off debounce counter
        //Serial.println(keys[i].pin);
        //Serial.print("ON");
      }
    }
    else                            // Key has been on
    {
      if(value == HIGH)
      {                             // Key has gone off
        if(--keys[i].debounce == 0) // If Key has remained off for DEBOUNCE scans,
        {
          noteOff(keys[i].keySent); // In case the offset has changed, send MIDI off for the right note
          //Serial.println(keys[i].pin);
          //Serial.print("OFF");
        }
      }
      else                            // Key has not gone off
      {
        keys[i].debounce = DEBOUNCE;  // Reset debounce counter in case we got
      }                               // a small number of key off scans
    }
  }
}




#endif /* KEYS_H_ */
