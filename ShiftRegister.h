/* 
	ShiftRegister.h
	Simple library for controlling a 74HC595 shift register.
	Created by Sean Underwood, 1 January 2014
	
	Usage:
		Initialize by creating an instance and specifying the pins
		it should use for communicating with the 595.

		Write data by encoding the bits you want to write to the 
	 	shift register into a char, and passing that to the write() method.

	Limitations:
		The OE pin is not controlled by this libary, and must be controlled
	  	separately or hard-wired to LOW.  If held LOW, the 595 may initially output 
		garbage when first powered up.

	 	The MR pin is not supported.  Similar behavior can be achieved by
		calling ShiftRegister.write(0);

		The libary is not aware that the 74HC595 can be daisy chained, but
		can still be used to drive a set of them operating in series.  
	 	However, since it always flashes the latch pin to HIGH after writing
		a byte, some flickering will occur while data is being pushed through
		the registers.
*/

#ifndef __SHIFTREGISTER_H
#define __SHIFTREGISTER_H

#include "Arduino.h"

class ShiftRegister {
public:
	// Initializes a ShiftRegister.
	// Parameters:
	//   dataPin:  Serial data input. Labeled Ds on the 595
	//   clockPin: Used to trigger reading from the data pin.  
	//             Labeled SHcp on the 595.
	//   latchPin: Used to trigger transferring data from the
	//             shift register to the storage register (output).
	//             Labeled STcp on the 595
	ShiftRegister(int dataPin, int clockPin, int latchPin);
	
	// Writes data to the shfit register.
	// Parameters:
	//	 data:	A bitfield of data to send to the shift register.
	//					Least significant bit gets written to output in Q0.
	void write(char data);
private:
	int _data, _clock, _latch;
};


#endif