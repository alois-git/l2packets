#ifndef L2PACKETREADER_H_
#define L2PACKETREADER_H_

//#define L2P_NETWORK_DEBUGOUT

#ifdef L2PNET_ENABLE_OLD_RECVSEND
unsigned char *L2PacketReceive(
		unsigned int sock,
		long tv_sec, long tv_usec,
		unsigned int *rcvdLen );

#endif /* L2PNET_ENABLE_OLD_RECVSEND */

/**
 L2PacketReceive_malloc
 * Reads L2 packet from socket sock
 * Reads 1st 2 bytes, treates them as packet len, and then reads len bytes
 * places all received data (including 1st 2 bytes) in allocated by malloc() buffer.
 * Sets (*rcvdLen) to number of bytes received

 * On read timeout (lWaitMiliSecs) returns NULL
 * On error returns NULL
 * returns pointer to buffer on success. caller should free returned buffer by free()
*/
unsigned char *L2PacketReceive_malloc( SOCKET sock, long lWaitMilliSecs, unsigned int *rcvdLen );

/**
 L2PacketReceive_buffer
 * Reads L2 packet from socket sock
 * Reads 1st 2 bytes, treates them as packet len, and then reads len bytes
 * places all received data (including 1st 2 bytes) in buffer recvBuffer.
 * Sets (*rcvdLen) to number of bytes received

 * On read timeout (lWaitMiliSecs) returns 0
 * On error returns -1
 * returns 1 on success

 * recvBuffer must point to big enough memory block (10 Kb min)
*/
int L2PacketReceive_buffer( SOCKET sock, long lWaitMilliSecs, unsigned int *rcvdLen, unsigned char *recvBuffer );

#endif /*L2PACKETREADER_H_*/
