#ifndef H_L2_PACKET_NAMES
#define H_L2_PACKET_NAMES

/** \file L2PacketNames.h
* Header to define functions to work with packet opcodes/packet names.
*/

/** Initializes strings */
void L2PacketNames_Init();

/** Get packet name (string) by packet opcode
* \param fromServer - must be true for Server->Client packet
* \param opcode1 - main packet opcode
* \param opcode2 - extended packet opcode. Used only for packets S->C 0xFE and C->S 0xD0
* \param outPacketName - pointer to buffer to receive packet name
* \param cchMax - buffer size
* \return resulting string in outPacketName
*/
void L2Packets_GetL2PacketName( bool fromServer,
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

/** Get packet name (string) by packet opcode for Server->Client packets
* \param opcode1 - main packet opcode
* \param opcode2 - extended packet opcode. Used only for packets S->C 0xFE
* \param outPacketName - pointer to buffer to receive packet name
* \param cchMax - buffer size
* \return resulting string in outPacketName
*/
void L2Packets_GetL2PacketName_fromServer(
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

/** Get packet name (string) by packet opcode for Client->Server packets
* \param opcode1 - main packet opcode
* \param opcode2 - extended packet opcode. Used only for packets C->S 0xD0
* \param outPacketName - pointer to buffer to receive packet name
* \param cchMax - buffer size
* \return resulting string in outPacketName
*/
void L2Packets_GetL2PacketName_fromClient(
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

#endif
