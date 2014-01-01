#include "ShiftRegister.h"

// Initializes a ShiftRegister.
// Parameters:
//   dataPin:  Serial data input. Labeled Ds on the 595
//   clockPin: Used to trigger reading from the data pin.  
//             Labeled SHcp on the 595.
//   latchPin: Used to trigger transferring data from the
//             shift register to the storage register (output).
//             Labeled STcp on the 595
ShiftRegister::ShiftRegister(int dataPin, int clockPin, int latchPin) 
{
	_data = dataPin;
	_clock = clockPin;
	_latch = latchPin;
	
	pinMode(_data, OUTPUT);
	pinMode(_clock, OUTPUT);
	pinMode(_latch, OUTPUT);
}

void ShiftRegister::write(char data) 
{
	// Set the latch pin low to prepare for updating.
    digitalWrite(_latch, LOW);
  
    // Loop backwards - 595's last output bit is the first one to go in. 
		for(int i = 7; i >= 0; i--) {
			
			// Bring clock LOW to prepare to write a bit	  
      digitalWrite(_clock, LOW);
			
			// Write the bit to the data pin
      if(data & 0x1 << i) {
        digitalWrite(_data, HIGH);
      } else {
        digitalWrite(_data, LOW);
      }
			
			// Shift register loads the data when the clock pin goes HIGH.
      digitalWrite(_clock, HIGH);

			// Not sure this is necessary - the ShiftOut tutorial
			// does it "to prevent bleed through"
      // digitalWrite(ds, LOW);
    }
		
		// Shift register contents get sent to the 595's output pins
		// when latch goes HIGH.
    digitalWrite(_latch, HIGH);
}