#include "stdafx.h"
#include "L2PacketNames.h"

void L2PacketNames_InitServer();
void L2PacketNames_InitClient();

void L2PacketNames_Init()
{
	L2PacketNames_InitServer();
	L2PacketNames_InitClient();
}

void L2Packets_GetL2PacketName( bool fromServer,
	unsigned char opcode1, unsigned short opcode2,
	char *outPacketName, unsigned int cchMax )
{
	if( fromServer )
		L2Packets_GetL2PacketName_fromServer( opcode1, opcode2, outPacketName, cchMax );
	else
		L2Packets_GetL2PacketName_fromClient( opcode1, opcode2, outPacketName, cchMax );
	outPacketName[cchMax] = 0;
}

