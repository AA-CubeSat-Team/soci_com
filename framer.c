//#include <inttypes.h>
//#include <stdio.h>
//#include <string.h>
//#include <time.h>
//#include <math.h>
//#include <stdlib.h>

#include "framer.h"

size_t create_segment(uint_fast8_t port, uint_fast16_t seq_num, uint_fast16_t ack, uint_fast8_t *in, const size_t length, uint_fast8_t *out){
	uint_fast8_t raw_frame[length+5]; //Header and payload
	uint_fast8_t segment[length+9]; //Header, payload and crc
	uint_fast8_t out_arr[length+11]; //COBS substitution and trailing 0x0
	
	//assign header
	raw_frame[0] = port; //data type
	raw_frame[1] = (seq_num >> 8) & 0xff; //seq_num first byte
	raw_frame[2] = seq_num & 0xff; //seq_num second byte
	raw_frame[3] = (ack >> 8) & 0xff; //ack first byte
	raw_frame[4] = ack & 0xff; //ack second byte
	
	int i;
	for (i=5;i<length+5;i++)//add payload to frame
		raw_frame[i] = *in++;
	
	uint_fast32_t crc_digest = crc32_custom(0, raw_frame, length+5);
	
	segment[length+5] = (crc_digest >> 24) & 0xFF;//add crc-32 as 4 entries in the byte array
	segment[length+6] = (crc_digest >> 16) & 0xFF;
	segment[length+7] = (crc_digest >> 8) & 0xFF;
	segment[length+8] = crc_digest & 0xFF;
	
	for (i=0;i<length+5;i++)
		segment[i] = raw_frame[i];
	
	StuffData(segment, length+9, out);
	
	out_arr[length+10] = 0x0; //explicitly add trailing 0
	
	for (i=0;i<length+11;i++)//payload
		*out++ = out_arr[i];
	return (size_t)(length+11);
}

size_t split_and_frame(uint_fast8_t port, uint_fast16_t ack, uint_fast8_t *in, const size_t length, const size_t target_payload_size, uint_fast8_t *out){
	const int target_packet_size = target_payload_size + 11;
	uint_fast8_t data[length];
	uint_fast8_t seg[target_payload_size+11];
	uint_fast16_t seq_num = 0;
	int total = length;
	int i;
	
	*out++ = 0x0;//add leading 0x0 (start of first frame)
	
	do{
		if(seq_num+target_payload_size<=length){
			for (i=0;i<target_packet_size;i++)//pack bytes to target_packet_size
				data[i] = *in++;
			total+=create_segment(port, seq_num, ack, data, target_packet_size, seg);
			for (i=0;i<target_packet_size+11;i++)//output segment
				*out = seg[i];
			seq_num+=target_packet_size;
		}else{
			int end = length % seq_num;
			uint_fast8_t data_last[end];
			uint_fast8_t seg_last[end+11];
			for (i=0;i<end;i++)//pack last bytes
				data_last[i] = *in++;
			total+=create_segment(port,seq_num,ack,data_last, end, seg_last);
			seq_num+=end;
		}
	}while(seq_num!=length);
	return (size_t)total;
}

void read_segment(uint_fast8_t *in, const size_t length, uint_fast8_t *out){
	uint_fast8_t segment[length];//whole frame
	uint_fast8_t payload[length-5];//without header
	uint_fast8_t raw_frame[length-4];//with header (for crc)
	
	int i;
	for(i=0;i<length;i++)//load into memory
		segment[i] = *in++;
		
	//Read header
	uint_fast8_t id = segment[0];
	uint_fast16_t seqn = ((uint_fast16_t)segment[1])<<8 + (uint_fast16_t)segment[2];
	uint_fast16_t ackn = ((uint_fast16_t)segment[3])<<8 + (uint_fast16_t)segment[4];
	
	//Grab payload with and without the header
	for(i=0;i<length-4;i++){
		if(i>=5)
			payload[i-5] = segment[i];
		raw_frame[i] = segment[i];
	}
	
	//CRC read, compute and compare
	uint_fast32_t crc_read = ((uint_fast32_t)segment[length-4])<<24 + ((uint_fast32_t)segment[length-3])<<16 + ((uint_fast32_t)segment[length-2])<<8 + (uint_fast32_t)segment[length-1];
	uint_fast32_t crc_comp = crc32_custom(0, raw_frame, length-4);
	
	if(crc_comp==crc_read){
		//TODO: what is done with correct data? Where does it go?
	}else{
		//TODO: What is done when a packet has an error? How and when does the reciever signal to the transmitter about this?
	}	
}

int main(){
	printf("test");
}

