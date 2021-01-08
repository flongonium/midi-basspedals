/*
 * octave.h
 *
 *  Created on: 08.01.2021
 *      Author: lucab
 */

#ifndef OCTAVE_H_
#define OCTAVE_H_
/* This code allows to change octaves by pressing buttons
 *  @todo Include new button for reset
 *        Include LEDs, to show how many octaves are switched up or down. Or LED to show when default (12) is active.
 */
#include <Arduino.h>
/* ----------------------OCTAVE General----------------------------- */
#define DEBOUNCE 1500

int octaveUpPin         = 2;
int buttonStateUp       = 0;
int lastButtonStateUp   = 0;
int octaveDownPin       = 4;
int buttonStateDown     = 0;
int lastButtonStateDown = 0;
int keyOffset           = 12;

/* ----------------------OCTAVE Switching----------------------------- */
/*2 Buttons to in-, or decrease offset, one button to reset offset to default value
 @todo insert LEDS for visualization of either octave is tuned up or down.
 */

void octaveSetup()
{
  pinMode(octaveUpPin, INPUT_PULLUP);
  pinMode(octaveDownPin, INPUT_PULLUP);
}

void octaveUp()
{
  buttonStateUp = digitalRead(octaveUpPin);

  if (buttonStateUp != lastButtonStateUp)
  {
    if (buttonStateUp == LOW)
    {
      keyOffset = keyOffset + 12;
    }
    delay(50);     // Delay a little bit to avoid bouncing
  }
  lastButtonStateUp = buttonStateUp;
}

void octaveDown()
{
  buttonStateDown = digitalRead(octaveDownPin);

  if (buttonStateDown != lastButtonStateDown)
  {
    if (buttonStateDown == LOW)
    {
      keyOffset = keyOffset - 12;
    }
    delay(50);     // Delay a little bit to avoid bouncing
  }
  lastButtonStateDown = buttonStateDown;
}




#endif /* OCTAVE_H_ */
