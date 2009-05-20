#ifndef H_L2_PACKET_NAMES
#define H_L2_PACKET_NAMES

void L2PacketNames_Init();

void L2Packets_GetL2PacketName( bool fromServer,
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

void L2Packets_GetL2PacketName_fromServer(
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

void L2Packets_GetL2PacketName_fromClient(
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax );

#endif
