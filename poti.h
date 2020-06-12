/* This code allows to change in Software assigned controls by turning potis
 *  ATTENTION: Same Analog inputs are used in led.h!
 */
/* --------------------- Control of poti on MidiShield ------------------------*/

int midiCommand           = 176; // Midi Command nr: 4, Midi Channel 1 --> 10110000
int potiPin[]             = {A0, A1};
int controllerNumber[]    = {21, 22};
long int controllerVal[]  = {0, 0};
int controllerValOld[]    = {0, 0};
long int potiVal[]        = {0, 0};


void readPotentiometer(){
  for(int i=0; i<2; i++) 
  {
    potiVal[i] = analogRead(potiPin[i]);
    controllerVal[i] = map(potiVal[i], 0, 1023, 0, 127);
  
    if (controllerVal[i] != controllerValOld[i])
    {
      Serial.write(midiCommand);
      Serial.write(controllerNumber[i]);
      Serial.write(controllerVal[i]);

      /*
      Serial.println(midiCommand);
      Serial.println(controllerNumber[i]);
      Serial.println(controllerVal[i]);
      */
    }
  controllerValOld[i] = controllerVal[i];
  }
}
