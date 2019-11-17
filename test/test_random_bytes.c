#include "test_random_bytes.h"

int main()
{
	const int packet_length = 250; //size with header, size without is 245
	char s[packet_length];
	
	uint_fast32_t crc_digest;
	int i;
	srand(time(0));
	
	printf("=================================\n");
	printf("Create and Frame Packet\n");
	printf("=================================\n");
	
	//Generate
	for (i=0;i<packet_length;i++){
		s[i]=rand() % 256;//arbitrary
	}
	
	printf("Random Payload (245 Bytes).\nAdd Random Header\n");
	printf("New Size: 250 Bytes (+5).\n");
	
	double time_spent = 0.0;
	clock_t begin = clock();
	crc_digest = crc32_custom(0, s, 250);
	//printf("\n%x/n",strlen(s));
	clock_t end = clock();
	
	//CRC-32
	printf("=================================\n");
	printf("CRC-32: 0x%x\n", crc_digest);
	
	time_spent = (double)(end - begin)*1000000 / CLOCKS_PER_SEC;

	printf("Time for step is %d microseconds.\n", (int)time_spent);
	printf("New Size: 254 Bytes (+4).\n");
	
	//COBS
	printf("=================================\n");
	printf("COBS Substitution of 0x0\n");
	
	uint_fast8_t s_byte[254];
	uint_fast8_t out[255];
	
	//s_byte[0] = 0x0;//add start of frame
	
	for (i=0;i<250;i++)//payload
		s_byte[i]= (uint8_t) s[i];

	s_byte[250] = (crc_digest >> 24) & 0xFF;//add crc-32 as 4 8-bit entries
	s_byte[251] = (crc_digest >> 16) & 0xFF;
	s_byte[252] = (crc_digest >> 8) & 0xFF;
	s_byte[253] = crc_digest & 0xFF;
	
	begin = clock();
	StuffData(s_byte, 254, out);
	end = clock();
	
	time_spent = (double)(end - begin)*1000000 / CLOCKS_PER_SEC;

	printf("Time for step is %d microseconds.\n", (int)time_spent);
	printf("Total Size: 256 Bytes (+2).\n");
	
	printf("\n=================================\n");
	printf("Deframe and Check Packet\n");
	printf("=================================\n");
	printf("Undo COBS Substitution of 0x0\n");
	
	uint_fast8_t s_byte_hat[254];
	
	begin = clock();
	UnStuffData(out, 255, s_byte_hat);
	end = clock();
	
	time_spent = (double)(end - begin)*1000000 / CLOCKS_PER_SEC;
	
	uint_fast32_t crc_rx;
	uint_fast32_t crc_digest_hat;
	uint_fast8_t payload[250];

	for(i = 0;i < 250; i++)
		payload[i] = s_byte_hat[i];
	
	begin = clock();
	crc_rx = (s_byte_hat[250] << 24) + (s_byte_hat[251] << 16) + (s_byte_hat[252] << 8) + s_byte_hat[253];
	crc_digest_hat = crc32_custom(0, payload, 250);
	end = clock();
	
	printf("Time for step is %d microseconds.\n", (int)time_spent);
	printf("RX CRC: 0x%x\n", crc_rx);
	printf("=================================\n");
	printf("Check CRC of RX frame\n");
	printf("Computed CRC: 0x%x\n",crc_digest_hat);
	printf("Matches?: %s\n", (int) crc_rx == (int) crc_digest_hat ? "True":"False");
	time_spent = (double)(end - begin)*1000000 / CLOCKS_PER_SEC;
	printf("Time for step is %d microseconds.\n", (int)time_spent);
	printf("=================================\n");
	printf("Payload + Header (250 Bytes).\n");
	
	/*
	printf("DEBUG PAYLOAD\n");
	for (int i = 0; i < 250; i++){
		printf("0x%02x|", (uint_fast8_t) s[i]);
		if (i % 8 == 7)
			printf("\n");
	}
		printf("=================================\n");

	for (int i = 0; i < 250; i++){
		printf("0x%02x|", payload[i]);
		if (i % 8 == 7)
			printf("\n");
	}
	*/
	
	return 0;
}
