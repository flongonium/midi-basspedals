#include "Arduino.h"
//The setup function is called once at startup of the sketch
#include "octave.h"
#include "led.h"
#include "keys.h"

int val_1;
int val_2;
/* ------------------- SETUP ------------------------*/
void setup()
{
  // Keys setup
  keySetup();

  // Octave
  octaveSetup();

  // LED Setup
  ledSetup();

  // Serial Com Init
  Serial.begin(38400);  //midi baudrate 31250, for programming/using with raspberry pi use ohter value
  //Serial.begin(31250, SERIAL_8E2);  //you might have to change byte structure (in my case SERIAL_8E2 for a moog minitaur) to use without raspberry pi
}


/* -------------------- LOOP ------------------------*/
void loop()
{
  // Key Event Function
  keyEvents();

  // Ocave Functions
  octaveUp();
  octaveDown();

  // LED Functions
/* @todo Idea: Insert Button, when pressed able to change color, if not pressed
 *  do not call function --> Delay is only when changing color, but then no note
 *  is played
 */
  val_1 = digitalRead(colorButtonPin1);
  val_2 = digitalRead(colorButtonPin2);
  if(val_1 == HIGH && val_2 == HIGH)
  {
    ledColorChange();
  }
}
