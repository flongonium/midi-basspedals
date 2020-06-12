//First attempt to control the LEDS on the Bass pedal Boards.

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
