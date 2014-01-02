/* 
	ShiftRegister.h
	Simple library for controlling a 74HC595 shift register.
	Created by Sean Underwood, 1 January 2014
	Released into the public domain.
	
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
	//	 registerCount:  Number of daisy-chained shift registers
	//							being controlled.  Default is 1.
	ShiftRegister(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, 
								uint8_t registerCount = 1);
	
	// Writes data to the shfit register.
	// Parameters:
	//	 data:	A bitfield of data to send to the shift register.
	//					Least significant bit gets written to output in Q0.
	void write(char data);
		
	// Writes data to the shfit register.
	// Parameters:
	//	 data:	An array of bitfields of data to send to the register.
	//				The length of the array should be equal to the number
	//				of shift registers configured in the contstructor.
	//				The contents of the first element in the array get written
	//				to the first register in the chain.
	void write(char* data);

private:
	uint8_t _data, _clock, _latch, _registerCount;
	
	void write(char* data, uint8_t count);
};


#endif