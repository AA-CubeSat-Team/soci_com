#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "COBS.h"

size_t StuffData(const uint_fast8_t *ptr, const size_t length, uint_fast8_t *dst)
{
	const uint_fast8_t *start = dst, *end = ptr + length;
	uint_fast8_t code, *code_ptr; // Where to insert the leading count
	StartBlock();
	
	while (ptr < end) {//loop over data
		if (code != 0xFF) {
			uint_fast8_t c = *ptr++;
			if (c != 0) {
				*dst++ = c;
				code++;
				continue;
			}
		}
		FinishBlock();
		StartBlock();
	}
	FinishBlock();
	return dst - start;
}

size_t UnStuffData(const uint_fast8_t *ptr, const size_t length, uint_fast8_t *dst)
{
	const uint_fast8_t *start = dst, *end = ptr + length;
	uint_fast8_t code = 0xFF, copy = 0;

	for (; ptr < end; copy--) {
		if (copy != 0) {
			*dst++ = *ptr++;
		} else {
			if (code != 0xFF)
				*dst++ = 0;
			copy = code = *ptr++;
			if (code == 0)
				break;
		}
	}
	return dst - start;
}



