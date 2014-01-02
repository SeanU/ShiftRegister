/*
  BinaryCounter
  Binary counter demo for ShiftRegister library.
  Created by Sean Underwood, 1 January 2014
  Released into the public domain.
  
  Wiring:
    - Arduino pin 5 to 74HC595 pin 14 (Data input)
    - Arduino pin 6 to 74HC595 pin 11 (shift register clock)
    - Arduino pin 7 to 74HC595 pin 12 (storage register clock)
    
    - 74HC595 pin 8 (VSS) to ground
    - 74HC595 pin 16 (VCC) to +5V
    - 74HC595 pin 10 (reset) to +5V
    - 74HC595 pin 13 (enable) to ground
 */

#include <ShiftRegister.h>

#define dataPin  5
#define clockPin 6
#define latchPin 7

byte counter = 0;

ShiftRegister reg(dataPin, clockPin, latchPin);


void setup() 
{
  // do nothing
}

void loop() {
  reg.write(counter);

  counter++;  
  delay(250);
}
