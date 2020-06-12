/* This code allows to change the color of the RGB LED strip by turning potentiometers
 *  All other LEDS are turned on
 *  @todo 
 *  Include new button for reset
 *  Include LEDs, to show how many octaves are switched up or down. Or LED to show when default (12) is state.
 */
 
/* --------------------- LED General --------------------------*/
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
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

/* This code was used for normal LEDS to dimm with PWM. It didn't work, due to use of delay. Just here as an archive */
/*
void led_setup(){
  struct LED {
    int pin;
    int led_nr;
  };
  
  struct LED LEDS[] = {
    {28, 0},              // Db
    {30, 1},              // D
    {32, 2},              // Eb
    {34, 3},              // E
    {36, 4},              // F
    {38, 5},              // Gb
    {40, 6},              // G
    {42, 7},              // Ab
    {44, 8},              // A
    {46, 9},              // Bb
    {48, 10},             // B
    {50, 11},             // c
    {52, 12}              // C
  };
}

void ledFadeIn(int led_pin) {
  for (int x = 1; x <= 255; x++) {
    digitalWrite(led_pin, x);
    delay(2);  
  }
}

void ledFadeOut(int led_pin) {
  for (int x = 255; x >= 0; x--) {
    digitalWrite(led_pin, x);
    delay(20);  
  }
}
*/
