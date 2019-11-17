## SOCi-Satellite-Communication (v1.1) ##
SOC-i is the first mission of the Aeronautics &amp; Astronautics CubeSat Team (AACT) at University of Washington.

Project website: ​[soci_com](https://github.com/AA-CubeSat-Team/soci_com)

### Features ###

* Code to perform COBS substitution and packetize an arbitrarily sized payload.
* Packet formatted to support a sliding window protocol.
* Error check with CRC-32 using an optimized polynomial.
* Can pack and unpack data.

### TODO ###

* Testing of code that unpacks frames.
* Back-end software to assemble and store final results.
* Software interface between the comms software and the physical hardware (TTL module and radio or OBC and radio).
* HMAC signatures for commands. Code to sign and check critical commands.
* Add a window size entry to be able to aim for a target PER.
* Autonomous downlink.
* Maybe: remove dependence of COBS. The radio might already provide something like this.

### Files and Folders ###

***COBS.c*** : Perform Consistent Overhead Byte Stuffing (COBS) to remove all 0x0 bytes in a sequence so that 0x0 can be used as the frame delimiter.

***crc32_custom.c*** : Compute the CRC-32 using an optimized polynomial (0x9960034c). This error-check is able to detect 32-bit burst errors and all 6-bit error patterns in sequences up to 4092 B.

***framer.c*** : All code relating to framing and deframing of data. The *create_segment()* method packetizes some data. *split_and_frame()* breaks data up into short runs of data and creates the packet for each. *read_segment()* deframes a packet and checks the CRC.

***/test/*** : Code to test various components of the system.

### Included Libraries ###

[libcorrect](https://github.com/quiet/libcorrect): Library to perform [Convolutional codes](https://en.wikipedia.org/wiki/Convolutional_code) and [Reed-Solomon](https://en.wikipedia.org/wiki/Reed%E2%80%93Solomon_error_correction).
libcorrect uses a [Viterbi algorithm](https://en.wikipedia.org/wiki/Viterbi_algorithm) decoder to decode convolutional codes. We are planning to add the ability for the satellite to autonomously downlink data. This is useful because SatNOGS provides the ability to record RF captures from a large community of groundstations but doesn't provide the ability of transmission. This rules out reliable transfer because 2-way comms is required. All the data must be sent in one shot and be as error-free as possible. Hence, additional information coding will be necessary for this mode.
