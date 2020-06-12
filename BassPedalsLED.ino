#include "octave.h"
#include "led.h"
#include "keys.h"
#include <SPI.h>

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
  Serial.begin(115200);  //start serial with midi baudrate 31250, for programming use 38400. In combination with serial computing, use 115200 or assigned value 
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
