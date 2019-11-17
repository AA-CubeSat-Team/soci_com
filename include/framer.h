//framing and deframing functions for the communication system intended to be used on the Soci cubesat.
//https://github.com/efreneau/SOCi-Satellite-Communication

#ifndef _framer_h
#define _framer_h

#include "crc32_custom.h"
#include "COBS.h"

size_t create_segment(uint_fast8_t port, uint_fast16_t seq_num, uint_fast16_t ack, uint_fast8_t *in, const size_t length, uint_fast8_t *out);
//port is to keep track of what is being transfered
//seq_num is the byte # corresponding to the first byte in the current payload (tx side)
//ack is the byte # referring to the last error free byte (rx side)
//*in points to the payload array
//*out points to the output array

size_t split_and_frame(uint_fast8_t port, uint_fast16_t ack, uint_fast8_t *in, const size_t length, const size_t target_payload_size, uint_fast8_t *out);
//port is to keep track of what is being transfered
//ack is the byte # referring to the last error free byte (rx side)
//*in points to the payload array
//length refers to the total length in bytes of the data object
//*out points to the output array

void read_segment(uint_fast8_t *in, const size_t length, uint_fast8_t *out);
//port signals what data type is being sent
//seq_num is the byte # corresponding to the first byte in the current payload
//ack is the byte # referring to the last error free byte recieved
//*in points to the unread segment
//*out points to the output array for data

#endif
