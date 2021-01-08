/*
 * led.h
 *
 *  Created on: 08.01.2021
 *      Author: lucab
 */

#ifndef LED_H_
#define LED_H_

/* This code allows to change the color of the RGB LED strip by turning potentiometers
 *  All other LEDS are turned on
 *  @todo
 *  Include new button for reset
 *  Include LEDs, to show how many octaves are switched up or down. Or LED to show when default (12) is state.
 */
#include <Arduino.h>

/* --------------------- LED General --------------------------*/
#include <Adafruit_NeoPixel.h>
const int ledCover    = 25;

const int colorButtonPin1 = 2;
const int colorButtonPin2 = 4;

const int ledPin      = 27;
const int numOfLed    = 16;
long      rgbOld[]    = {0, 0, 0};
long      rgb[]       = {255, 50, 0};
int       potiPin[]   = {A8, A6, A4};
long      potiVal[]   = {0, 0, 0};


Adafruit_NeoPixel pixels  = Adafruit_NeoPixel(numOfLed, ledPin, NEO_GRB + NEO_KHZ800);


/* --------------- LED Setup ------------------------------*/
void ledSetup()
{
  // LED Strip
  pinMode(colorButtonPin1, INPUT_PULLUP);
  pinMode(colorButtonPin2, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(100);

  for(int i=0;i<numOfLed;i++)
  {
    pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(250);
  }

  // Analog LEDs
  pinMode(ledCover, OUTPUT);
  digitalWrite(ledCover, HIGH);
}


/* -------------------- RGB Strip Color change with potis --------------------- */
/* @todo remove lag; if code is initialized, not on -> not off goes approx. 14sec. Why? */

void ledColorChange()
{
  for(int i=0; i<3; i++)
  {
    potiVal[i] = analogRead(potiPin[i]);
    rgb[i] = map(potiVal[i], 0, 1023, 0, 255);
    if(rgb != rgbOld)
    {
      for(int i=0;i<numOfLed;i++)
      {
        pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
        pixels.show();
      }
    }
    rgbOld[i] = rgb[i];
  }
}

#endif /* LED_H_ */
