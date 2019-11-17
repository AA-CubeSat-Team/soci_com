#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

#include "crc32_custom.h"

int main()
{
	const int packet_length = 245; 
	uint_fast8_t s[packet_length];
	
	//Generate
	uint_fast32_t crc_digest;
	int i;
	srand(time(0));
	for (i=0;i<packet_length;i++){
		s[i]=(rand()%26)+65;
	}
	
	printf("Random Payload (%d Bytes).\n",packet_length);
	
	double time_spent = 0.0;
	clock_t begin = clock();
	crc_digest = crc32_custom(0, s, packet_length);
	clock_t end = clock();
	
	//CRC-32
	printf("=================================\n");
	printf("CRC-32: 0x%x\n", crc_digest);
	
	time_spent = (double)(end - begin)*1000000 / CLOCKS_PER_SEC;

	printf("Time elpased is %d microseconds.\n", (int)time_spent);
	printf("Total Size: 254 Bytes (+4).");
	printf("\n=================================\n");
	return 0;
}
