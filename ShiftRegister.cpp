/* 
	ShiftRegister.cpp
	Simple library for controlling a 74HC595 shift register.
	Created by Sean Underwood, 1 January 2014
	Released into the public domain.
*/

#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin,
	 													 uint8_t registerCount) 
{
	_data = dataPin;
	_clock = clockPin;
	_latch = latchPin;
	_registerCount = registerCount;
	
	pinMode(_data, OUTPUT);
	pinMode(_clock, OUTPUT);
	pinMode(_latch, OUTPUT);
}

void ShiftRegister::write(byte data) 
{
	write(&data, 1);
}

void ShiftRegister::write(byte* data)
{
	write(data, _registerCount);
}

void ShiftRegister::write(byte* data, uint8_t count)
{
	// Set the latch pin low to prepare for updating.
  digitalWrite(_latch, LOW);

	// Loop backwards - last 595 chip gets the first data to go in.
	for(char j = count - 1; j >= 0; j--)
	{
	  // Loop backwards - 595's last output bit is the first one to go in. 
		for(char i = 7; i >= 0; i--) {
		
			// Bring clock LOW to prepare to write a bit	  
	    digitalWrite(_clock, LOW);
		
			// Write the bit to the data pin
	    if(data[j] & 0x1 << i) {
	      digitalWrite(_data, HIGH);
	    } else {
	      digitalWrite(_data, LOW);
	    }
		
			// Shift register loads the data when the clock pin goes HIGH.
	    digitalWrite(_clock, HIGH);

	  }
	}
	
	// Shift register contents get sent to the 595's output pins
	// when latch goes HIGH.
  digitalWrite(_latch, HIGH);
}