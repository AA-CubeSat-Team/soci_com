//CRC-32 function for the communication system intended to be used on the Soci cubesat.
//https://github.com/efreneau/SOCi-Satellite-Communication

//adapted code from https://github.com/intel/soft-crc/blob/master/crc.c
//Polynomial obtained from https://users.ece.cmu.edu/~koopman/crc/
//verified with http://www.sunshine2k.de/coding/javascript/crc/crc_js.html

//Able to detect 32 bit burst errors and all 6-bit error patterns in sequences up to 4092 B.
//Uses polynomial of 0x9960034c with results reflected.

//Another option can detect 32 bit burst errors and all 7-bit error patterns in sequences up to 124 B;
//Uses polynomial of 0xf8c9140a with results reflected.

//Check the Koopman website to find the most up to date ideal polynomial. Both of these are liable to change.

#ifndef _crc32_custom_h
#define _crc32_custom_h

uint_fast32_t crc32_custom(uint_fast32_t crc, const uint_fast8_t *buf, const size_t len);

#endif
