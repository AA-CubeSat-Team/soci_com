//COBS functions for the communication system intended to be used on the Soci cubesat.
//https://github.com/efreneau/SOCi-Satellite-Communication

#ifndef _COBS_h
#define _COBS_h

//functions used in StuffData
#define StartBlock()	(code_ptr = dst++, code = 1)
#define FinishBlock()	(*code_ptr = code)

size_t StuffData(const uint_fast8_t *ptr, const size_t length, uint_fast8_t *dst);
//StuffData performs COBS on a byte array.
//It returns the size of the resulting array.
//
//*ptr points to the input.
//length reffers to the input array.
//*dst points to the output.


size_t UnStuffData(const uint_fast8_t *ptr, const size_t length, uint_fast8_t *dst);
//UnStuffData reverses the COBS substitution.
//It returns the size of the resulting array.
//
//*ptr points to the COBS stuffed input.
//length reffers to the input array.
//*dst points to the UnStuffed output.

#endif
