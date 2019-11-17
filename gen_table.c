//adapted code from https://github.com/intel/soft-crc/blob/master/crc.c
//Polynomial obtained from https://users.ece.cmu.edu/~koopman/crc/
//verified with http://www.sunshine2k.de/coding/javascript/crc/crc_js.html

//Able to detect 32 bit burst errors and all 6-bit error patterns in sequences up to 4092 B.
//Uses polynomial of 0x9960034c with results reflected.

//Another option can detect 32 bit burst errors and all 7-bit error patterns in sequences up to 124 B;
//Uses polynomial of 0xf8c9140a with results reflected.

//Check the Koopman website to find the most up to date ideal polynomial. Both of these are liable to change.

#include <stdio.h>
#include <stdint.h>

#include <stdlib.h>

uint32_t LUT[256];

void crc32_init_lut(const uint32_t poly, uint32_t *lut)
{
	uint_fast32_t i, j;

	if (lut == NULL)
		return;

	for (i = 0; i < 256; i++) {
		uint_fast32_t crc = (i << 24);

		for (j = 0; j < 8; j++)
			if (crc & 0x80000000L)
				crc = (crc << 1) ^ poly;
			else
				crc <<= 1;

		lut[i] = crc;
	}
}
int main(int argc, char **argv)
{
	uint32_t LUT[256];
	crc32_init_lut(0x9960034c, LUT);
	
	printf("const uint_fast32_t Crc32Lookup[256] = \n{\n");
	for (int i = 0; i <= 255; i++){
		if (i % 4 == 0)
			printf("\t");
		printf("0x%08x,", LUT[i]);
		if (i % 4 == 3)
			printf("\n");
	}
	printf("};");
	return 0;
}
